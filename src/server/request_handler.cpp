
#include "request_handler.h"

#include "client_ready_request.h"
#include "client_shoot_request.h"
#include "game_instance.h"
#include "game_instance_manager.h"
#include "helper_functions.h"
#include "player_manager.h"
#include "server_network_manager.h"
#include "server_response.h"
// #include "client_prepared_request.h"
// #include "client_give_up_request.h"

void RequestHandler::handle_request(const ClientRequestType& type,
                                    const json& data) {
    switch (type) {
        case ClientRequestType::Ready:
            // Parse the ready request
            try {
                ClientReadyRequest ready_request;
                ready_request = ClientReadyRequest(data);
                handle_ready_request_(ready_request);
            } catch (const std::exception& e) {
                std::cout << "[RequestHandler] Error parsing ready request: "
                          << e.what() << std::endl;
                return;
            }

            break;

            // case ClientRequestType::Prepared:
            //     // Parse the ready request
            //     try {
            //         ClientPreparedRequest prepared_request;
            //         prepared_request = ClientPreparedRequest(data);
            //         handle_prepared_request_(prepared_request);
            //     } catch (const std::exception& e) {
            //         std::cout << "[RequestHandler] Error parsing prepared
            //         request: "
            //                   << e.what() << std::endl;
            //         return;
            //     }

            //     break;

        case ClientRequestType::Shoot:
            // Parse the ready request
            try {
                ClientShootRequest shoot_request;
                shoot_request = ClientShootRequest(data);
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

        case ClientRequestType::Join:
            throw std::runtime_error(
                "[RequestHandler] Please call handle_join_request() instead "
                "of handle_request. This is a special case because the "
                "ServerNetworkManager needs the player_id from the newly "
                "created player if the join request is successful.");
            return;

        default:
            throw std::runtime_error(
                "[RequestHandler] Unhandled ClientRequest type");
            return;
    }
}

std::tuple<Player*, ServerResponse> RequestHandler::handle_join_request(
    const ClientRequest& client_request) {
    assert(client_request.get_type() == ClientRequestType::Join);

    // create a player id string by creating a random hash string
    std::string new_player_id = HelperFunctions::create_random_id();

    // add new player to player manager
    Player* new_player_ptr = PlayerManager::add_or_get_player(new_player_id);
    if (new_player_ptr == nullptr) {
        std::cout
            << "[RequestHandler] Error: Could not add player to PlayerManager"
            << std::endl;

        const ServerResponse response(ServerResponseType::RequestResponse,
                                      ClientRequestType::Join, "", "",
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
                                      ClientRequestType::Join,
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
            ServerResponseType::RequestResponse, ClientRequestType::Join, "",
            new_player_id, "Error: Could not add player to any game!");

        return std::make_tuple(nullptr, response);
    }
}

void RequestHandler::handle_ready_request_(
    const ClientRequest& client_request) {
    assert(client_request.get_type() == ClientRequestType::Ready);

    const ServerResponse response(
        ServerResponseType::RequestResponse, ClientRequestType::Ready,
        client_request.get_game_id(), client_request.get_player_id());

    ServerNetworkManager::send_response(response, response.get_player_id());
}

void RequestHandler::handle_prepared_request_(
    const ClientRequest& client_request) {
    assert(client_request.get_type() == ClientRequestType::Prepared);

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