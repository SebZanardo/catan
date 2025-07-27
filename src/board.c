#include "board.h"

#define REGULAR_HEXES 19
#define REGULAR_EDGES 72
#define REGULAR_VERTICES 54
#define REGULAR_PORTS 9
static_assert(REGULAR_HEXES <= MAX_BOARD_HEXES, "");
static_assert(REGULAR_VERTICES <= MAX_BOARD_VERTICES, "");
static_assert(REGULAR_EDGES <= MAX_BOARD_EDGES, "");
static_assert(REGULAR_PORTS <= MAX_BOARD_PORTS, "");

// TODO: Read these lookup tables from file so easy to load custom maps
// Can make custom file format! Yippee that'll be fun :))
static const TerrainHex regular_recommended_hexes[REGULAR_HEXES] = {
    TERRAIN_PASTURE, TERRAIN_FIELD, TERRAIN_DESERT, TERRAIN_HILL,
    TERRAIN_FOREST, TERRAIN_FIELD, TERRAIN_MOUNTAIN, TERRAIN_FIELD,
    TERRAIN_PASTURE, TERRAIN_FOREST, TERRAIN_PASTURE, TERRAIN_MOUNTAIN,
    TERRAIN_FOREST, TERRAIN_PASTURE, TERRAIN_FIELD, TERRAIN_HILL,
    TERRAIN_MOUNTAIN, TERRAIN_FOREST, TERRAIN_HILL
};
static const Port regular_recommended_ports[REGULAR_PORTS] = {
    PORT_THREE, PORT_WOOL, PORT_THREE, PORT_THREE, PORT_BRICK,
    PORT_WOOD, PORT_THREE, PORT_WHEAT, PORT_ORE
};
static const u8 regular_recommended_hex_values[REGULAR_HEXES] = {
    11, 8, 0, 6, 10, 2, 6, 3, 10, 8, 5, 9, 4, 3, 5, 9, 4, 12,
};
static const u8 regular_hex_values[REGULAR_HEXES] = {
    5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11,
};

static const u8 regular_hex_to_vertices[REGULAR_HEXES][6] = {
    {2, 5, 6, 9, 10, 14},
    {1, 4, 5, 8, 9, 13},
    {0, 3, 4, 7, 8, 12},
    {7, 11, 12, 16, 17, 22},
    {16, 21, 22, 27, 28, 33},
    {28, 33, 34, 38, 39, 43},
    {39, 43, 44, 47, 48, 51},
    {40, 44, 45, 48, 49, 52},
    {41, 45, 46, 49, 50, 53},
    {31, 36, 37, 41, 42, 46},
    {20, 25, 26, 31, 32, 37},
    {10, 14, 15, 19, 20, 25},
    {9, 13, 14, 18, 19, 24},
    {8, 12, 13, 17, 18, 23},
    {17, 22, 23, 28, 29, 34},
    {29, 34, 35, 39, 40, 44},
    {30, 35, 36, 40, 41, 45},
    {19, 24, 25, 30, 31, 36},
    {18, 23, 24, 29, 30, 35}
};

