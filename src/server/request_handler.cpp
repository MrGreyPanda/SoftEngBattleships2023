
#include "request_handler.h"

#include "server_response.h"

void RequestHandler::handle_request(const ClientRequest& request) {
    if (client_request.get_type() == ClientRequestType::ClientReadyRequest) {
        handle_ready_request_(client_request, peer_address);
    } else if (client_request.get_type() ==
               ClientRequestType::ClientPreparedRequest) {
        handle_prepared_request_(client_request, peer_address);
    } else if (client_request->get_type() ==
               ClientRequestType::ClientShootRequest) {
        handle_shoot_request_(client_request, peer_address);
    } else if (client_request->get_type() ==
               ClientRequestType::ClientGiveUpRequest) {
        handle_give_up_request_(client_request, peer_address);
    } else {
        throw std::runtime_error(
            "[ServerNetworkManager] Unhandled ClientRequest type");
    }
}

Player* RequestHandler::handle_join_request(
    const ClientRequest& client_request) {
    assert(client_request->get_type() == ClientRequestType::ClientJoinRequest);

    std::cout << "[RequestHandler] Received join request from "
              << peer_address.to_string() << std::endl;

    // create a player id string by creating a random hash string
    std::string new_player_id = HelperFunctions::create_random_id();

    // create new player object
    Player* new_player_ptr = new Player(new_player_id);

    std::cout << "[RequestHandler] (Debug) Created new Player with ID '"
              << new_player-><< "'" << std::endl;

    // add new player to player manager
    PlayerManager::add_or_get_player(new_player_id);
    std::cout << "[ServerNetworkManager] (Debug) Added Player object to "
                 "PlayerManager"
              << std::endl;

    // add the player to a game
    GameInstance* game = nullptr;
    if (GameInstanceManager::add_player_to_any_game(new_player)) {
        std::cout << "[ServerNetworkManager] Added Player to game with ID '"
                  << game->get_id() << "'" << std::endl;

        // formulate response
        return ServerResponse(ServerResponseType::RequestResponse,
                              ClientRequestType::ClientJoinRequest,
                              game->get_id(), new_player_id);
    } else {
        // Error adding player to a game
        std::cout << "[ServerNetworkManager] Error: Could not add player to "
                     "any game!"
                  << std::endl;
        // TODO add more error messages

        // Formulate error response message
        return ServerResponse(ServerResponseType::RequestResponse,
                              ClientRequestType::ClientJoinRequest, "",
                              new_player_id,
                              "Error: Could not add player to any game!");
    }
}

void RequestHandler::handle_ready_request_(
    const ClientRequest& client_request) {
    assert(client_request->get_type() ==
           ClientRequestType::ClientReadyRequest);

    std::cout << "[RequestHandler] (Debug) Received ready request from "
              << peer_address.to_string() << std::endl;

    const ServerResponse response(ServerResponseType::RequestResponse,
                                  ClientRequestType::ClientReadyRequest,
                                  client_request->get_game_id(),
                                  client_request->get_player_id());

    ServerNetworkManager::send_response_to_player(response, player_id);
}

void RequestHandler::handle_prepared_request_(
    const ClientRequest& client_request) {
    assert(client_request->get_type() ==
           ClientRequestType::ClientPreparedRequest);

    throw std::runtime_error("Not implemented yet");
}

void RequestHandler::handle_shoot_request_(
    const ClientRequest& client_request) {
    throw std::runtime_error("Not implemented yet");
}

void RequestHandler::handle_give_up_request_(
    const ClientRequest& client_request) {
    throw std::runtime_error("Not implemented yet");
}