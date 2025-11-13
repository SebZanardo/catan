#include "board.h"

// TODO: Just write two functions for these instead of being tricky
DEFINE_SHUFFLE_FUNCTION(TerrainHex, board_hex_shuffle, MAX_BOARD_HEXES)
DEFINE_SHUFFLE_FUNCTION(Port, board_port_shuffle, MAX_BOARD_PORTS)

void board_setup(Board* board) {
    board->robber_position = MAX_BOARD_HEXES;
    board->robber_moved_by = MAX_PLAYERS;

    u8 hex_value_index;

    // TODO: Get information from parsing from file
}

void board_place_robber(Board* board, u8 tile_index, u8 player_index) {
    board->robber_position = tile_index;
    board->robber_moved_by = player_index;
}
