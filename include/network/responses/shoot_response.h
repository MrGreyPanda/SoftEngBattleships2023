#pragma once

#include "response.h"
#include "shot_message.h"

/**
 * @brief A message sent from the server to the client as a response to a
 * shoot request.
 */
class ShootResponse : public ShotMessage, public Response {
   public:
    ShootResponse(const json& data);

    /**
     * @brief Constructor for invalid shot response
     */
    ShootResponse(const std::string& game_id, const std::string& player_id,
                  const unsigned short& x, const unsigned short& y,
                  const bool& is_valid, const std::string& error);

    /**
     * @brief Constructor for valid shot response, with no destroyed ship
     */
    ShootResponse(const std::string& game_id, const std::string& player_id,
                  const unsigned short& x, const unsigned short& y,
                  const bool& has_hit);

    /**
     * @brief Constructor for valid shot response, with destroyed ship
     */
    ShootResponse(const std::string& game_id, const std::string& player_id,
                  const unsigned short& x, const unsigned short& y,
                  const ShipData& destroyed_ship_);

    json to_json() const;

    std::string to_string() const;

    std::string get_game_id() const;

    std::string get_player_id() const;

    bool is_valid() const;

    virtual MessageType get_type() const;

   private:
    bool is_valid_;
};
