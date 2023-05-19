
#include "server_request_handler.h"

#include "game_instance.h"
#include "game_instance_manager.h"
#include "helper_functions.h"
#include "join_message.h"
#include "player_manager.h"
#include "server_network_manager.h"

void ServerRequestHandler::handle_request(const MessageType& type,
                                          const json& data) {
    switch (type) {
        case MessageType::ReadyRequestType:
            // Parse the ready request
            try {
                ReadyRequest ready_request(data);
                handle_ready_request_(ready_request);
            } catch (const std::exception& e) {
                std::cout
                    << "[ServerRequestHandler] Error parsing ready request: "
                    << e.what() << std::endl;
                return;
            }

            break;

        case MessageType::PreparedRequestType:
            // Parse the ready request
            try {
                const PreparedRequest prepared_request(data);
                handle_prepared_request_(prepared_request);
            } catch (const std::exception& e) {
                std::cout << "[ServerRequestHandler] Error parsing prepared "
                             "request: "
                          << e.what() << std::endl;
                return;
            }

            break;

        case MessageType::ShootRequestType:
            // Parse the ready request
            try {
                ShootRequest shoot_request(data);
                handle_shoot_request_(shoot_request);
            } catch (const std::exception& e) {
                std::cout
                    << "[ServerRequestHandler] Error parsing shoot request: "
                    << e.what() << std::endl;
                return;
            }

            break;

            // case ClientRequestType::GiveUp:
            //     // Parse the ready request
            //     try {
            //         ClientGiveUpRequest give_up_request;
            //         give_up_request = ClientGiveUpRequest(data);
            //         handle_give_up_request_(give_up_request);
            //     } catch (const std::exception& e) {
            //         std::cout << "[ServerRequestHandler] Error parsing give
            //         up request: "
            //                   << e.what() << std::endl;
            //         return;
            //     }

            //     break;

        case MessageType::JoinRequestType:
            throw std::runtime_error(
                "[ServerRequestHandler] Please call handle_join_request() "
                "instead "
                "of handle_request. This is a special case because the "
                "ServerNetworkManager needs the player_id from the newly "
                "created player if the join request is successful.");
            return;

        default:
            throw std::runtime_error(
                "[ServerRequestHandler] Unhandled request type");
            return;
    }
}

std::tuple<Player*, JoinResponse> ServerRequestHandler::handle_join_request(
    const JoinRequest& join_request) {
    assert(join_request.get_type() == MessageType::JoinRequestType);

    // create a player id string by creating a random hash string
    std::string new_player_id = HelperFunctions::create_random_id();

    // add new player to player manager
    Player* new_player_ptr = PlayerManager::add_or_get_player(new_player_id);
    if (new_player_ptr == nullptr) {
        std::cout << "[ServerRequestHandler] Error: Could not add player to "
                     "PlayerManager"
                  << std::endl;

        const JoinResponse join_response("", "",
                                         "Error: Could not add player to "
                                         "PlayerManager");

        return std::make_tuple(nullptr, join_response);
    }

    std::cout << "[ServerRequestHandler] (Debug) Added new player with ID '"
              << new_player_id << "'" << std::endl;

    // add the player to a game
    GameInstance* game_ptr =
        GameInstanceManager::add_player_to_any_game(new_player_ptr);

    if (game_ptr != nullptr) {
        const std::string game_id = game_ptr->get_id();
        std::cout << "[ServerRequestHandler] Added Player '" << new_player_id
                  << "'to a game with ID '" << game_id << "'" << std::endl;

        // Player successfully joined the game

        // formulate response
        const JoinResponse join_response(game_id, new_player_id);

        if (game_ptr->is_full()) {
            // notify the other player that a player joined
            // create join message
            const std::string other_player_id =
                game_ptr->try_get_other_player_id(new_player_id);

            if (!other_player_id.empty()) {
                const JoinedMessage join_message(game_id, other_player_id);

                ServerNetworkManager::send_message(join_message.to_string(),
                                                   other_player_id);
            } else {
                std::cout
                    << "[ServerRequestHandler] Error: Could not find other "
                       "player for game with ID '"
                    << game_id << "'" << std::endl;
            }
        } else {
            std::cout << "[ServerRequestHandler] (Debug) Game with ID '"
                      << game_id << "' is not full yet" << std::endl;
        }

        return std::make_tuple(new_player_ptr, join_response);

    } else {
        // Error adding player to a game
        std::cout << "[ServerRequestHandler] Error: Could not add player to "
                     "any game!"
                  << std::endl;
        // TODO add more error messages

        // Formulate error response message
        const JoinResponse response(
            "", new_player_id, "Error: Could not add player to any game!");

        return std::make_tuple(nullptr, response);
    }
}

