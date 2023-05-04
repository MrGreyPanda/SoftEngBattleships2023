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

#include "response_listener_thread.h"



class ClientNetworkManager{

public:
    /**
     * @brief initialises a connection too host
     * @param host the host of the connection
     * @param port the port for the connection
     */
    static void init(const std::string& host, const uint16_t port);

    /**
     * @brief client sends a request to connected host
     * @param request the request to be sent
     */
    static void send_request(const ClientRequest& request);

    /**
     * @brief parses a received response from the server for further processing
     * @param message the string of the message
     */
    static void parse_response(const std::string& message);

private:
    static bool connect_(const std::string& host, const uint16_t port);

    static sockpp::tcp_connector* connection_;

    static bool connection_success_;
    static bool failed_to_connect_;

};