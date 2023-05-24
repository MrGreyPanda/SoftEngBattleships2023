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

#include "game_over_message.h"

// give up
// ...

#include "game_state.h"

#include "battle_panel.h"
#include "end_panel.h"

// other messages

/**
 * @brief Handles responses and messages from the server to the client.
 */
class ClientResponseMessageHandler {
   public:
    static void handle_message_string(const std::string& message);

    inline static void set_game_controller_game_state(GameState* game_state)
    {
        game_controller_game_state_ = game_state;
    };

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
     * TODO: Throw exception if the ship has been destroyed in server but not in client
     */
    static void handle_shot_message_(const ShotMessage& message);

    // TODO more
    // Maybe have private static game_state_* here, then, this handler can really handle all stuff
    // Question is, who is updating the GUI? and how?

    /**
     * @brief Handles the message of a game over
     * 
     * @param message
    */
    static void handle_game_over_message_(const GameOverMessage& message);

    static GameState* game_controller_game_state_;
};
