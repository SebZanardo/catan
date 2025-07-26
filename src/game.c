#include "game.h"

void game_start(Game* game, GameType game_type) {
    game->game_type = game_type;

    for (int i = 0; i < game->player_count; i++) {
        player_setup(&game->players[i]);
     }

    board_setup(&game->board, game_type);
    cards_setup(&game->cards, game_type);
}

bool game_setup_add_player(Game* game, PlayerColour colour, char name[16]) {
    // Cannot add another player if we already have max number of players
    if (game->player_count >= MAX_PLAYERS) {
        return false;
    }

    game->player_count++;
    Player* new_player = &game->players[game->player_count];

    new_player->colour = colour;
    for (int i = 0; i < MAX_PLAYER_NAME_LENGTH; i++) {
        new_player->name[i] = name[i];
    }

    return true;
}

bool game_setup_remove_player(Game* game, u8 index) {
    if (game->player_count == 0 || game->player_count <= index) {
        return false;
    }

    game->player_count--;

    // Shift everyone down, instead of swapping with end to preserve order
    // Only need to move name and colour, rest is already zeroed out upon start
    for (int i = index; i < game->player_count; i++) {
        game->players[i].colour = game->players[i + 1].colour;
        for (int c = 0; c < MAX_PLAYER_NAME_LENGTH; c++) {
            game->players[i].name[c] = game->players[i + 1].name[c];
        }
    }

    return true;
}
