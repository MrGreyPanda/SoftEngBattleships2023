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
    if (response.get_player_amount() > 1) {
        game_controller_game_state_->add_player(new Player(""));
    }
}

// TODO: implement
void ClientResponseMessageHandler::handle_joined_message_(
    const JoinedMessage &message) {
    assert(game_controller_game_state_ != nullptr && "game_controller_game_state_ cannot be nullptr");
    game_controller_game_state_->add_player(new Player(""));
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

// Handles shoot response and updates game state
void ClientResponseMessageHandler::handle_shoot_response_(
    const ShootResponse &response) {

    Player* player = game_controller_game_state_->get_player_by_id(response.get_player_id());
    if(response.is_valid()){
        player->get_enemy_board().set_is_shot(response.get_x(), response.get_y(), true);
        if(response.has_hit()){
            // update the grid value for GUI, don't change turn
            player->is_own_turn = true;
            player->has_shot = false;
            // Check if ship has been sunk
            if(response.has_destroyed_ship()){
                ShipData destroyed_ship = response.get_destroyed_ship();
                unsigned short length = category_to_size(destroyed_ship.name);
                if(destroyed_ship.is_horizontal){
                    for(unsigned short i = 0; i < length; i++){
                        player->get_enemy_board().set_grid_value(destroyed_ship.x + i, destroyed_ship.y, destroyed_ship.name);
                    }
                }
                else {
                    for(unsigned short i = 0; i < length; i++){
                        player->get_enemy_board().set_grid_value(destroyed_ship.x, destroyed_ship.y + i, destroyed_ship.name);
                    }
                }
                player->get_enemy_board().get_ship_by_name(destroyed_ship.name)->set_is_sunk(true);
            }
            player->get_enemy_board().set_grid_value(response.get_x(), response.get_y(), 6);
        }
        else{
            // Change turns
            player->is_own_turn = false;
            player->has_shot = true;
        }
    }
    else{
        // Not changing turn as the player has to shoot again
        player->is_own_turn = true;
        player->has_shot = false;
    }
}

// Handles shoot message and updates game state
void ClientResponseMessageHandler::handle_shot_message_(
    const ShotMessage &message) {

    unsigned short x = message.get_x();
    unsigned short y = message.get_y();
    game_controller_game_state_->get_players()[0]->get_own_board().set_is_shot(x, y, true);
    if(message.has_hit()){
        // update the status of the ship
        game_controller_game_state_->get_players()[0]->get_own_board().get_ship(x, y)->shot_at();
        // Just for safety
        game_controller_game_state_->get_players()[0]->is_own_turn = false;

        // Check up if we get same data
        bool correct game_controller_game_state_->get_players()[0]->get_own_board().get_ship(x, y)->is_sunk() == message.has_destroyed_ship();
        // TODO: Throw error if not correct
    }
    else{
        // Change turns
        game_controller_game_state_->get_players()[0]->is_own_turn = true;
        game_controller_game_state_->get_players()[0]->has_shot = false;
    }
}