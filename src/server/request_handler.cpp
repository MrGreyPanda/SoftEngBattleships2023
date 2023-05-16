
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

    if (game_ptr != nullptr) {
        std::cout << "[RequestHandler] Added Player '" << new_player_id
                  << "'to a game with ID '" << game_ptr->get_id() << "'"
                  << std::endl;

        // Player successfully joined the game

        // formulate response
        const JoinResponse join_response(game_ptr->get_id(), new_player_id);

        // notify the other player that a player joined
        // create join message
        const std::string other_player_id =
            game_ptr->get_other_player_id(new_player_id)->get_id();

        if (!other_player_id.empty()) {
            const JoinMessage join_message(game_ptr->get_id(),
                                           other_player_id);

            ServerNetworkManager::send_response(join_message.to_string(),
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

    ServerNetworkManager::send_response(ready_response.to_string(),
                                        ready_response.get_player_id());
}

void RequestHandler::handle_prepared_request_(
    const PreparedRequest& prepared_request) {
    assert(prepared_request.get_type() == MessageType::PreparedRequestType);

    const PreparedResponse prepared_response(
        prepared_request.get_game_id(), prepared_request.get_player_id(),
        prepared_request.get_ship_data(), "Not implemented yet!");

    ServerNetworkManager::send_response(prepared_response.to_string(),
                                        prepared_response.get_player_id());
}

void RequestHandler::handle_shoot_request_(const ShootRequest& shoot_request) {
    GameState* game_ptr =
        GameInstanceManager::get_game_instance(shoot_request.get_game_id())
            ->get_game_state();

    // Get coords from client request, needs to be coded -> Check up with Lukas
    // short x = shoot_request.get_x();
    // short y = shoot_request.get_y();
    short x = 0;  // DUMMY VALUES
    short y = 0;  // DUMMY VALUES
    // Get player from player manager
    Player* player_ptr =
        PlayerManager::try_get_player(shoot_request.get_player_id());

    // Check if own players enemy board is already shot at the given coords
    if (player_ptr->get_enemy_board().get_is_shot(x, y)) {
        // Send error message to client

        // TODO
        // const ShootResponse shoot_response(
        //     shoot_request.get_game_id(), shoot_request.get_player_id(),
        //     "Error: You already shot at this position!");

        // ServerNetworkManager::send_response(shoot_response.to_string(),
        //                                     shoot_response.get_player_id());
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

        // TODO
        // const ShootResponse shoot_response(
        //     shoot_request.get_game_id(), shoot_request.get_player_id(),
        //     "Error: This position was already shot at!");

        // ServerNetworkManager::send_response(shoot_response.to_string(),
        //                                     shoot_response.get_player_id());
        return;
    }

    other_player_ptr->get_own_board().set_is_shot(x, y, true);
    player_ptr->get_enemy_board().set_is_shot(x, y, true);
    // Check if other players board has a ship at the given coords
    if (other_player_ptr->get_own_board().get_grid_value(x, y) != 0) {
        // Send hit message to client
        // const ServerResponse response(ServerResponseType::RequestResponse,
        //                         ClientRequestType::Shoot,
        //                         shoot_request.get_game_id(),
        //                         shoot_request.get_player_id(),
        //                         "Hit!");
        // ServerNetworkManager::send_response(response.to_string(),
        // response.get_player_id());

        // // Send hit message to other client
        // const ServerResponse response(ServerResponseType::RequestResponse,
        //                         ClientRequestType::ShootRequest,
        //                         shoot_request.get_game_id(),
        //                         other_player_id,
        //                         "You got hit!");
        // ServerNetworkManager::send_response(response.to_string(),
        // response.get_player_id());

        // Get ship from other players board
        Ship* ship_ptr = other_player_ptr->get_own_board().get_ship(x, y);

        // Update the ships health
        other_player_ptr->get_own_board().update_ship(x, y);

        // Check if ship is destroyed
        if (ship_ptr->get_is_sunk()) {
            // Send ship destroyed message to client
            // const ServerResponse
            // response(ServerResponseType::RequestResponse,
            //                     ClientRequestType::Shoot,
            //                     shoot_request.get_game_id(),
            //                     shoot_request.get_player_id(),
            //                     "You destroyed a ship!");

            // // Send ship destroyed message to other client
            // const ServerResponse
            // response(ServerResponseType::RequestResponse,
            //                     ClientRequestType::Shoot,
            //                     shoot_request.get_game_id(),
            //                     other_player_id,
            //                     "One of your ships was destroyed!");

            // update enemy boards ship vector
            player_ptr->get_enemy_board().update_ship_vec(
                ship_ptr->get_name());
        }

        // Check if other player has lost
        if (other_player_ptr->has_lost()) {
            // Send win message to client
            // const ServerResponse
            // response(ServerResponseType::RequestResponse,
            //                     ClientRequestType::Shoot,
            //                     shoot_request.get_game_id(),
            //                     shoot_request.get_player_id(),
            //                     "You won!");
            // ServerNetworkManager::send_response(response.to_string(),
            // response.get_player_id());

            // // Send lose message to other client
            // const ServerResponse
            // response(ServerResponseType::RequestResponse,
            //                     ClientRequestType::Shoot,
            //                     shoot_request.get_game_id(),
            //                     other_player_id,
            //                     "You lost!");
            // ServerNetworkManager::send_response(response.to_string(),
            // response.get_player_id());
            game_ptr->set_phase(End);
        }

        // Change turn in game state
        game_ptr->change_turn_player_index();

        return;
    }
}

void RequestHandler::handle_give_up_request_(
    const GiveUpRequest& give_up_request) {
    throw std::runtime_error("Not implemented yet");
}