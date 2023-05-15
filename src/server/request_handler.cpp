
#include "request_handler.h"

#include "game_instance.h"
#include "game_instance_manager.h"
#include "helper_functions.h"
#include "player_manager.h"
#include "server_network_manager.h"
#include "server_response.h"

void RequestHandler::handle_request(const ClientRequest& request) {
    if (request.get_type() == ClientRequestType::ClientReadyRequest) {
        handle_ready_request_(request);
    } else if (request.get_type() ==
               ClientRequestType::ClientPreparedRequest) {
        handle_prepared_request_(request);
    } else if (request.get_type() == ClientRequestType::ClientShootRequest) {
        handle_shoot_request_(request);
    } else if (request.get_type() == ClientRequestType::ClientGiveUpRequest) {
        handle_give_up_request_(request);
    } else if (request.get_type() == ClientRequestType::ClientJoinRequest) {
        throw std::runtime_error(
            "[RequestHandler] Please call handle_join_request() instead of "
            "handle_request. This is a special case because the "
            "ServerNetworkManager needs the player_id from the newly created "
            "player if the join request is successful.");
    } else {
        throw std::runtime_error(
            "[RequestHandler] Unhandled ClientRequest type");
    }
}

std::tuple<Player*, ServerResponse> RequestHandler::handle_join_request(
    const ClientRequest& client_request) {
    assert(client_request.get_type() == ClientRequestType::ClientJoinRequest);

    // create a player id string by creating a random hash string
    std::string new_player_id = HelperFunctions::create_random_id();

    // add new player to player manager
    Player* new_player_ptr = PlayerManager::add_or_get_player(new_player_id);
    if (new_player_ptr == nullptr) {
        std::cout
            << "[RequestHandler] Error: Could not add player to PlayerManager"
            << std::endl;

        const ServerResponse response(ServerResponseType::RequestResponse,
                                      ClientRequestType::ClientJoinRequest, "",
                                      "",
                                      "Error: Could not add player to "
                                      "PlayerManager");

        return std::make_tuple(nullptr, response);
    }

    std::cout << "[RequestHandler] (Debug) Added  player with ID '"
              << new_player_id << "'" << std::endl;

    // add the player to a game
    GameInstance* game_ptr =
        GameInstanceManager::add_player_to_any_game(new_player_ptr);

    if (game_ptr != nullptr) {
        std::cout << "[RequestHandler] Added Player to a game with ID '"
                  << game_ptr->get_id() << "'" << std::endl;

        // formulate response
        const ServerResponse response(ServerResponseType::RequestResponse,
                                      ClientRequestType::ClientJoinRequest,
                                      game_ptr->get_id(), new_player_id);

        return std::make_tuple(new_player_ptr, response);

    } else {
        // Error adding player to a game
        std::cout << "[RequestHandler] Error: Could not add player to "
                     "any game!"
                  << std::endl;
        // TODO add more error messages

        // Formulate error response message
        const ServerResponse response(
            ServerResponseType::RequestResponse,
            ClientRequestType::ClientJoinRequest, "", new_player_id,
            "Error: Could not add player to any game!");

        return std::make_tuple(nullptr, response);
    }
}

void RequestHandler::handle_ready_request_(
    const ClientRequest& client_request) {
    assert(client_request.get_type() == ClientRequestType::ClientReadyRequest);

    const ServerResponse response(ServerResponseType::RequestResponse,
                                  ClientRequestType::ClientReadyRequest,
                                  client_request.get_game_id(),
                                  client_request.get_player_id());

    ServerNetworkManager::send_response(response, response.get_player_id());
}

void RequestHandler::handle_prepared_request_(
    const ClientRequest& client_request) {
    assert(client_request.get_type() ==
           ClientRequestType::ClientPreparedRequest);

    throw std::runtime_error("Not implemented yet");
}

