#include "board.h"

TerrainHex regular_recommended_hexes[MAX_BOARD_HEXES] = {
    TERRAIN_PASTURE, TERRAIN_FIELD, TERRAIN_DESERT, TERRAIN_HILL,
    TERRAIN_FOREST, TERRAIN_FIELD, TERRAIN_MOUNTAIN, TERRAIN_FIELD,
    TERRAIN_PASTURE, TERRAIN_FOREST, TERRAIN_PASTURE, TERRAIN_MOUNTAIN,
    TERRAIN_FOREST, TERRAIN_PASTURE, TERRAIN_FIELD, TERRAIN_HILL,
    TERRAIN_MOUNTAIN, TERRAIN_FOREST, TERRAIN_HILL,

    TERRAIN_NONE, TERRAIN_NONE, TERRAIN_NONE, TERRAIN_NONE,
    TERRAIN_NONE, TERRAIN_NONE, TERRAIN_NONE, TERRAIN_NONE,
    TERRAIN_NONE, TERRAIN_NONE, TERRAIN_NONE
};
Port regular_recommended_ports[MAX_BOARD_PORTS] = {
    PORT_THREE, PORT_TWO_WOOL, PORT_THREE, PORT_THREE, PORT_TWO_BRICK,
    PORT_TWO_WOOD, PORT_THREE, PORT_TWO_WHEAT, PORT_TWO_ORE,
    PORT_NONE, PORT_NONE
};
u8 regular_recommended_hex_values[MAX_BOARD_HEXES] = {
    11, 8, 0, 6, 10, 2, 6, 3, 10, 8, 5, 9, 4, 3, 5, 9, 4, 12,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
u8 regular_hex_values[MAX_BOARD_HEXES] = {
    5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

TerrainHex expansion_recommended_hexes[MAX_BOARD_HEXES] = {
    TERRAIN_DESERT, TERRAIN_PASTURE, TERRAIN_HILL, TERRAIN_HILL,
    TERRAIN_FOREST, TERRAIN_DESERT, TERRAIN_FOREST, TERRAIN_FOREST,
    TERRAIN_HILL, TERRAIN_PASTURE, TERRAIN_MOUNTAIN, TERRAIN_FIELD,
    TERRAIN_FOREST, TERRAIN_FIELD, TERRAIN_PASTURE, TERRAIN_HILL,
    TERRAIN_MOUNTAIN, TERRAIN_FIELD, TERRAIN_MOUNTAIN, TERRAIN_PASTURE,
    TERRAIN_MOUNTAIN, TERRAIN_FIELD, TERRAIN_FOREST, TERRAIN_HILL,
    TERRAIN_PASTURE, TERRAIN_FIELD, TERRAIN_FOREST, TERRAIN_FIELD,
    TERRAIN_PASTURE, TERRAIN_MOUNTAIN
};
Port expansion_recommended_ports[MAX_BOARD_PORTS] = {
    PORT_THREE, PORT_TWO_WOOL, PORT_THREE, PORT_THREE, PORT_TWO_BRICK,
    PORT_TWO_WOOL, PORT_TWO_WOOD, PORT_THREE, PORT_TWO_WHEAT, PORT_THREE,
    PORT_TWO_ORE,
};
u8 expansion_recommended_hex_values[MAX_BOARD_HEXES] = {
    0, 6, 10, 6, 3, 0, 12, 8, 9, 12, 8, 5, 11, 8, 4,
    11, 9, 2, 11, 5, 10, 3, 9, 4, 3, 10, 5, 4, 2, 6
};
u8 expansion_hex_values[MAX_BOARD_HEXES] = {
    2, 5, 4, 6, 3, 9, 8, 11, 11, 10, 6, 3, 8, 4, 8,
    10, 11, 12, 10, 5, 4, 9, 5, 9, 12, 3, 2, 6
};

// TODO: Setup options
// RECOMMENDED -> same everytime for first game
// BALANCED -> randomise the tiles and use set numbers
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
        case GAME_NONE:
            for (int i = 0; i < MAX_BOARD_HEXES; i++) {
                board->hexes[i] = TERRAIN_NONE;
                board->hex_values[i] = 0;
            }
            for (int i = 0; i < MAX_BOARD_PORTS; i++) {
                board->ports[i] = PORT_NONE;
            }
            break;
        case GAME_REGULAR:
            for (int i = 0; i < MAX_BOARD_HEXES; i++) {
                board->hexes[i] = regular_recommended_hexes[i];
                board->hex_values[i] = regular_recommended_hex_values[i];
            }
            for (int i = 0; i < MAX_BOARD_PORTS; i++) {
                board->ports[i] = regular_recommended_ports[i];
            }
            break;
        case GAME_EXPANSION:
            for (int i = 0; i < MAX_BOARD_HEXES; i++) {
                board->hexes[i] = expansion_recommended_hexes[i];
                board->hex_values[i] = expansion_recommended_hex_values[i];
            }
            for (int i = 0; i < MAX_BOARD_PORTS; i++) {
                board->ports[i] = expansion_recommended_ports[i];
            }
            break;
    }
}
