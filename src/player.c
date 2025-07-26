#include "player.h"

void player_setup(Player* player) {
    player->placed_roads = 0;
    player->placed_settlements = 0;
    player->placed_cities = 0;
    player->knights_played = 0;

    for (int i = 0; i < RESOURCE_CARD_TYPE_COUNT; i++) {
        player->resource_cards[i] = 0;
    }

    for (int i = 0; i < DEVELOPMENT_CARD_TYPE_COUNT; i++) {
        player->development_cards[i] = 0;
    }
}
