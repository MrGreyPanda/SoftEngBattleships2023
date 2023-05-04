#pragma once

#include <functional>
#include <shared_mutex>
#include <unordered_map>
#include <string>

#include "client_request.h"
#include "server_response.h"
#include "sockpp/tcp_acceptor.h"
#include "sockpp/tcp_socket.h"
#include "sockpp/tcp_connector.h"

#include "ResponseListenerThread.h"



class ClientNetworkManager{

public:
    /**
     * @brief initialises a connection too host
     * @param host the host of the connection
     * @param port the port for the connection
     */
    static void init(const std::string& host, const uint16_t port);

    static void sendRequest(const ClientRequest& request);

    static void parseResponse(const std::string& message);

private:

    static bool connect(const std::string& host, const uint16_t port);

    static sockpp::tcp_connector* connection_;

    static bool connectionSuccess_;
    static bool failedToConnect_;

};