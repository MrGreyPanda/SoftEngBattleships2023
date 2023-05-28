
#include "server_request_handler.h"

#include "game_instance.h"
#include "game_instance_manager.h"
#include "game_over_message.h"
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

        case MessageType::GiveUpRequestType:
            // Parse the give up request
            try {
                GiveUpRequest give_up_request(data);
                handle_give_up_request_(give_up_request);
            } catch (const std::exception& e) {
                std::cout << "[ServerRequestHandler] Error parsing give "
                             "up request: "
                          << e.what() << std::endl;
                return;
            }

            break;

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
                                         "PlayerManager",
                                         0);

        return std::make_tuple(nullptr, join_response);
    }

    // add the player to a game
    GameInstance* game_ptr =
        GameInstanceManager::add_player_to_any_game(new_player_ptr);

    if (game_ptr != nullptr) {
        const std::string game_id = game_ptr->get_id();
        std::cout << "[ServerRequestHandler] Added Player '" << new_player_id
                  << "'to a game with ID '" << game_id << "'" << std::endl;

        // Player successfully joined the game

        // formulate response
        JoinResponse join_response(game_id, new_player_id, 1);

        if (game_ptr->is_full()) {
            // notify the other player that a player joined
            // create join message
            const std::string other_player_id =
                game_ptr->try_get_other_player_id(new_player_id);

            if (!other_player_id.empty()) {
                const JoinedMessage join_message(game_id, other_player_id, 2);

                ServerNetworkManager::send_message(join_message.to_string(),
                                                   other_player_id);

                join_response.set_player_amount(2);
            } else {
                std::cout
                    << "[ServerRequestHandler] Error: Could not find other "
                       "player for game with ID '"
                    << game_id << "'" << std::endl;
            }
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
            "", new_player_id, "Error: Could not add player to any game!", 0);

        return std::make_tuple(nullptr, response);
    }
}

void ServerRequestHandler::handle_player_disconnect(
    const std::string& player_id) {
    std::cout << "[ServerRequestHandler] Handling player disconnect for "
                 "player with ID '"
              << player_id << "'" << std::endl;

    // get player instance
    Player* player_ptr = PlayerManager::try_get_player(player_id);

    if (player_ptr == nullptr) {
        std::cout << "[ServerRequestHandler] Error handling player "
                     "disconnect: Could not find player "
                     "with ID '"
                  << player_id << "'" << std::endl;
        return;
    }

    // get game the player is in
    GameInstance* game_ptr =
        GameInstanceManager::find_game_by_player_id(player_id);

    if (game_ptr == nullptr) {
        std::cout << "[ServerRequestHandler] Error handling player "
                     "disconnect: Could not find game "
                     "with player ID '"
                  << player_id << "'" << std::endl;
        return;
    }

    const Phase current_game_phase = game_ptr->get_game_state()->get_phase();

    const std::string other_player_id =
        game_ptr->try_get_other_player_id(player_id);

    if (current_game_phase == Phase::Preparation ||
        current_game_phase == Phase::Battle) {
        // remove the player and let the other one win

        std::cout << "[ServerRequestHandler] Handling player disconnect: "
                     "current phase: "
                  << current_game_phase << std::endl;

        if (game_ptr->try_remove_player(player_ptr)) {
            // notify the other player that he won

            if (!other_player_id.empty()) {
                if (current_game_phase == Phase::Preparation) {
                    const GameOverMessage won_message(game_ptr->get_id(),
                                                      other_player_id, true);

                    ServerNetworkManager::send_message(won_message.to_string(),
                                                       other_player_id);
                } else {
                    const GameOverMessage won_message(
                        game_ptr->get_id(), other_player_id, false,
                        player_ptr->get_own_board().get_ship_configuration());

                    ServerNetworkManager::send_message(won_message.to_string(),
                                                       other_player_id);
                }

            } else {
                std::cout << "[ServerRequestHandler] Error handling player "
                             "disconnect: Could not find other "
                             "player for game with ID '"
                          << game_ptr->get_id() << "'" << std::endl;
            }
        } else {
            std::cout << "[ServerRequestHandler] Error handling player "
                         "disconnect: Could not remove player "
                         "with ID '"
                      << player_id << "' from game with ID '"
                      << game_ptr->get_id() << "'" << std::endl;
            return;
        }
    } else {
        // simply remove the player and notify the other one, if one is there
        if (game_ptr->try_remove_player(player_ptr)) {
        } else {
            std::cout << "[ServerRequestHandler] Error handling player "
                         "disconnect: Could not remove player "
                         "with ID '"
                      << player_id << "' from game with ID '"
                      << game_ptr->get_id() << "'" << std::endl;
            return;
        }

        // notify the other player that the other one disconnected
        const JoinedMessage leave_message(game_ptr->get_id(), player_id, 1);

        ServerNetworkManager::send_message(leave_message.to_string(),
                                           other_player_id);
    }

    PlayerManager::remove_player(player_id);
}

