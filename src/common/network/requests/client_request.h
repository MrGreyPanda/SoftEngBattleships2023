#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ClientRequest {
   public:
    ClientRequest(const json& data);

    /**
     * @brief Get the player_id string from this ClientRequest
     *
     * @return std::string
     */
    std::string get_player_id() const;

    /**
     * @brief Check if this ClientRequest has a player_id
     *
     * @return true if this ClientRequest has a player_id, false
     * otherwise
     */
    bool has_player_id() const;

   private:
};