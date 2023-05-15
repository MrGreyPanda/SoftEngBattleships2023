#pragma once

#include <tuple>

#include "client_request.h"
#include "player.h"
#include "server_response.h"

class RequestHandler {
   public:
    static void handle_request(const ClientRequest& request);

    /**
     * @brief Handle a join request. Creates a new player and returns a pointer
     * to the player object. Creates a ServerResponse and calls the
     * send_response function of the ServerNetworkManager
     *
     * @param request The client request object
     * @returns The pointer to the new player object
     */
    static std::tuple<Player*, ServerResponse> handle_join_request(
        const ClientRequest& request);

   private:
    /**
     * @brief Handle a ready request. Creates a ServerResponse and calls the
     * send_response function of the ServerNetworkManager
     *
     * @param request
     */
    static void handle_ready_request_(const ClientRequest& request);

    /**
     * @brief Handle a prepared request. Creates a ServerResponse and calls the
     * send_response function of the ServerNetworkManager
     *
     * @param request
     */
    static void handle_prepared_request_(const ClientRequest& request);

    /**
     * @brief Handle a shoot request. Creates a ServerResponse and calls the
     * send_response function of the ServerNetworkManager
     *
     * @param request
     * 
     * TODO: Check if the hit ship is sunk, and if so, send a message to the players, and update the game state/boards
     */
    static void handle_shoot_request_(const ClientRequest& request);

    /**
     * @brief Handle a give up request. Creates a ServerResponse and calls the
     * send_response function of the ServerNetworkManager
     *
     * @param request
     */
    static void handle_give_up_request_(const ClientRequest& request);
};