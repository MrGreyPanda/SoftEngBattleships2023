#include "client_ready_request.h"

ClientReadyRequest::ClientReadyRequest() : ClientRequest() {}

ClientReadyRequest::ClientReadyRequest(std::string game_id,
                                       std::string player_id)
    : ClientRequest(ClientRequestType::Ready, game_id, player_id) {}

ClientReadyRequest::ClientReadyRequest(const json& data)
    : ClientRequest(data) {}

json ClientReadyRequest::to_json() const { return ClientRequest::to_json(); }
