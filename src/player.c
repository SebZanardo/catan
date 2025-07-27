#include "player.h"

void player_setup(Player* player) {
    for (int i = 0; i < MAX_BOARD_EDGES; i++) {
        player->available_edge_positions[i] = false;
        player->placed_road_positions[i] = false;
    }

    for (int i = 0; i < MAX_BOARD_VERTICES; i++) {
        player->available_vertex_positions[i] = false;
        player->placed_settlement_positions[i] = false;
        player->placed_city_positions[i] = false;
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

void player_collect_resource(Player* player, ResourceCard resource) {
    player->resource_cards[resource]++;
}

void player_spend_resource(Player* player, ResourceCard resource) {
    player->resource_cards[resource]--;
}

void player_build_road(Player* player, u8 edge_index) {
    player->placed_road_positions[edge_index] = true;
    player->placed_roads++;
}

void player_build_settlement(Player* player, u8 vertex_index) {
    player->placed_settlement_positions[vertex_index] = true;
    player->placed_settlements++;

    player->victory_points++;
}

void player_build_city(Player* player, u8 vertex_index) {
    player->placed_city_positions[vertex_index] = true;
    player->placed_cities++;

    player->victory_points++;
}

void player_build_development_card(Player* player, DevelopmentCard card) {
    if (card == VICTORY_POINT) {
        player->victory_points++;
    }

    player->development_cards_held[card]++;
}

void player_spend_development_card(Player* player, DevelopmentCard card) {
    player->development_cards_held[card]--;
}
