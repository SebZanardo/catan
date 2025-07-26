#ifndef BOARD_H
#define BOARD_H

#include "core.h"

#define MAX_BOARD_EDGES 109
#define MAX_BOARD_VERTICES 80
#define MAX_BOARD_HEXES 30
#define MAX_BOARD_PORTS 11

typedef enum {
	TERRAIN_NONE,
	TERRAIN_HILL,
	TERRAIN_FOREST,
	TERRAIN_PASTURE,
	TERRAIN_FIELD,
	TERRAIN_MOUNTAIN,
	TERRAIN_DESERT,
} TerrainHex;

typedef enum {
	PORT_NONE,
	PORT_THREE,
	PORT_TWO_BRICK,
	PORT_TWO_WOOD,
	PORT_TWO_WOOL,
	PORT_TWO_WHEAT,
	PORT_TWO_ORE,
} Port;

typedef struct {
	u8 edges[MAX_BOARD_EDGES];
	u8 vertices[MAX_BOARD_VERTICES];
	TerrainHex hexes[MAX_BOARD_HEXES];
	u8 hex_values[MAX_BOARD_HEXES];
	Port ports[MAX_BOARD_PORTS];
	u8 robber_position;
	u8 robber_moved_by;  // Store what player moved the robber last
} Board;

void board_setup(Board* board, GameType game_type);

#endif  /* BOARD_H */
