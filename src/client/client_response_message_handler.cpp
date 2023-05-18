#include "client_response_message_handler.h"

#include <iostream>

GameState* ClientResponseMessageHandler::game_controller_game_state_ = nullptr;

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

// Sets own player id and game id
void ClientResponseMessageHandler::handle_join_response_(
    const JoinResponse &response) {
    assert(game_controller_game_state_ != nullptr && "game_controller_game_state_ cannot be nullptr"); 
    game_controller_game_state_->add_player(new Player(response.get_player_id()));
    game_controller_game_state_->set_game_id(response.get_game_id());
}

// TODO: implement
void ClientResponseMessageHandler::handle_joined_message_(
    const JoinedMessage &message) {
    assert(game_controller_game_state_ != nullptr && "game_controller_game_state_ cannot be nullptr"); 
}

// Sets own player as ready
void ClientResponseMessageHandler::handle_ready_response_(
    const ReadyResponse &response) {
    assert(game_controller_game_state_ != nullptr && "game_controller_game_state_ cannot be nullptr"); 
    game_controller_game_state_->set_player_ready(
        game_controller_game_state_->get_player_id_by_index(0));
}

// Sets other player as ready
void ClientResponseMessageHandler::handle_ready_message_(
    const ReadyMessage &message) {
    assert(game_controller_game_state_ != nullptr && "game_controller_game_state_ cannot be nullptr"); 
    game_controller_game_state_->set_player_ready(
        game_controller_game_state_->get_player_id_by_index(1));
}

// Sets own player as prepared
void ClientResponseMessageHandler::handle_prepared_response_(
    const PreparedResponse &response) {
    game_controller_game_state_->get_players()[0]->set_prepared();
}

// Sets other player as prepared
void ClientResponseMessageHandler::handle_prepared_message_(
    const PreparedMessage &message) {
    game_controller_game_state_->get_players()[1]->set_prepared();
}

// TODO: implement
void ClientResponseMessageHandler::handle_shoot_response_(
    const ShootResponse &response) {
    std::cout << "[ClientResponseMessageHandler] Handling shoot response not "
                 "implemented yet."
              << std::endl;
    Player* player = game_controller_game_state_->get_player_by_id(response.get_player_id());
    if(response.is_valid()){
        player->get_enemy_board().set_is_shot(response.get_x(), response.get_y(), true);
        if(response.has_hit()){
            player->is_own_turn = true;
            player->has_shot = false;
            player->get_own_board().set_grid_value(response.get_x(), response.get_y(), 6);
        }
        else{
            player->is_own_turn = false;
            player->has_shot = true;
        }
    }
    else{
        player->is_own_turn = true;
        player->has_shot = false;
    }
}

// TODO: implement
void ClientResponseMessageHandler::handle_shot_message_(
    const ShotMessage &message) {
    unsigned short x = message.get_x();
    unsigned short y = message.get_y();
    game_controller_game_state_->get_players()[0]->get_own_board().set_is_shot(x, y, true);
    if(message.has_hit()){
        game_controller_game_state_->get_players()[0]->get_own_board().get_ship(x, y)->shot_at();
        game_controller_game_state_->get_players()[0]->is_own_turn = false;
    }
    else{
        game_controller_game_state_->get_players()[0]->is_own_turn = true;
        game_controller_game_state_->get_players()[0]->has_shot = false;
    }
}