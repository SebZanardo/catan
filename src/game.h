#ifndef GAME_H
#define GAME_H

#include "core.h"
#include "board.h"
#include "cards.h"
#include "player.h"

typedef struct {
	Board board;
	Cards cards;
	Player players[MAX_PLAYERS];
	u8 player_count;
	GameType game_type;
} Game;

void game_start(Game* game, GameType game_type);
bool game_setup_add_player(Game* game, PlayerColour colour, char name[16]);
bool game_setup_remove_player(Game* game, u8 index);

#endif  /* GAME_H */
