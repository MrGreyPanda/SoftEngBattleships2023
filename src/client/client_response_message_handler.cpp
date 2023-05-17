#include "client_response_message_handler.h"

#include <iostream>

void ClientResponseMessageHandler::handle_message_string(
    const std::string &message) {
    // Debug log
    std::cout << "[ClientResponseMessageHandler] Handling message: '"
              << message << "'" << std::endl;

    // parse the JSON
    json json_message;
    try {
        json_message = json::parse(message);
    } catch (std::exception &err) {
        std::cerr << "[ClientResponseMessageHandler] Error while parsing "
                     "message: "
                  << err.what() << std::endl;
        return;
    }

    // get the type of the message
    MessageType message_type = MessageType::UnknownType;
    try {
        Message message(json_message);
        message_type = message.get_type();
    } catch (std::exception &err) {
        std::cerr << "[ClientResponseMessageHandler] Error while extracting "
                     "message type"
                  << err.what() << std::endl;
        return;
    }

    // handle the message for its type
    switch (message_type) {
        // join
        case MessageType::JoinResponseType:
            handle_join_response_(JoinResponse(json_message));
            break;
        case MessageType::JoinedMessageType:
            handle_joined_message_(JoinedMessage(json_message));
            break;

        // ready
        case MessageType::ReadyResponseType:
            handle_ready_response_(ReadyResponse(json_message));
            break;
        case MessageType::ReadyMessageType:
            handle_ready_message_(ReadyMessage(json_message));
            break;

        // prepared
        case MessageType::PreparedResponseType:
            handle_prepared_response_(PreparedResponse(json_message));
            break;
        case MessageType::PreparedMessageType:
            handle_prepared_message_(PreparedMessage(json_message));
            break;

        // shoot
        case MessageType::ShootResponseType:
            handle_shoot_response_(ShootResponse(json_message));
            break;
        case MessageType::ShotMessageType:
            handle_shot_message_(ShotMessage(json_message));
            break;

        case MessageType::UnknownType:
            std::cerr << "[ClientResponseMessageHandler] Error: Unknown "
                         "message type"
                      << std::endl;
            break;
        default:
            std::cerr << "[ClientResponseMessageHandler] Error: Unhandled "
                         "message type"
                      << std::endl;
            break;
    }
}

// TODO: implement
void ClientResponseMessageHandler::handle_join_response_(
    const JoinResponse &response) {
    std::cout << "[ClientResponseMessageHandler] Handling join response not "
                 "implemented yet."
              << std::endl;
}

// TODO: implement
void ClientResponseMessageHandler::handle_joined_message_(
    const JoinedMessage &message) {
    std::cout << "[ClientResponseMessageHandler] Handling joined message not "
                 "implemented yet."
              << std::endl;
}

// TODO: implement
void ClientResponseMessageHandler::handle_ready_response_(
    const ReadyResponse &response) {
    std::cout << "[ClientResponseMessageHandler] Handling ready response not "
                 "implemented yet."
              << std::endl;
}

// TODO: implement
void ClientResponseMessageHandler::handle_ready_message_(
    const ReadyMessage &message) {
    std::cout << "[ClientResponseMessageHandler] Handling ready message not "
                 "implemented yet."
              << std::endl;
}

// TODO: implement
void ClientResponseMessageHandler::handle_prepared_response_(
    const PreparedResponse &response) {
    std::cout
        << "[ClientResponseMessageHandler] Handling prepared response not "
           "implemented yet."
        << std::endl;
}

// TODO: implement
void ClientResponseMessageHandler::handle_prepared_message_(
    const PreparedMessage &message) {
    std::cout
        << "[ClientResponseMessageHandler] Handling prepared message not "
           "implemented yet."
        << std::endl;
}

// TODO: implement
void ClientResponseMessageHandler::handle_shoot_response_(
    const ShootResponse &response) {
    std::cout << "[ClientResponseMessageHandler] Handling shoot response not "
                 "implemented yet."
              << std::endl;
}

// TODO: implement
void ClientResponseMessageHandler::handle_shot_message_(
    const ShotMessage &message) {
    std::cout << "[ClientResponseMessageHandler] Handling shot message not "
                 "implemented yet."
              << std::endl;
}