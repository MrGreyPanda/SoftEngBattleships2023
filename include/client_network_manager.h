#pragma once

// #include <functional>
#include <shared_mutex>
#include <unordered_map>

// #include "sockpp/tcp_acceptor.h"
#include "sockpp/tcp_connector.h"
// #include "sockpp/tcp_socket.h"

enum ClientNetworkConnectionStatus {
    CONNECTED,
    FAILED_TO_CONNECT,
    NOT_CONNECTED
};

class ClientNetworkManager {
   public:
    /**
     * @brief Tries to connect to the host at the specified address and port.
     * Returns true on success and stores the connection and update the
     * connection status. Returns false on failure to connect.
     *
     * @param host the host of the connection
     * @param port the port for the connection
     */
    static bool connect(const std::string& address_string,
                        const uint16_t& port);

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

    /**
     * @brief Get the connection status object
     *
     * @return ClientNetworkConnectionStatus
     */
    static ClientNetworkConnectionStatus get_connection_status();

   private:
    static bool connect_to_host_(const std::string& address_string,
                                 const uint16_t& port);

    static void handle_incoming_messages_();

    static sockpp::tcp_connector* connection_;

    static ClientNetworkConnectionStatus connection_status_;
};