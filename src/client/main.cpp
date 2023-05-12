
#include <cstdint>
#include <cstdio>

#include "client_network_manager.h"

int main(int argc, const char** argv) {
    printf("Starting the Client...\n");

    // TODO open connection window

    if (ClientNetworkManager::connect("localhost", 1337)) {
        // Send join request when connected
        ClientNetworkManager::send_request(
            ClientRequest(ClientRequestType::ClientJoinRequest));

        // recieve join response
        while (true) {
        }

        // simulate ready in lobby...

        // ClientNetworkManager::send_request(
        //     ClientRequest(ClientRequestType::ClientReadyRequest, "", ""));
    }

    return 0;
}