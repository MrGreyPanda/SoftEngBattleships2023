#pragma once

#include <functional>

#include "sockpp/tcp_socket.h"

class ServerNetworkManager {
   public:
    /**
     * @brief Constructs a new ServerNetworkManager
     */
    ServerNetworkManager();

    /**
     * @brief Broadcasts a message to all conne
    // Start the cted clients
     *
     * @param message The message to broadcast
     */
    static void broadcast(const std::string& message);

    /**
     * @brief Sends a message to a specific client
     *
     * @param player_id The ID of the player to send the message to
     */
    static void player_left(const std::string& player_id);

   private:
    /**
     * @brief Starts the server listener loop
     */
    static void start();

    /**
     * @brief Handle the messages of a new thread
     *
     * @param socket The socket to handle
     * @param message_handler The message handler function to use
     */
    static void handle_socket(
        sockpp::tcp_socket socket,
        const std::function<void(const std::string&,
                                 const sockpp::tcp_socket::addr_t&)>&
            message_handler);

    /**
     * @brief Handles an incoming message from a client
     *
     * @param message The message to handle
     */
    static void handle_incoming_message(const std::string& message);
};