// Don't actually need this if we have vertices to edges map
/*static const u8 regular_vertices_to_neighbours[REGULAR_VERTICES][3] = {*/
/*    {3, 4, MAX_BOARD_VERTICES},*/
/*    {4, 5, MAX_BOARD_VERTICES},*/
/*    {5, 6, MAX_BOARD_VERTICES},*/
/*    {0, 7, MAX_BOARD_VERTICES},*/
/*    {0, 1, 8},*/
/*    {1, 2, 9},*/
/*    {2, 10, MAX_BOARD_VERTICES},*/
/*    {3, 11, 12},*/
/*    {4, 12, 13},*/
/*    {5, 13, 14},*/
/*    {6, 14, 15},*/
/*    {7, 16, MAX_BOARD_VERTICES},*/
/*    {7, 8, 17},*/
/*    {8, 9, 18},*/
/*    {9, 10, 19},*/
/*    {10, 20, MAX_BOARD_VERTICES},*/
/*    {11, 21, 22},*/
/*    {12, 22, 23},*/
/*    {13, 23, 24},*/
/*    {14, 24, 25},*/
/*    {15, 25, 26},*/
/*    {16, 27, MAX_BOARD_VERTICES},*/
/*    {16, 17, 28},*/
/*    {17, 18, 29},*/
/*    {18, 19, 30},*/
/*    {19, 20, 31},*/
/*    {20, 32, MAX_BOARD_VERTICES},*/
/*    {21, 33, MAX_BOARD_VERTICES},*/
/*    {22, 33, 34},*/
/*    {23, 34, 35},*/
/*    {24, 35, 36},*/
/*    {25, 36, 37},*/
/*    {26, 37, MAX_BOARD_VERTICES},*/
/*    {27, 28, 38},*/
/*    {28, 29, 39},*/
/*    {29, 30, 40},*/
/*    {30, 31, 41},*/
/*    {31, 32, 42},*/
/*    {33, 43, MAX_BOARD_VERTICES},*/
/*    {34, 43, 44},*/
/*    {35, 44, 45},*/
/*    {36, 45, 46},*/
/*    {37, 46, MAX_BOARD_VERTICES},*/
/*    {38, 39, 47},*/
/*    {39, 40, 48},*/
/*    {40, 41, 49},*/
/*    {41, 42, 50},*/
/*    {43, 51, MAX_BOARD_VERTICES},*/
/*    {44, 51, 52},*/
/*    {45, 52, 53},*/
/*    {46, 53, MAX_BOARD_VERTICES},*/
/*    {47, 48, MAX_BOARD_VERTICES},*/
/*    {48, 49, MAX_BOARD_VERTICES},*/
/*    {49, 50, MAX_BOARD_VERTICES}*/
/*};*/

static const u8 regular_vertices_to_edges[REGULAR_VERTICES][3] = {
    {0, 1, MAX_BOARD_EDGES},
    {2, 3, MAX_BOARD_EDGES},
    {4, 5, MAX_BOARD_EDGES},
    {0, 6, MAX_BOARD_EDGES},
    {1, 2, 7},
    {3, 4, 8},
    {5, 9, MAX_BOARD_EDGES},
    {6, 10, 11},
    {7, 12, 13},
    {8, 14, 15},
    {9, 16, 17},
    {10, 18, MAX_BOARD_EDGES},
    {11, 12, 19},
    {13, 14, 20},
    {15, 16, 21},
    {17, 22, MAX_BOARD_EDGES},
    {18, 23, 24},
    {19, 25, 26},
    {20, 27, 28},
    {21, 29, 30},
    {22, 31, 32},
    {23, 33, MAX_BOARD_EDGES},
    {24, 25, 34},
    {26, 27, 35},
    {28, 29, 36},
    {30, 31, 37},
    {32, 38, MAX_BOARD_EDGES},
    {33, 39, MAX_BOARD_EDGES},
    {34, 40, 41},
    {35, 42, 43},
    {36, 44, 45},
    {37, 46, 47},
    {38, 48, MAX_BOARD_EDGES},
    {39, 40, 49},
    {41, 42, 50},
    {43, 44, 51},
    {45, 46, 52},
    {47, 48, 53},
    {49, 54, MAX_BOARD_EDGES},
    {50, 55, 56},
    {51, 57, 58},
    {52, 59, 60},
    {53, 61, MAX_BOARD_EDGES},
    {54, 55, 62},
    {56, 57, 63},
    {58, 59, 64},
    {60, 61, 65},
    {62, 66, MAX_BOARD_EDGES},
    {63, 67, 68},
    {64, 69, 70},
    {65, 71, MAX_BOARD_EDGES},
    {66, 67, MAX_BOARD_EDGES},
    {68, 69, MAX_BOARD_EDGES},
    {70, 71, MAX_BOARD_EDGES}
};

