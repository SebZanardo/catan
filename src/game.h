#ifndef GAME_H
#define GAME_H

#include "core.h"
#include "board.h"
#include "cards.h"
#include "player.h"

typedef enum {
	REGULAR,    // 2-4 players
	EXPANSION,  // 5-6 players
} GameType;

typedef struct {
	Board board;
	Cards cards;
	Player players[6];
	u8 player_count;
	GameType game_type;
} GameState;

#endif  /* GAME_H */
