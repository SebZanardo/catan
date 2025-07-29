#include "game.h"

DEFINE_SHUFFLE_FUNCTION(u8, game_player_order_shuffle, MAX_PLAYERS)

void game_start(Game* game, GameType game_type) {
    game->game_type = game_type;

    game->player_turn = 0;

    for (int i = 0; i < game->player_count; i++) {
        player_setup(&game->players[i]);
        game->player_order[i] = i;
    }

    // Shuffle turn order map
    game_player_order_shuffle(&game->player_order, game->player_count);

    // Update player pointer so first player
    game_update_active_player(game);

    board_setup(&game->board, game_type);
    cards_setup(&game->cards, game_type);
}

bool game_setup_add_player(Game* game, PlayerColour colour, char name[16]) {
    // Cannot add another player if we already have max number of players
    if (game->player_count >= MAX_PLAYERS) {
        return false;
    }

    game->player_count++;
    Player* new_player = &game->players[game->player_count];

    new_player->colour = colour;
    for (int i = 0; i < MAX_PLAYER_NAME_LENGTH; i++) {
        new_player->name[i] = name[i];
    }

    return true;
}

bool game_setup_remove_player(Game* game, u8 index) {
    if (game->player_count == 0 || game->player_count <= index) {
        return false;
    }

    game->player_count--;

    // Shift everyone down, instead of swapping with end to preserve order
    // Only need to move name and colour, rest is already zeroed out upon start
    for (int i = index; i < game->player_count; i++) {
        game->players[i].colour = game->players[i + 1].colour;
        for (int c = 0; c < MAX_PLAYER_NAME_LENGTH; c++) {
            game->players[i].name[c] = game->players[i + 1].name[c];
        }
    }

    return true;
}

bool game_valid_road(Game* game, u8 edge_index) {
    assert(edge_index < MAX_BOARD_EDGES);

    // Check that player has roads left to place
    if (game->active_player->placed_roads >= MAX_PLAYER_ROADS) {
        return false;
    }

    // Check that player has resources
    if (
        game->active_player->resource_cards[BRICK] < 1 ||
        game->active_player->resource_cards[WOOD] < 1
    ) {
        return false;
    }

    // Check edge is empty
    if (!(game->active_player->data[edge_index] & BITMASK_AVAILABLE_EDGE)) {
        return false;
    }

    // Check edge is connected to our built roads
    if (!(game->active_player->data[edge_index] & BITMASK_CONNECTED_EDGE)) {
        return false;
    }

    return true;
}

bool game_valid_settlement(Game* game, u8 vertex_index) {
    assert(vertex_index < MAX_BOARD_VERTICES);

    // Check that player has settlements left to place
    if (game->active_player->placed_settlements >= MAX_PLAYER_SETTLEMENTS) {
        return false;
    }

    // Check that player has resources
    if (
        game->active_player->resource_cards[BRICK] < 1 ||
        game->active_player->resource_cards[WOOD] < 1 ||
        game->active_player->resource_cards[WHEAT] < 1 ||
        game->active_player->resource_cards[WOOL] < 1
    ) {
        return false;
    }

    // Check vertex is empty and not within two vertices of another building
    if (!(game->active_player->data[vertex_index] & BITMASK_AVAILABLE_VERTEX)) {
        return false;
    }

    // Check vertex is connected to our built roads
    if (!(game->active_player->data[vertex_index] & BITMASK_CONNECTED_VERTEX)) {
        return false;
    }

    return true;
}

bool game_valid_city(Game* game, u8 vertex_index) {
    assert(vertex_index < MAX_BOARD_VERTICES);

    // Check that player has cities left to place
    if (game->active_player->placed_cities >= MAX_PLAYER_CITIES) {
        return false;
    }

    // Check that player has resources
    if (
        game->active_player->resource_cards[WHEAT] < 2 ||
        game->active_player->resource_cards[ORE] < 3
    ) {
        return false;
    }

    // Check if placing ontop of settlement we own
    if (!(game->active_player->data[vertex_index] & BITMASK_OWN_SETTLEMENT)) {
        return false;
    }

    return true;
}

bool game_valid_development_card(Game* game) {
    // Check that there are cards to buy
    if (game->cards.development_card_count < 1) {
        return false;
    }

    // Check that player has resources
    if (
        game->active_player->resource_cards[WHEAT] < 1 ||
        game->active_player->resource_cards[WOOL] < 1 ||
        game->active_player->resource_cards[ORE] < 1
    ) {
        return false;
    }

    return true;
}

void game_build_road(Game* game, u8 edge_index) {
    // TODO: Loop through players and set edge available to false
    player_add_road(game->active_player, edge_index);
}

void game_build_settlement(Game* game, u8 vertex_index) {
    // TODO: Loop through players and set vertex available to false
    // Also need to do it for 3 neighbouring vertices
    player_add_settlement(game->active_player, vertex_index);
}

void game_build_city(Game* game, u8 vertex_index) {
    player_add_city(game->active_player, vertex_index);
}

void game_build_development_card(Game* game) {
    DevelopmentCard card = card_draw_development_card(&game->cards);
    player_add_development_card(game->active_player, card);
}

void game_update_active_player(Game* game) {
    game->active_player = &game->players[game->player_order[game->player_turn]];
}

void game_next_turn(Game* game) {
    game->player_turn = (game->player_turn + 1) % game->player_count;
    game_update_active_player(game);
}