// TODO: There is most definitely a pattern here. Would be good to simplify
// Pass 3, 4, 5, 4, 3 into a function?
static const u8 regular_edge_to_vertices[REGULAR_EDGES][2] = {
    {0, 3},
    {0, 4},
    {1, 4},
    {1, 5},
    {2, 5},
    {2, 6},
    {3, 7},
    {4, 8},
    {5, 9},
    {6, 10},
    {7, 11},
    {7, 12},
    {8, 12},
    {8, 13},
    {9, 13},
    {9, 14},
    {10, 14},
    {10, 15},
    {11, 16},
    {12, 17},
    {13, 18},
    {14, 19},
    {15, 20},
    {16, 21},
    {16, 22},
    {17, 22},
    {17, 23},
    {18, 23},
    {18, 24},
    {19, 24},
    {19, 25},
    {20, 25},
    {20, 26},
    {21, 27},
    {22, 28},
    {23, 29},
    {24, 30},
    {25, 31},
    {26, 32},
    {27, 33},
    {28, 33},
    {28, 34},
    {29, 34},
    {29, 35},
    {30, 35},
    {30, 36},
    {31, 36},
    {31, 37},
    {32, 37},
    {33, 38},
    {34, 39},
    {35, 40},
    {36, 41},
    {37, 42},
    {38, 43},
    {39, 43},
    {39, 44},
    {40, 44},
    {40, 45},
    {41, 45},
    {41, 46},
    {43, 47},
    {44, 48},
    {45, 49},
    {46, 50},
    {47, 51},
    {48, 51},
    {48, 52},
    {49, 52},
    {49, 53},
    {50, 53}
};

#define EXPANSION_HEXES 30
#define EXPANSION_EDGES 109
#define EXPANSION_VERTICES 80
#define EXPANSION_PORTS 11
static_assert(EXPANSION_HEXES <= MAX_BOARD_HEXES, "");
static_assert(EXPANSION_EDGES <= MAX_BOARD_EDGES, "");
static_assert(EXPANSION_VERTICES <= MAX_BOARD_VERTICES, "");
static_assert(EXPANSION_PORTS <= MAX_BOARD_PORTS, "");

static const TerrainHex expansion_recommended_hexes[EXPANSION_HEXES] = {
    TERRAIN_DESERT, TERRAIN_PASTURE, TERRAIN_HILL, TERRAIN_HILL,
    TERRAIN_FOREST, TERRAIN_DESERT, TERRAIN_FOREST, TERRAIN_FOREST,
    TERRAIN_HILL, TERRAIN_PASTURE, TERRAIN_MOUNTAIN, TERRAIN_FIELD,
    TERRAIN_FOREST, TERRAIN_FIELD, TERRAIN_PASTURE, TERRAIN_HILL,
    TERRAIN_MOUNTAIN, TERRAIN_FIELD, TERRAIN_MOUNTAIN, TERRAIN_PASTURE,
    TERRAIN_MOUNTAIN, TERRAIN_FIELD, TERRAIN_FOREST, TERRAIN_HILL,
    TERRAIN_PASTURE, TERRAIN_FIELD, TERRAIN_FOREST, TERRAIN_FIELD,
    TERRAIN_PASTURE, TERRAIN_MOUNTAIN
};
static const Port expansion_recommended_ports[EXPANSION_PORTS] = {
    PORT_THREE, PORT_WOOL, PORT_THREE, PORT_THREE, PORT_BRICK,
    PORT_WOOL, PORT_WOOD, PORT_THREE, PORT_WHEAT, PORT_THREE, PORT_ORE
};
static const u8 expansion_recommended_hex_values[EXPANSION_HEXES] = {
    0, 6, 10, 6, 3, 0, 12, 8, 9, 12, 8, 5, 11, 8, 4,
    11, 9, 2, 11, 5, 10, 3, 9, 4, 3, 10, 5, 4, 2, 6
};
static const u8 expansion_hex_values[EXPANSION_HEXES] = {
    2, 5, 4, 6, 3, 9, 8, 11, 11, 10, 6, 3, 8, 4, 8,
    10, 11, 12, 10, 5, 4, 9, 5, 9, 12, 3, 2, 6
};

// TODO: Yeah not gonna do these by hand. We need to write a function or script
static const u8 expansion_hex_to_vertices[EXPANSION_HEXES][6] = {};
static const u8 expansion_vertices_to_edges[EXPANSION_VERTICES][3] = {};
static const u8 expansion_edge_to_vertices[EXPANSION_EDGES][2] = {};

// TODO: Setup options
// RECOMMENDED -> same everytime for first game (remove this and just use seed??)
// BALANCED -> random tiles, walk in order (skip desert) and use set numbers
void board_setup(Board* board, GameType game_type) {
    // TODO: Set robber to desert
    board->robber_position = MAX_BOARD_HEXES;
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

void board_place_robber(Board* board, u8 tile_index, u8 player_index) {
    board->robber_position = tile_index;
    board->robber_moved_by = player_index;
}
