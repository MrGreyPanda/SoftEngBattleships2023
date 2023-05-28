#include "client_response_message_handler.h"

#include <iostream>

#include "preparation_panel.h"

GameState *ClientResponseMessageHandler::game_controller_game_state_ = nullptr;

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

        case MessageType::GiveUpResponseType:
            // do nothing and wait for the game over message.
            break;
        case MessageType::GaveUpMessageType:
            // do nothing and wait for game over message
            break;

        case MessageType::GameOverMessageType:
            handle_game_over_message_(GameOverMessage(json_message));
            break;

        case MessageType::UnknownType:
            std::cerr << "[ClientResponseMessageHandler] Error: Unknown "
                         "message type"
                      << std::endl;
            break;
        default:
            std::cerr << "[ClientResponseMessageHandler] Error: Unhandled "
                         "message type: "
                      << MessageTypeHelpers::make_string_from_message_type(
                             message_type)
                      << std::endl;
            break;
    }
}

// Sets own player id and game id
void ClientResponseMessageHandler::handle_join_response_(
    const JoinResponse &response) {
    assert(game_controller_game_state_ != nullptr &&
           "game_controller_game_state_ cannot be nullptr");

    // make sure the game state does not have a player and was reset
    assert(game_controller_game_state_->get_players().size() == 0 &&
           "game_controller_game_state_ should not have players");

    std::cout << "Adding new player\n";
    game_controller_game_state_->add_player(
        new Player(response.get_player_id()));
    game_controller_game_state_->set_game_id(response.get_game_id());
    // LobbyPanel::set_game_state(game_controller_game_state_);
    PreparationPanel::reset();
    BattlePanel::reset();
    EndPanel::reset();

    if (response.get_player_amount() > 1) {
        game_controller_game_state_->add_player(new Player(""));
        game_controller_game_state_->get_players()[0]->is_own_turn = false;
        game_controller_game_state_->get_players()[0]->has_shot    = false;
    } else {
        game_controller_game_state_->get_players()[0]->is_own_turn = true;
        game_controller_game_state_->get_players()[0]->has_shot    = false;
    }

    PreparationPanel::update_board();
    BattlePanel::update_board();

    game_controller_game_state_->set_phase(Lobby);
}

void ClientResponseMessageHandler::handle_joined_message_(
    const JoinedMessage &message) {
    assert(game_controller_game_state_ != nullptr &&
           "game_controller_game_state_ cannot be nullptr");
    if (message.get_number_of_players() == 2 &&
        game_controller_game_state_->get_players().size() == 1) {
        game_controller_game_state_->add_player(new Player(""));
    } else if (message.get_number_of_players() == 1 &&
               game_controller_game_state_->get_players().size() == 2) {
        Player *player_to_rm_ptr =
            game_controller_game_state_->get_players()[1];
        game_controller_game_state_->remove_player(player_to_rm_ptr);
    }

    game_controller_game_state_->set_phase(Lobby);
    // LobbyPanel::set_game_state(game_controller_game_state_);
}

// Sets own player as ready
void ClientResponseMessageHandler::handle_ready_response_(
    const ReadyResponse &response) {
    assert(game_controller_game_state_ != nullptr &&
           "game_controller_game_state_ cannot be nullptr");
    game_controller_game_state_->set_player_ready(
        game_controller_game_state_->get_player_id_by_index(0));
}

// Sets other player as ready
void ClientResponseMessageHandler::handle_ready_message_(
    const ReadyMessage &message) {
    assert(game_controller_game_state_ != nullptr &&
           "game_controller_game_state_ cannot be nullptr");
    game_controller_game_state_->set_player_ready(
        game_controller_game_state_->get_player_id_by_index(1));
}

// Sets own player as prepared
void ClientResponseMessageHandler::handle_prepared_response_(
    const PreparedResponse &response) {
    if (response.is_valid()) {
        game_controller_game_state_->get_players()[0]->set_prepared();
        if (game_controller_game_state_->get_players()[1]->get_is_prepared()) {
            BattlePanel::update_board();
            game_controller_game_state_->set_phase(Battle);
        }

    } else {
        game_controller_game_state_->get_players()[0]->unset_prepared();
        game_controller_game_state_->get_players()[0]->get_own_board().reset();
    }
}

// Sets other player as prepared
void ClientResponseMessageHandler::handle_prepared_message_(
    const PreparedMessage &message) {
    game_controller_game_state_->get_players()[1]->set_prepared();
    if (game_controller_game_state_->get_players()[0]->get_is_prepared() &&
        game_controller_game_state_->get_phase() != Battle) {
        BattlePanel::update_board();
        game_controller_game_state_->set_phase(Battle);
    }
}