void RequestHandler::handle_shoot_request_(
    const ClientRequest& client_request) {

    GameState* game_ptr = GameInstanceManager::get_game_instance(client_request.get_game_id())->get_game_state();

    // Get coords from client request, needs to be coded -> Check up with Lukas
    // short x = client_request.get_x();
    // short y = client_request.get_y();
    short x = 0;    // DUMMY VALUES
    short y = 0;    // DUMMY VALUES
    // Get player from player manager
    Player* player_ptr = PlayerManager::try_get_player(client_request.get_player_id());

    // Check if own players enemy board is already shot at the given coords
    if(player_ptr->get_enemy_board().get_is_shot(x, y)){
        // Send error message to client
        const ServerResponse response(ServerResponseType::RequestResponse,
                                ClientRequestType::ClientShootRequest,
                                client_request.get_game_id(),
                                client_request.get_player_id(),
                                "Error: You already shot at this position!");
        ServerNetworkManager::send_response(response, response.get_player_id());
        return;
    }

    // Check if other players board is already shot at the given coords
    // Get other player id from game state via game instance
    std::string other_player_id = game_ptr->get_other_player_id(player_ptr->get_id());

    // Get other player from player manager
    Player* other_player_ptr = PlayerManager::try_get_player(other_player_id);

    if(other_player_ptr->get_own_board().get_is_shot(x, y)){
        // Send error message to client
        const ServerResponse response(ServerResponseType::RequestResponse,
                                ClientRequestType::ClientShootRequest,
                                client_request.get_game_id(),
                                client_request.get_player_id(),
                                "Error: This position was already shot at!");
        ServerNetworkManager::send_response(response, response.get_player_id());
        return;
    }

    other_player_ptr->get_own_board().set_is_shot(x, y, true);
    player_ptr->get_enemy_board().set_is_shot(x, y, true);
    // Check if other players board has a ship at the given coords
    if(other_player_ptr->get_own_board().get_grid_value(x, y) != 0){
        // Send hit message to client
        // const ServerResponse response(ServerResponseType::RequestResponse,
        //                         ClientRequestType::ClientShootRequest,
        //                         client_request.get_game_id(),
        //                         client_request.get_player_id(),
        //                         "Hit!");
        // ServerNetworkManager::send_response(response, response.get_player_id());

        // // Send hit message to other client
        // const ServerResponse response(ServerResponseType::RequestResponse,
        //                         ClientRequestType::ClientShootRequest,
        //                         client_request.get_game_id(),
        //                         other_player_id,
        //                         "You got hit!");
        // ServerNetworkManager::send_response(response, response.get_player_id());

        // Get ship from other players board
        std::shared_ptr<Ship> ship_ptr = other_player_ptr->get_own_board().get_ship(x, y);

        // Update the ships health
        other_player_ptr->get_own_board().update_ship(x, y);

        // Check if ship is destroyed
        if(ship_ptr->get_is_sunk()){
            // Send ship destroyed message to client
            // const ServerResponse response(ServerResponseType::RequestResponse,
            //                     ClientRequestType::ClientShootRequest,
            //                     client_request.get_game_id(),
            //                     client_request.get_player_id(),
            //                     "You destroyed a ship!");

            // // Send ship destroyed message to other client
            // const ServerResponse response(ServerResponseType::RequestResponse,
            //                     ClientRequestType::ClientShootRequest,
            //                     client_request.get_game_id(),
            //                     other_player_id,
            //                     "One of your ships was destroyed!");
            
            // update enemy boards ship vector
            player_ptr->get_enemy_board().update_ship_vec(ship_ptr->get_name());
        }

        // Check if other player has lost
        if(other_player_ptr->has_lost()){
            // Send win message to client
            // const ServerResponse response(ServerResponseType::RequestResponse,
            //                     ClientRequestType::ClientShootRequest,
            //                     client_request.get_game_id(),
            //                     client_request.get_player_id(),
            //                     "You won!");
            // ServerNetworkManager::send_response(response, response.get_player_id());

            // // Send lose message to other client
            // const ServerResponse response(ServerResponseType::RequestResponse,
            //                     ClientRequestType::ClientShootRequest,
            //                     client_request.get_game_id(),
            //                     other_player_id,
            //                     "You lost!");
            // ServerNetworkManager::send_response(response, response.get_player_id());
            game_ptr->set_phase(End); 

        }

        // Change turn in game state
        game_ptr->change_turn_player_index();


        return;
    }



}

void RequestHandler::handle_give_up_request_(
    const ClientRequest& client_request) {

    throw std::runtime_error("Not implemented yet");
}