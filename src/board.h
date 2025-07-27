#ifndef BOARD_H
#define BOARD_H

#include "core.h"

#define MAX_BOARD_EDGES 109
#define MAX_BOARD_VERTICES 80
#define MAX_BOARD_HEXES 30
#define MAX_BOARD_PORTS 11

typedef enum {
	TERRAIN_HILL,
	TERRAIN_FOREST,
	TERRAIN_PASTURE,
	TERRAIN_FIELD,
	TERRAIN_MOUNTAIN,
	TERRAIN_DESERT,
} TerrainHex;

typedef enum {
	PORT_THREE,
	PORT_BRICK,
	PORT_WOOD,
	PORT_WOOL,
	PORT_WHEAT,
	PORT_ORE,
} Port;

typedef struct {
	// Technically these are no longer needed as players store everything /////
	u8 edges[MAX_BOARD_EDGES];
	u8 vertices[MAX_BOARD_VERTICES];
	///////////////////////////////////////////////////////////////////////////

	TerrainHex hexes[MAX_BOARD_HEXES];
	u8 hex_values[MAX_BOARD_HEXES];  // Dice roll needed to collect
	Port ports[MAX_BOARD_PORTS];

	u8 robber_position;
	u8 robber_moved_by;  // Store what player moved the robber last
} Board;

void board_setup(Board* board, GameType game_type);
void board_place_road(Board* board, u8 edge_index, u8 player_index);
void board_place_settlement(Board* board, u8 vertex_index, u8 player_index);
void board_place_city(Board* board, u8 vertex_index, u8 player_index);
void board_place_robber(Board* board, u8 tile_index, u8 player_index);

#endif  /* BOARD_H */
