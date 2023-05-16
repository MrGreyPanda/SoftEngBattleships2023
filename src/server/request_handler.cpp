
#include "request_handler.h"

#include "game_instance.h"
#include "game_instance_manager.h"
#include "helper_functions.h"
#include "join_message.h"
#include "player_manager.h"
#include "server_network_manager.h"

void RequestHandler::handle_request(const MessageType& type,
                                    const json& data) {
    switch (type) {
        case MessageType::ReadyRequestType:
            // Parse the ready request
            try {
                ReadyRequest ready_request(data);
                handle_ready_request_(ready_request);
            } catch (const std::exception& e) {
                std::cout << "[RequestHandler] Error parsing ready request: "
                          << e.what() << std::endl;
                return;
            }

            break;

        case MessageType::PreparedRequestType:
            // Parse the ready request
            try {
                PreparedRequest prepared_request(data);
                handle_prepared_request_(prepared_request);
            } catch (const std::exception& e) {
                std::cout
                    << "[RequestHandler] Error parsing prepared request: "
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
                std::cout << "[RequestHandler] Error parsing shoot request: "
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
            //         std::cout << "[RequestHandler] Error parsing give up
            //         request: "
            //                   << e.what() << std::endl;
            //         return;
            //     }

            //     break;

        case MessageType::JoinRequestType:
            throw std::runtime_error(
                "[RequestHandler] Please call handle_join_request() instead "
                "of handle_request. This is a special case because the "
                "ServerNetworkManager needs the player_id from the newly "
                "created player if the join request is successful.");
            return;

        default:
            throw std::runtime_error(
                "[RequestHandler] Unhandled request type");
            return;
    }
}

std::tuple<Player*, JoinResponse> RequestHandler::handle_join_request(
    const JoinRequest& join_request) {
    assert(join_request.get_type() == MessageType::JoinRequestType);

    // create a player id string by creating a random hash string
    std::string new_player_id = HelperFunctions::create_random_id();

    // add new player to player manager
    Player* new_player_ptr = PlayerManager::add_or_get_player(new_player_id);
    if (new_player_ptr == nullptr) {
        std::cout
            << "[RequestHandler] Error: Could not add player to PlayerManager"
            << std::endl;

        const JoinResponse join_response("", "",
                                         "Error: Could not add player to "
                                         "PlayerManager");

        return std::make_tuple(nullptr, join_response);
    }

    std::cout << "[RequestHandler] (Debug) Added new player with ID '"
              << new_player_id << "'" << std::endl;

    // add the player to a game
    GameInstance* game_ptr =
        GameInstanceManager::add_player_to_any_game(new_player_ptr);

    const std::string game_id = game_ptr->get_id();

    if (game_ptr != nullptr) {
        std::cout << "[RequestHandler] Added Player '" << new_player_id
                  << "'to a game with ID '" << game_id << "'" << std::endl;

        // Player successfully joined the game

        // formulate response
        const JoinResponse join_response(game_id, new_player_id);

        // notify the other player that a player joined
        // create join message
        const std::string other_player_id =
            game_ptr->try_get_other_player_id(new_player_id);

        if (!other_player_id.empty()) {
            const JoinMessage join_message(game_id, other_player_id);

            ServerNetworkManager::send_message(join_message.to_string(),
                                               join_message.get_player_id());
        }

        return std::make_tuple(new_player_ptr, join_response);

    } else {
        // Error adding player to a game
        std::cout << "[RequestHandler] Error: Could not add player to "
                     "any game!"
                  << std::endl;
        // TODO add more error messages

        // Formulate error response message
        const JoinResponse response(
            "", new_player_id, "Error: Could not add player to any game!");

        return std::make_tuple(nullptr, response);
    }
}

void RequestHandler::handle_ready_request_(const ReadyRequest& ready_request) {
    assert(ready_request.get_type() == MessageType::ReadyRequestType);

    const ReadyResponse ready_response(ready_request.get_game_id(),
                                       ready_request.get_player_id());

    ServerNetworkManager::send_message(ready_response.to_string(),
                                       ready_response.get_player_id());
}

void RequestHandler::handle_prepared_request_(
    const PreparedRequest& prepared_request) {
    assert(prepared_request.get_type() == MessageType::PreparedRequestType);

    const PreparedResponse prepared_response(
        prepared_request.get_game_id(), prepared_request.get_player_id(),
        prepared_request.get_ship_data(), "Not implemented yet!");

    ServerNetworkManager::send_message(prepared_response.to_string(),
                                       prepared_response.get_player_id());
}

void RequestHandler::handle_shoot_request_(const ShootRequest& shoot_request) {
    std::string game_id = shoot_request.get_game_id();

    GameState* game_ptr =
        GameInstanceManager::get_game_instance(game_id)->get_game_state();

    std::string player_id = shoot_request.get_player_id();
    short x               = shoot_request.get_x();
    short y               = shoot_request.get_y();

    // Get player from player manager
    Player* player_ptr = PlayerManager::try_get_player(player_id);

    // Check if own players enemy board is already shot at the given coords
    if (player_ptr->get_enemy_board().get_is_shot(x, y)) {
        const ShootResponse shoot_response(game_id, player_id, x, y);

        ServerNetworkManager::send_message(shoot_response.to_string(),
                                           shoot_response.get_player_id());
        return;
    }

    // Check if other players board is already shot at the given coords
    // Get other player id from game state via game instance
    std::string other_player_id =
        game_ptr->get_other_player_id(player_ptr->get_id());

    // Get other player from player manager
    Player* other_player_ptr = PlayerManager::try_get_player(other_player_id);

    if (other_player_ptr->get_own_board().get_is_shot(x, y)) {
        // Send error message to client
        const ShootResponse shoot_response(
            game_id, player_id, x, y,
            "Error: This position was already shot at!");

        ServerNetworkManager::send_message(shoot_response.to_string(),
                                           shoot_response.get_player_id());
        return;
    }

    other_player_ptr->get_own_board().set_is_shot(x, y, true);
    player_ptr->get_enemy_board().set_is_shot(x, y, true);
    // Check if other players board has a ship at the given coords
    if (other_player_ptr->get_own_board().get_grid_value(x, y) != 0) {
        // Send hit message to client
        const ShootResponse hit_response(game_id, player_id, x, y);

        ServerNetworkManager::send_message(hit_response.to_string(),
                                           hit_response.get_player_id());

        // Send hit message to other client
        const ShootResponse got_hit_response(game_id, other_player_id, x, y);
        // Error message
        ServerNetworkManager::send_message(got_hit_response.to_string(),
                                           got_hit_response.get_player_id());

        // Get ship from other players board
        Ship* ship_ptr = other_player_ptr->get_own_board().get_ship(x, y);

        // Update the ships health
        other_player_ptr->get_own_board().update_ship(x, y);

        // Check if ship is destroyed
        if (ship_ptr->get_is_sunk()) {
            // Send ship destroyed message to client that shot

            // TODO

            // update enemy boards ship vector
            player_ptr->get_enemy_board().update_ship_vec(
                ship_ptr->get_name());
        }

        // Check if other player has lost
        if (other_player_ptr->has_lost()) {
            // Send win message to client
            // const GameOverMessage won_message(
            //     shoot_request.get_game_id(), shoot_request.get_player_id(),
            //     true);  // This is not how it works, here should go an
            //             // Error message
            // ServerNetworkManager::send_message(won_message.to_string(),
            //                                     won_message.get_player_id());

            // // Send lose message to other client
            // const GameOverMessageType
            // lost_message(shoot_request.get_game_id(),
            //                                        other_player_id, false)
            //     ServerNetworkManager::send_message(
            //         lost_message.to_string(), lost_message.get_player_id());
            // game_ptr->set_phase(End);
        }

        // Change turn in game state
        game_ptr->change_turn_player_index();

        return;
    }
}

void RequestHandler::handle_give_up_request_(
    const GiveUpRequest& give_up_request) {
    // const GameOverMessage won_message(give_up_request.get_game_id(),
    //                                   give_up_request.get_player_id(),
    //                                   true);

    // ServerNetworkManager::send_message(won_message.to_string(),
    //                                     won_message.get_player_id());

    throw std::runtime_error("Not implemented yet");
}