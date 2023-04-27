#pragma once

#include <functional>

#include "sockpp/tcp_acceptor.h"
#include "sockpp/tcp_socket.h"

class ServerNetworkManager {
   public:
    /**
     * @brief Constructs a new ServerNetworkManager
     */
    ServerNetworkManager();
    // TODO check if we need a destructor

    /**
     * @brief Broadcasts a message to all connected clients
     *
     * @param message The message to broadcast
     */
    static void broadcast(const std::string& message);

    /**
     * // TODO
     */
    static void player_left(const std::string& player_id);

   private:
    /**
     * @brief Starts the server listener loop
     */
    static void _start();

    /**
     * @brief Handle the messages of a new thread
     *
     * @param socket The socket to handle
     * @param message_handler The message handler function to use
     */
    static void _handle_socket(
        sockpp::tcp_socket socket,
        const std::function<void(const std::string&,
                                 const sockpp::tcp_socket::addr_t&)>&
            message_handler);

    /**
     * @brief Handles an incoming message from a client
     *
     * @param message The message to handle
     */
    static void _handle_incoming_message(const std::string& message);

    static void _send_message_to_player(const std::string& message,
                                        const std::string& player_id);

    static sockpp::tcp_acceptor _acceptor;

    /**
     * @brief A map of player ids to their addresses
     */
    static std::unordered_map<std::tring, std::string> _player_addresses;

    /**
     * @brief A map of player ids to their sockets
     */
    static std::unordered_map<std::string, sockpp::tcp_socket> _sockets;
};