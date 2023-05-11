

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

bool ClientNetworkManager::connect(const std::string& address_string,
                                   const uint16_t& port) {
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
    if (ClientNetworkManager::connect_to_host_(address_string, port)) {
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

bool ClientNetworkManager::connect_to_host_(const std::string& address_string,
                                            const uint16_t& port) {
    // create sockpp address and catch any errors
    sockpp::inet_address address;
    try {
        address = sockpp::inet_address(address_string, port);
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

void ClientNetworkManager::send_request(const ClientRequest& request) {
    // 1. check if connected to server
    if (!ClientNetworkManager::connection_->is_connected()) {
        std::cout << "Not connected to server" << std::endl;
        return;
    }

    // 2. Send the client request to the server as json
    const std::string message = request.to_string() + '\0';

    auto bytes_sent = ClientNetworkManager::connection_->write(message.c_str(),
                                                               message.size());

    if (bytes_sent != message.size()) {
        std::cout << "Failed to send full request to server" << std::endl;
        std::cerr << ClientNetworkManager::connection_->last_error_str()
                  << std::endl;
    }
}

ClientNetworkConnectionStatus ClientNetworkManager::get_connection_status() {
    return ClientNetworkManager::connection_status_;
}

void ClientNetworkManager::handle_incoming_messages_() {}
