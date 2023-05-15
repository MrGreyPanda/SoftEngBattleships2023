

#include "client_request.h"
#include "ship.h"

class ClientPreparedRequest : public ClientRequest {
   public:
    ClientPreparedRequest();
    ClientPreparedRequest(const json& data);
    ClientPreparedRequest(std::string game_id, std::string player_id,
                          std::vector<Ship> ships);
    ClientPreparedRequest(std::string game_id, std::string player_id,
                          std::vector<ShipData> ships);

    json to_json() const;

   private:
    ShipData ships_;
};