void ServerRequestHandler::handle_ready_request_(
    const ReadyRequest& ready_request) {
    std::cout << "[ServerRequestHandler] (Debug) Handling a ready request!"
              << std::endl;
    // Store that this client is ready to play the game
    // TODO check
    const std::string& game_id   = ready_request.get_game_id();
    const std::string& player_id = ready_request.get_player_id();

    GameInstance* game_ptr = GameInstanceManager::get_game_instance(game_id);

    if (game_ptr == nullptr) {
        std::cout << "[ServerRequestHandler] Error: Could not find game with "
                     "ID '"
                  << game_id << "'" << std::endl;

        const ReadyResponse ready_response(
            game_id, player_id,
            "Error: Could not find game for given Game ID.");

        ServerNetworkManager::send_message(ready_response.to_string(),
                                           player_id);

        return;
    }

    // mark the player as ready in its game instance
    if (!game_ptr->set_player_ready(player_id)) {
        std::cout
            << "[ServerRequestHandler] Error: Could not mark player with "
               "ID '"
            << player_id << "' as ready." << std::endl;

        const ReadyResponse ready_response(
            game_id, player_id, "Error: Error marking your player as ready.");

        ServerNetworkManager::send_message(ready_response.to_string(),
                                           player_id);

        return;
    }

    const ReadyResponse ready_response(game_id, player_id);

    ServerNetworkManager::send_message(ready_response.to_string(), player_id);

    // Send a message to the other player if there is one.
    const std::string other_player_id =
        game_ptr->try_get_other_player_id(player_id);

    if (!other_player_id.empty()) {
        const ReadyMessage ready_message(game_id, other_player_id);
        ServerNetworkManager::send_message(ready_message.to_string(),
                                           other_player_id);
    }

    // Check if both players are ready to advance the game
    if (game_ptr->all_players_ready()) {
        std::cout << "[ServerRequestHandler] (Debug) Both players are ready, "
                     "starting game!"
                  << std::endl;

        // Start the game
        game_ptr->start_game();

        // Send a message to both players that the game has started
        // const GameStartedMessage game_started_message(game_id, player_id);
        // ServerNetworkManager::send_message(game_started_message.to_string(),
        //                                    player_id);

        // const std::string other_player_id =
        //     game_ptr->try_get_other_player_id(player_id);

        // if (!other_player_id.empty()) {
        //     ServerNetworkManager::send_message(
        //         game_started_message.to_string(), other_player_id);
        // }
    }
}