void ServerRequestHandler::handle_ready_request_(
    const ReadyRequest& ready_request) {
    // Store that this client is ready to play the game
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
        // Start the game
        game_ptr->start_preparation();
    }
}

void ServerRequestHandler::handle_prepared_request_(
    const PreparedRequest& prepared_request) {
    // Get GameInstance
    const std::string game_id   = prepared_request.get_game_id();
    const std::string player_id = prepared_request.get_player_id();
    const std::array<ShipData, 5> ship_data_vec =
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
        // Start the game
        game_ptr->start_battle();
    }
}

void ServerRequestHandler::handle_shoot_request_(
    const ShootRequest& shoot_request) {
    std::cout << "Got shoot request\n";

    const std::string game_id = shoot_request.get_game_id();

    GameInstance* game_ptr = GameInstanceManager::get_game_instance(game_id);

    const std::string player_id = shoot_request.get_player_id();
    std::string other_player_id = "";
    short x                     = shoot_request.get_x();
    short y                     = shoot_request.get_y();
    bool is_valid               = false;
    bool has_hit                = false;
    bool has_destroyed_ship     = false;
    ShipData destroyed_ship     = ShipData();
    bool has_won_game           = false;

    game_ptr->handle_shot(player_id, other_player_id, x, y, is_valid, has_hit,
                          has_destroyed_ship, destroyed_ship, has_won_game);

    if (!is_valid) {
        ShootResponse response(game_id, player_id, x, y, false,
                               "This shot is not valid!");

        ServerNetworkManager::send_message(response.to_string(), player_id);
        return;
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

        if (has_won_game) {
            // this last ship decided the game

            std::array<ShipData, 5> winner_ships =
                game_ptr->get_game_state()
                    ->get_player_by_id(player_id)
                    ->get_own_board()
                    .get_ship_configuration();

            std::array<ShipData, 5> loser_ships =
                game_ptr->get_game_state()
                    ->get_player_by_id(other_player_id)
                    ->get_own_board()
                    .get_ship_configuration();

            GameOverMessage game_over_message_to_winner(game_id, player_id,
                                                        true, loser_ships);

            GameOverMessage game_over_message_to_loser(
                game_id, other_player_id, false, winner_ships);

            ServerNetworkManager::send_message(
                game_over_message_to_winner.to_string(), player_id);
            ServerNetworkManager::send_message(
                game_over_message_to_loser.to_string(), other_player_id);

            // end the game
            kill_game_(game_ptr, player_id, other_player_id);
        }
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
    const std::string game_id   = give_up_request.get_game_id();
    const std::string player_id = give_up_request.get_player_id();

    GameInstance* game_ptr = GameInstanceManager::get_game_instance(game_id);

    const GiveUpResponse give_up_response(game_id, player_id);
    ServerNetworkManager::send_message(give_up_response.to_string(),
                                       player_id);

    const std::string other_player_id =
        game_ptr->try_get_other_player_id(player_id);
    if (other_player_id.empty()) {
        std::cout << "[ServerRequestHandler] Error: Could not find other "
                     "player ID for game with ID '"
                  << game_id << "'" << std::endl;
        // Hint: the other player might have left the game already
        return;
    }

    const GaveUpMessage give_up_message(game_id, player_id);
    ServerNetworkManager::send_message(give_up_message.to_string(),
                                       other_player_id);

    // send game over messages
    if (game_ptr->get_game_state()->get_phase() == Phase::Preparation) {
        GameOverMessage game_over_message_to_winner(game_id, other_player_id,
                                                    true);

        GameOverMessage game_over_message_to_loser(game_id, player_id, false);

        ServerNetworkManager::send_message(
            game_over_message_to_winner.to_string(), other_player_id);

        ServerNetworkManager::send_message(
            game_over_message_to_loser.to_string(), player_id);
    } else {
        std::array<ShipData, 5> winner_ships =
            game_ptr->get_game_state()
                ->get_player_by_id(other_player_id)
                ->get_own_board()
                .get_ship_configuration();

        std::array<ShipData, 5> loser_ships = game_ptr->get_game_state()
                                                  ->get_player_by_id(player_id)
                                                  ->get_own_board()
                                                  .get_ship_configuration();

        GameOverMessage game_over_message_to_winner(game_id, other_player_id,
                                                    true, loser_ships);

        GameOverMessage game_over_message_to_loser(game_id, player_id, false,
                                                   winner_ships);

        ServerNetworkManager::send_message(
            game_over_message_to_winner.to_string(), other_player_id);

        ServerNetworkManager::send_message(
            game_over_message_to_loser.to_string(), player_id);
    }

    kill_game_(game_ptr, player_id, other_player_id);
}

void ServerRequestHandler::kill_game_(GameInstance* game_ptr,
                                      const std::string& player_id,
                                      const std::string& other_player_id) {
    // remove the game
    GameInstanceManager::delete_game_(
        game_ptr->get_id());  // TODO FIXME check if this is correct, how
                              // to talk to player manager?
    PlayerManager::remove_player(player_id);
    PlayerManager::remove_player(other_player_id);
}