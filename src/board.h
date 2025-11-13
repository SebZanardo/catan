#ifndef BOARD_H
#define BOARD_H

#include "core.h"

// TODO: These shouldn't be hardcoded constants, read from parsed map file
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
	// TODO: Allocate these arrays on an Arena and store length in variable
	TerrainHex hexes[MAX_BOARD_HEXES];
	u8 hex_values[MAX_BOARD_HEXES];  // Dice roll needed to collect
	Port ports[MAX_BOARD_PORTS];

	u8 edges_count;
	u8 vertices_count;
	u8 hex_count;
	u8 port_count;

	u8 robber_position;
	u8 robber_moved_by;  // Store what player moved the robber last
} Board;

void board_setup(Board* board);
void board_place_robber(Board* board, u8 tile_index, u8 player_index);

#endif  /* BOARD_H */
