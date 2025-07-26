#ifndef BOARD_H
#define BOARD_H

#include "core.h"

typedef enum {
	HILL,
	FOREST,
	PASTURE,
	FIELD,
	MOUNTAIN,
	DESERT,
} TerrainHex;

typedef enum {
	THREE,
	TWO_BRICK,
	TWO_WOOD,
	TWO_WOOL,
	TWO_WHEAT,
	TWO_ORE,
} Port;

typedef struct {
	u8 edges[109];
	u8 vertices[80];
	TerrainHex hexes[30];
	Port ports[11];
	u8 robber_position;
	u8 robber_moved_by;  // Store what player moved the robber last
} Board;

#endif  /* BOARD_H */
