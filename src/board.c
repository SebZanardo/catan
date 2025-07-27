#include "board.h"
#include "lookup.h"

DEFINE_SHUFFLE_FUNCTION(TerrainHex, board_hex_shuffle, MAX_BOARD_HEXES)
DEFINE_SHUFFLE_FUNCTION(Port, board_port_shuffle, MAX_BOARD_PORTS)

// TODO: Like I mentioned in the other file we need to rework this to load
// map files from disk. Will clean up duplicate logic significantly

void board_setup(Board* board, GameType game_type) {
    board->robber_position = MAX_BOARD_HEXES;
    board->robber_moved_by = MAX_PLAYERS;

    u8 hex_value_index;

    switch (game_type) {
    case GAME_REGULAR:
        board->edges_count = REGULAR_EDGES;
        board->vertices_count = REGULAR_VERTICES;
        board->hex_count = REGULAR_HEXES;
        board->port_count = REGULAR_PORTS;

        for (int i = 0; i < REGULAR_HEXES; i++) {
            board->hexes[i] = regular_hexes[i];
        }
        for (int i = 0; i < REGULAR_PORTS; i++) {
            board->ports[i] = regular_ports[i];
        }

        // Shuffle hexes
        board_hex_shuffle(&board->hexes, board->hex_count);

        // Shuffle ports
        board_port_shuffle(&board->ports, board->port_count);

        // Walk hexes and assign values
        hex_value_index = 0;
        for (u8 i = 0; i < REGULAR_HEXES; i++) {
            if (board->hexes[i] == TERRAIN_DESERT) {
                // Set robber to desert
                board->robber_position = i;
            } else {
                board->hex_values[i] = regular_hex_values[hex_value_index];
                hex_value_index++;
            }
        }
        break;
    case GAME_EXPANSION:
        board->edges_count = EXPANSION_EDGES;
        board->vertices_count = EXPANSION_VERTICES;
        board->hex_count = EXPANSION_HEXES;
        board->port_count = EXPANSION_PORTS;

        for (int i = 0; i < EXPANSION_HEXES; i++) {
            board->hexes[i] = expansion_hexes[i];
        }
        for (int i = 0; i < EXPANSION_PORTS; i++) {
            board->ports[i] = expansion_ports[i];
        }

        // Shuffle hexes
        board_hex_shuffle(&board->hexes, board->hex_count);

        // Shuffle ports
        board_port_shuffle(&board->ports, board->port_count);

        // Walk hexes and assign values
        hex_value_index = 0;
        for (u8 i = 0; i < EXPANSION_HEXES; i++) {
            if (board->hexes[i] == TERRAIN_DESERT) {
                // Set robber to desert
                board->robber_position = i;
            } else {
                board->hex_values[i] = expansion_hex_values[hex_value_index];
                hex_value_index++;
            }
        }
        break;
    }
}

void board_place_robber(Board* board, u8 tile_index, u8 player_index) {
    board->robber_position = tile_index;
    board->robber_moved_by = player_index;
}
