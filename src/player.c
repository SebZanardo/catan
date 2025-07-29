#include "player.h"

void player_setup(Player* player) {
    for (int i = 0; i < MAX_BOARD_EDGES; i++) {
        // Make all edges and vertices available
        player->data[i] = 0;
        player->data[i] |= BITMASK_AVAILABLE_EDGE;
        player->data[i] |= BITMASK_AVAILABLE_VERTEX;
    }

    for (int i = 0; i < RESOURCE_CARD_TYPE_COUNT; i++) {
        player->resource_cards[i] = 0;
    }

    for (int i = 0; i < DEVELOPMENT_CARD_TYPE_COUNT; i++) {
        player->development_cards_held[i] = 0;
        player->development_cards_played[i] = 0;
    }

    player->placed_roads = 0;
    player->placed_settlements = 0;
    player->placed_cities = 0;

    player->victory_points = 0;
}

void player_buy_road(Player* player) {
    player->resource_cards[BRICK]--;
    player->resource_cards[WOOD]--;
}

void player_buy_settlement(Player* player) {
    player->resource_cards[BRICK]--;
    player->resource_cards[WOOD]--;
    player->resource_cards[WHEAT]--;
    player->resource_cards[WOOL]--;
}

void player_buy_city(Player* player) {
    player->resource_cards[WHEAT] -= 2;
    player->resource_cards[ORE] -= 3;
}

void player_buy_development_card(Player* player) {
    player->resource_cards[WHEAT]--;
    player->resource_cards[ORE]--;
    player->resource_cards[WOOL]--;
}

void player_add_road(Player* player, u8 edge_index) {
    // NOTE: Game handles updating all player available edges before this

    // TODO: Update connected edges

    // Place road
    player->data[edge_index] |= BITMASK_OWN_ROAD;
    player->placed_roads++;
}

void player_add_settlement(Player* player, u8 vertex_index) {
    // NOTE: Game handles updating all player available vertices before this

    // TODO: Update connected vertices

    // Place settlement
    player->data[vertex_index] |= BITMASK_OWN_SETTLEMENT;
    player->placed_settlements++;

    player->victory_points++;
}

void player_add_city(Player* player, u8 vertex_index) {
    // NOTE: Game handles updating all players available vertices before this

    // Place city
    player->data[vertex_index] |= BITMASK_OWN_CITY;
    player->placed_cities++;

    // Remove settlement
    player->data[vertex_index] &= BITMASK_OWN_SETTLEMENT;
    player->placed_settlements--;

    player->victory_points++;
}

void player_add_development_card(Player* player, DevelopmentCard card) {
    if (card == VICTORY_POINT) {
        player->victory_points++;
    }

    player->development_cards_held[card]++;
}

void player_use_development_card(Player* player, DevelopmentCard card) {
    player->development_cards_held[card]--;
}
