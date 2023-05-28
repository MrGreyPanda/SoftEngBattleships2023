#pragma once

#include "prepared_request.h"

/**
 * @brief Message sent by a player when the game is over
 */
class GameOverMessage : public PreparedRequest {
   public:
    GameOverMessage(const json& data);

    /**
     * @brief Construct a new Game Over Message object
     * (This constructor is used when a player gives up in the preparation
     * phase and their ship configuration is not set yet.)
     *
     * @param game_id
     * @param player_id
     * @param has_won
     */
    GameOverMessage(const std::string& game_id, const std::string& player_id,
                    const bool& has_won);
    GameOverMessage(const std::string& game_id, const std::string& player_id,
                    const bool& has_won, std::array<ShipData, 5> ship_config);

    json to_json() const;

    MessageType get_type() const;

    bool has_won() const;

   private:
    bool has_won_;
};
