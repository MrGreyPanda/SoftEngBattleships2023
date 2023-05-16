#pragma once

#include <tuple>

#include "gave_up_message.h"
#include "give_up_request.h"
#include "give_up_response.h"
#include "join_message.h"
#include "join_request.h"
#include "join_response.h"
#include "player.h"
#include "prepared_message.h"
#include "prepared_request.h"
#include "prepared_response.h"
#include "ready_message.h"
#include "ready_request.h"
#include "ready_response.h"
#include "shoot_request.h"
#include "shoot_response.h"
#include "shot_message.h"

class RequestHandler {
   public:
    static void handle_request(const MessageType& type, const json& data);

    /**
     * @brief Handle a join request. Creates a new player and returns a pointer
     * to the player object. Creates a ServerResponse and calls the
     * send_message function of the ServerNetworkManager
     *
     * @param request The client request object
     * @returns The pointer to the new player object
     */
    static std::tuple<Player*, JoinResponse> handle_join_request(
        const JoinRequest& join_request);

   private:
    /**
     * @brief Handle a ready request. Creates a ServerResponse and calls the
     * send_message function of the ServerNetworkManager
     *
     * @param request
     */
    static void handle_ready_request_(const ReadyRequest& ready_request);

    /**
     * @brief Handle a prepared request. Creates a ServerResponse and calls the
     * send_message function of the ServerNetworkManager
     *
     * @param request
     */
    static void handle_prepared_request_(
        const PreparedRequest& prepared_request);

    /**
     * @brief Handle a shoot request. Creates a ShootResponse and calls the
     * send_message function of the ServerNetworkManager
     *
     * @param request
     *
     * TODO: Check if the hit ship is sunk, and if so, send a message to the
     * players, and update the game state/boards
     */
    static void handle_shoot_request_(const ShootRequest& shoot_request);

    /**
     * @brief Handle a give up request. Creates a GiveUp and calls the
     * send_message function of the ServerNetworkManager
     *
     * @param request
     */
    static void handle_give_up_request_(const GiveUpRequest& give_up_request);
};