

#include "client_network_manager.h"

// #include <nlohmann/json.hpp>
// #include <thread>

// #include "helper_functions.h"
// #include "player.h"

// #include "server_response.h"
// #client request

#include <sockpp/exception.h>

using json = nlohmann::json;

// initialise static members
sockpp::tcp_connector* ClientNetworkManager::connection_ = nullptr;

ClientNetworkConnectionStatus ClientNetworkManager::connection_status_ =
    ClientNetworkConnectionStatus::NOT_CONNECTED;

bool ClientNetworkManager::connect(const std::string& host,
                                   const uint16_t port) {
    // initialise sockpp framework
    // sockpp::socket_initializer sock_init;

    // reset connection status
    ClientNetworkManager::connection_status_ =
        ClientNetworkConnectionStatus::NOT_CONNECTED;

    // delete exiting connection and create new one
    if (ClientNetworkManager::connection_ != nullptr) {
        ClientNetworkManager::connection_->shutdown();
        delete ClientNetworkManager::connection_;
    }
    ClientNetworkManager::connection_ = new sockpp::tcp_connector();

    // try connecting to server
    if (ClientNetworkManager::connect_to_host_(host, port)) {
        // connected to host
        // TODO check for errors

        // TODO start listening to this connection

        ClientNetworkManager::connection_status_ =
            ClientNetworkConnectionStatus::CONNECTED;
        return true;
    } else {
        ClientNetworkManager::connection_status_ =
            ClientNetworkConnectionStatus::FAILED_TO_CONNECT;
        return false;
    }
}

bool ClientNetworkManager::connect_to_host_(const std::string& address,
                                            const uint16_t port) {
    // create sockpp address and catch any errors
    sockpp::inet_address address;
    try {
        address = sockpp::inet_address(host, port);
    } catch (const sockpp::getaddrinfo_error& e) {
        // GameController::showError("Connection error",
        //                           "Failed to resolve address " +
        //                           e.hostname());
        std::cout << "Connection error: Failed to resolve address "
                  << e.hostname() << std::endl;
        return false;
    }

    // establish connection to given address
    if (!ClientNetworkManager::connection_->connect(address)) {
        std::cout << "Connection error: Failed to connect to "
                  << address.to_string() << ":" << port << std::endl;
        return false;
    }
    return true;  // connect worked
}

// void ClientNetworkManager::send_request(const ClientRequest& request) {
//     if()
// }

ClientNetworkConnectionStatus ClientNetworkManager::get_connection_status() {
    return ClientNetworkManager::connection_status_;
}
