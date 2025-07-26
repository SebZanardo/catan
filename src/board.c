#include "board.h"

#define REGULAR_HEXES 19
#define REGULAR_PORTS 9
static_assert(REGULAR_HEXES <= MAX_BOARD_HEXES, "");
static_assert(REGULAR_PORTS <= MAX_BOARD_PORTS, "");

TerrainHex regular_recommended_hexes[REGULAR_HEXES] = {
    TERRAIN_PASTURE, TERRAIN_FIELD, TERRAIN_DESERT, TERRAIN_HILL,
    TERRAIN_FOREST, TERRAIN_FIELD, TERRAIN_MOUNTAIN, TERRAIN_FIELD,
    TERRAIN_PASTURE, TERRAIN_FOREST, TERRAIN_PASTURE, TERRAIN_MOUNTAIN,
    TERRAIN_FOREST, TERRAIN_PASTURE, TERRAIN_FIELD, TERRAIN_HILL,
    TERRAIN_MOUNTAIN, TERRAIN_FOREST, TERRAIN_HILL
};
Port regular_recommended_ports[REGULAR_PORTS] = {
    PORT_THREE, PORT_WOOL, PORT_THREE, PORT_THREE, PORT_BRICK,
    PORT_WOOD, PORT_THREE, PORT_WHEAT, PORT_ORE
};
u8 regular_recommended_hex_values[REGULAR_HEXES] = {
    11, 8, 0, 6, 10, 2, 6, 3, 10, 8, 5, 9, 4, 3, 5, 9, 4, 12,
};
u8 regular_hex_values[REGULAR_HEXES] = {
    5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11,
};

#define EXPANSION_HEXES 30
#define EXPANSION_PORTS 11
static_assert(EXPANSION_HEXES <= MAX_BOARD_HEXES, "");
static_assert(EXPANSION_PORTS <= MAX_BOARD_PORTS, "");

TerrainHex expansion_recommended_hexes[EXPANSION_HEXES] = {
    TERRAIN_DESERT, TERRAIN_PASTURE, TERRAIN_HILL, TERRAIN_HILL,
    TERRAIN_FOREST, TERRAIN_DESERT, TERRAIN_FOREST, TERRAIN_FOREST,
    TERRAIN_HILL, TERRAIN_PASTURE, TERRAIN_MOUNTAIN, TERRAIN_FIELD,
    TERRAIN_FOREST, TERRAIN_FIELD, TERRAIN_PASTURE, TERRAIN_HILL,
    TERRAIN_MOUNTAIN, TERRAIN_FIELD, TERRAIN_MOUNTAIN, TERRAIN_PASTURE,
    TERRAIN_MOUNTAIN, TERRAIN_FIELD, TERRAIN_FOREST, TERRAIN_HILL,
    TERRAIN_PASTURE, TERRAIN_FIELD, TERRAIN_FOREST, TERRAIN_FIELD,
    TERRAIN_PASTURE, TERRAIN_MOUNTAIN
};
Port expansion_recommended_ports[EXPANSION_PORTS] = {
    PORT_THREE, PORT_WOOL, PORT_THREE, PORT_THREE, PORT_BRICK,
    PORT_WOOL, PORT_WOOD, PORT_THREE, PORT_WHEAT, PORT_THREE, PORT_ORE
};
u8 expansion_recommended_hex_values[EXPANSION_HEXES] = {
    0, 6, 10, 6, 3, 0, 12, 8, 9, 12, 8, 5, 11, 8, 4,
    11, 9, 2, 11, 5, 10, 3, 9, 4, 3, 10, 5, 4, 2, 6
};
u8 expansion_hex_values[EXPANSION_HEXES] = {
    2, 5, 4, 6, 3, 9, 8, 11, 11, 10, 6, 3, 8, 4, 8,
    10, 11, 12, 10, 5, 4, 9, 5, 9, 12, 3, 2, 6
};

// TODO: Setup options
// RECOMMENDED -> same everytime for first game
// BALANCED -> random tiles, walk in order (skip desert) and use set numbers
void board_setup(Board* board, GameType game_type) {
    for (int i = 0; i < MAX_BOARD_EDGES; i++) {
        board->edges[i] = MAX_PLAYERS;
    }
    for (int i = 0; i < MAX_BOARD_VERTICES; i++) {
        board->vertices[i] = MAX_PLAYERS;
    }
    board->robber_position = MAX_BOARD_VERTICES;
    board->robber_moved_by = MAX_PLAYERS;

    switch (game_type) {
        case GAME_REGULAR:
            for (int i = 0; i < REGULAR_HEXES; i++) {
                board->hexes[i] = regular_recommended_hexes[i];
                board->hex_values[i] = regular_recommended_hex_values[i];
            }
            for (int i = 0; i < REGULAR_PORTS; i++) {
                board->ports[i] = regular_recommended_ports[i];
            }
            break;
        case GAME_EXPANSION:
            for (int i = 0; i < EXPANSION_HEXES; i++) {
                board->hexes[i] = expansion_recommended_hexes[i];
                board->hex_values[i] = expansion_recommended_hex_values[i];
            }
            for (int i = 0; i < EXPANSION_PORTS; i++) {
                board->ports[i] = expansion_recommended_ports[i];
            }
            break;
    }
}
