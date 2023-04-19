#pragma once
/*
The class attributes are:
id: string, unique player ID
is_ready: bool, TRUE if the player in the lobby is ready to play
is_prepared: bool, TRUE if the player has placed all the ships and confirmed, via button press, that he is ready, FALSE otherwise
own_board: OwnBoard, a board representing the board the user places his ships and shots from the opponent are displayed.
enemy_board: EnemyBoard, a board representing the board which the user uses to place shots at the enemy and the opponents ships are revealed, turn by turn.
The class operations are:
place_ship: player selects the position and orientation of their ships
shoot: bool, player selects a cell on the opponent’s grid, returns FALSE if it was a miss and TRUE if it was a hit, the function can only be called if the cell hasn’t been shot at already
*/


class Player {
public:

private:

};