void ServerRequestHandler::handle_prepared_request_(
    const PreparedRequest& prepared_request) {
    // Get GameInstance
    const std::string game_id   = prepared_request.get_game_id();
    const std::string player_id = prepared_request.get_player_id();
    const std::vector<ShipData> ship_data_vec =
        prepared_request.get_ship_data();
    GameInstance* game_ptr = GameInstanceManager::get_game_instance(game_id);

    if (game_ptr == nullptr) {
        std::cout << "[ServerRequestHandler] Error: Could not find game with "
                     "ID '"
                  << game_id << "'" << std::endl;

        const PreparedResponse prepared_response(
            game_id, player_id, ship_data_vec,
            "Error: Could not find game for given Game ID.");

        ServerNetworkManager::send_message(prepared_response.to_string(),
                                           player_id);

        return;
    }

    std::cout
        << "[ServerRequestHandler] (Debug) Handling a prepared request!\n"
        << prepared_request.to_string() << std::endl;

    // Validate ship configuration
    const bool is_config_valid =
        game_ptr->set_player_prepared(player_id, ship_data_vec);

    // Send response
    if (is_config_valid) {
        // Send valid response
        const PreparedResponse valid_preparation_response(game_id, player_id,
                                                          ship_data_vec, true);

        ServerNetworkManager::send_message(
            valid_preparation_response.to_string(), player_id);
    } else {
        // Send invalid response
        const PreparedResponse invalid_preparation_response(
            game_id, player_id, ship_data_vec, false,
            "Error: Invalid ship configuration.");

        ServerNetworkManager::send_message(
            invalid_preparation_response.to_string(), player_id);
    }

    // Send a message to the other player if the other player is not yet
    // prepared
    const std::string other_player_id =
        game_ptr->try_get_other_player_id(player_id);

    if (!other_player_id.empty()) {
        const PreparedMessage prepared_message(game_id, other_player_id);
        ServerNetworkManager::send_message(prepared_message.to_string(),
                                           other_player_id);
    }

    // Check if both players are ready to advance the game
    if (game_ptr->all_players_prepared()) {
        std::cout
            << "[ServerRequestHandler] (Debug) Both players are prepared, "
               "starting battle!"
            << std::endl;

        // Start the game
        game_ptr->start_game();

        // Send a message to both players that the game has started
        // const GameStartedMessage game_started_message(game_id, player_id);
        // ServerNetworkManager::send_message(game_started_message.to_string(),
        //                                    player_id);

        // const std::string other_player_id =
        //     game_ptr->try_get_other_player_id(player_id);

        // if (!other_player_id.empty()) {
        //     ServerNetworkManager::send_message(
        //         game_started_message.to_string(), other_player_id);
        // }
    }
}

void ServerRequestHandler::handle_shoot_request_(
    const ShootRequest& shoot_request) {
    std::cout << "Got shoot request\n";

    std::string game_id = shoot_request.get_game_id();

    GameInstance* game_ptr = GameInstanceManager::get_game_instance(game_id);

    std::string player_id       = shoot_request.get_player_id();
    std::string other_player_id = "";
    short x                     = shoot_request.get_x();
    short y                     = shoot_request.get_y();
    bool is_valid               = false;
    bool has_hit                = false;
    bool has_destroyed_ship     = false;
    ShipData destroyed_ship;

    game_ptr->handle_shot(player_id, other_player_id, x, y, is_valid, has_hit,
                          has_destroyed_ship, destroyed_ship);

    if (!is_valid) {
        ShootResponse response(game_id, player_id, x, y,
                               "This shot is not valid!");

        ServerNetworkManager::send_message(response.to_string(), player_id);
    }

    if (other_player_id.empty()) {
        ShootResponse response(
            game_id, player_id, x, y,
            "Server Error: Other player could not be found!");

        ServerNetworkManager::send_message(response.to_string(), player_id);
        return;
    }

    if (has_destroyed_ship) {
        ShootResponse response(game_id, player_id, x, y, destroyed_ship);
        ServerNetworkManager::send_message(response.to_string(), player_id);

        ShotMessage message(game_id, other_player_id, x, y, destroyed_ship);
        ServerNetworkManager::send_message(message.to_string(),
                                           other_player_id);
    } else {
        ShootResponse response(game_id, player_id, x, y, has_hit);

        ServerNetworkManager::send_message(response.to_string(), player_id);

        ShotMessage message(game_id, other_player_id, x, y, has_hit);
        ServerNetworkManager::send_message(message.to_string(),
                                           other_player_id);
    }
}

void ServerRequestHandler::handle_give_up_request_(
    const GiveUpRequest& give_up_request) {
    // const GameOverMessage won_message(give_up_request.get_game_id(),
    //                                   give_up_request.get_player_id(),
    //                                   true);

    // ServerNetworkManager::send_message(won_message.to_string(),
    //                                     won_message.get_player_id());

    throw std::runtime_error("Not implemented yet");
}