// Handles shoot response and updates game state
void ClientResponseMessageHandler::handle_shoot_response_(
    const ShootResponse &response) {
    // Player *player = game_controller_game_state_->get_player_by_id(
    //     response.get_player_id());
    Player *player = game_controller_game_state_->get_players()[0];
    if (player == nullptr) std::cout << "Player is nullptr" << std::endl;
    if (response.is_valid()) {
        player->get_enemy_board().set_is_shot(response.get_x(),
                                              response.get_y(), true);
        if (response.has_hit()) {
            // update the grid value for GUI, don't change turn
            player->is_own_turn = true;
            player->has_shot    = false;
            // Check if ship has been sunk
            if (response.has_destroyed_ship()) {
                ShipData destroyed_ship = response.get_destroyed_ship();
                unsigned short length = category_to_size(destroyed_ship.name);
                unsigned short x = destroyed_ship.x;
                unsigned short y = destroyed_ship.y;
                if (destroyed_ship.is_horizontal) {
                    for (unsigned short i = 0; i < length; i++) {
                        player->get_enemy_board().set_grid_value(
                            x + i, y,
                            (unsigned short)destroyed_ship.name);
                        player->get_enemy_board().set_is_shot(
                            x + i, y, true);
                    }
                } else {
                    for (unsigned short i = 0; i < length; i++) {
                        player->get_enemy_board().set_grid_value(
                            x, y + i,
                            (unsigned short)destroyed_ship.name);
                        player->get_enemy_board().set_is_shot(x, y + i, true);
                    }
                }
                Ship* dest_ship = player->get_enemy_board().get_ship_by_name(destroyed_ship.name);
                dest_ship->set_is_sunk(true);
                dest_ship->set_xy(destroyed_ship.x, destroyed_ship.y);
                dest_ship->set_is_horizontal(destroyed_ship.is_horizontal);
            } else
                player->get_enemy_board().set_grid_value(response.get_x(),
                                                         response.get_y(), 6);
        } else {
            // Change turns
            player->is_own_turn = false;
            player->has_shot    = true;
        }
    } else {
        // Not changing turn as the player has to shoot again
        player->is_own_turn = true;
        player->has_shot    = false;
    }
}

// Handles shoot message and updates game state
void ClientResponseMessageHandler::handle_shot_message_(
    const ShotMessage &message) {
    unsigned short x = message.get_x();
    unsigned short y = message.get_y();
    game_controller_game_state_->get_players()[0]->get_own_board().set_is_shot(
        x, y, true);
    if (message.has_hit()) {
        // update the status of the ship
        game_controller_game_state_->get_players()[0]
            ->get_own_board()
            .get_ship(x, y)
            ->shot_at();
        // Just for safety
        game_controller_game_state_->get_players()[0]->is_own_turn = false;

        // Check up if we get same data
        bool correct_info =
            game_controller_game_state_->get_players()[0]
                ->get_own_board()
                .get_ship(x, y)
                ->get_is_sunk() == message.has_destroyed_ship();
        // if(!correct_info){
        // throw std::runtime_error("Server and client data mismatch!");
        //}
    } else {
        // Change turns
        game_controller_game_state_->get_players()[0]->is_own_turn = true;
        game_controller_game_state_->get_players()[0]->has_shot    = false;
    }
}

void ClientResponseMessageHandler::handle_game_over_message_(
    const GameOverMessage &message) {
    std::cout
        << "[ClientResponseMessageHandler] (Debug) Game over message received"
        << std::endl;
    assert(game_controller_game_state_ != nullptr);
    assert(game_controller_game_state_->get_players().size() == 2);
    assert(game_controller_game_state_->get_players()[0] != nullptr);
    assert(game_controller_game_state_->get_players()[1] != nullptr);

    // Set the winner
    game_controller_game_state_->get_players()[0]->has_won = message.has_won();
    game_controller_game_state_->get_players()[1]->has_won =
        !message.has_won();

    std::cout
        << "[ClientResponseMessageHandler] Game over message setting ship data"
        << std::endl;

    if (game_controller_game_state_->get_phase() != Preparation) {
        game_controller_game_state_->get_players()[0]
            ->get_enemy_board()
            .set_ship_data(message.get_ship_data());
        EndPanel::update_board();
    }

    std::cout << "[ClientResponseMessageHandler] Game over message handled"
              << std::endl;
    game_controller_game_state_->set_phase(End);
}