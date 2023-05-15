#include "client_prepared_request.h"

ClientPreparedRequest::ClientPreparedRequest() : ClientRequest() {}

ClientPreparedRequest::ClientPreparedRequest(const json& data)
    : ClientRequest(data) {
    // parse ship data
    ships_ = std::vector<ShipData>();
    for (auto& ship_data : data["ships"]) {
        ships_.push_back();
    }
