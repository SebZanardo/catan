#include "player.h"

void player_setup(Player* player) {
    for (int i = 0; i < MAX_BOARD_EDGES; i++) {
        player->available_edge_positions[i] = false;
    }

    for (int i = 0; i < MAX_BOARD_VERTICES; i++) {
        player->available_vertex_positions[i] = false;
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
}

void player_build_road(Player* player, u8 edge_index) {
    player->resource_cards[BRICK]--;
    player->resource_cards[WOOD]--;
    player->placed_road_positions[player->placed_roads++] = edge_index;
}

void player_build_settlement(Player* player, u8 vertex_index) {
    player->resource_cards[BRICK]--;
    player->resource_cards[WOOD]--;
    player->resource_cards[WHEAT]--;
    player->resource_cards[WOOL]--;
    player->placed_settlement_positions[player->placed_settlements++] = vertex_index;
}

void player_build_city(Player* player, u8 vertex_index) {
    player->resource_cards[WHEAT] -= 2;
    player->resource_cards[ORE] -= 3;
    player->placed_city_positions[player->placed_cities++] = vertex_index;
}

void player_build_development_card(Player* player, DevelopmentCard card) {
    player->resource_cards[WOOL]--;
    player->resource_cards[WHEAT]--;
    player->resource_cards[ORE]--;
    player->development_cards_held[card]++;
}

void player_spend_development_card(Player* player, DevelopmentCard card) {
    player->development_cards_held[card]--;
}
