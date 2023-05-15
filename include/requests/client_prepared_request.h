

#include "client_request.h"
#include "ship.h"

class ClientPreparedRequest : public ClientRequest {
   public:
    ClientPreparedRequest();
    ClientPreparedRequest(const json& data);
    ClientPreparedRequest(const std::string& game_id,
                          const std::string& player_id,
                          const std::vector<Ship>& ships);
    ClientPreparedRequest(const std::string& game_id,
                          const std::string& player_id,
                          const std::vector<ShipData>& ship_data);

    json to_json() const;

    const std::vector<Ship>& get_ships() const;
    const std::vector<ShipData>& get_ship_data() const;

   private:
    std::vector<ShipData> ships_;
};