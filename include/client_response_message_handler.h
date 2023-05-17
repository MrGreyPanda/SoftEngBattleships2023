#pragma once

// join
#include "join_message.h"
#include "join_response.h"

// ready
#include "ready_message.h"
#include "ready_response.h"

// prepared
#include "prepared_message.h"
#include "prepared_response.h"

// shoot
#include "shoot_response.h"
#include "shot_message.h"

// give up
// ...

// other messages

/**
 * @brief Handles responses and messages from the server to the client.
 */
class ClientResponseMessageHandler {
   public:
    static void handle_message_string(const std::string& message);

   private:
    /**
     * @brief Handles the response to a join request. This will include the
     * game_id and player_id assigned to this client
     *
     * @param request
     */
    static void handle_join_response_(const JoinResponse& request);

    /**
     * @brief Handles the message of another player joining the lobby.
     *
     * @param request
     */
    static void handle_joined_message_(const JoinedMessage& message);

    /**
     * @brief Handles the response to a ready request.
     * If this is recieved, this client knows that the server knows that it
     * is ready to go from the lobby to the preparation phase.
     *
     * @param request
     */
    static void handle_ready_response_(const ReadyResponse& request);

    /**
     * @brief Handles the message of another player being ready to play (to go
     * from the lobby to the preparation phase.)
     *
     * @param request
     */
    static void handle_ready_message_(const ReadyMessage& message);

    /**
     * @brief Handles the response to a prepared request. This will include
     * wether the ship configuration was valid or not.
     *
     * @param request
     */
    static void handle_prepared_response_(const PreparedResponse& request);

    /**
     * @brief Handles the message of another player being prepared to battle.
     *
     * @param request
     */
    static void handle_prepared_message_(const PreparedMessage& message);

    /**
     * @brief Handles the response to a shoot request. This will include
     * wether the shot was valid or not.
     *
     * @param request
     */
    static void handle_shoot_response_(const ShootResponse& request);

    /**
     * @brief Handles the message of another players shot on this clients
     * board.
     *
     * @param request
     */
    static void handle_shot_message_(const ShotMessage& message);

    // TODO more
};
