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
	u8 player_order[MAX_PLAYERS];

	Player* active_player;
	u8 player_count;
	u8 player_turn;

	GameType game_type;
} Game;

void game_start(Game* game, GameType game_type);

bool game_setup_add_player(Game* game, PlayerColour colour, char name[16]);
bool game_setup_remove_player(Game* game, u8 index);

bool game_valid_road(Game* game, u8 edge_index);
bool game_valid_settlement(Game* game, u8 vertex_index);
bool game_valid_city(Game* game, u8 vertex_index);
bool game_valid_development_card(Game* game);

void game_build_road(Game* game, u8 edge_index);
void game_build_settlement(Game* game, u8 vertex_index);
void game_build_city(Game* game, u8 vertex_index);
void game_build_development_card(Game* game);

void game_next_turn(Game* game);
void game_update_active_player(Game* game);

#endif  /* GAME_H */
