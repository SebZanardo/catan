#include "cards.h"

void cards_setup(Cards* cards, GameType game_type) {
    switch (game_type) {
        case GAME_NONE:
            for (int i = 0; i < DEVELOPMENT_CARD_TYPE_COUNT; i++) {
                cards->development_cards[i] = 0;
            }
            for (int i = 0; i < RESOURCE_CARD_TYPE_COUNT; i++) {
                cards->resource_cards[i] = 0;
            }
            break;
        case GAME_REGULAR:
            cards->development_cards[MONOPOLY] = 2;
            cards->development_cards[ROAD_BUILDING] = 2;
            cards->development_cards[INVENTION] = 2;
            cards->development_cards[KNIGHT] = 14;
            cards->development_cards[VICTORY_POINT] = 5;

            cards->resource_cards[BRICK] = 19;
            cards->resource_cards[WOOD] = 19;
            cards->resource_cards[WOOL] = 19;
            cards->resource_cards[WHEAT] = 19;
            cards->resource_cards[ORE] = 19;
            break;
        case GAME_EXPANSION:
            cards->development_cards[MONOPOLY] = 3;
            cards->development_cards[ROAD_BUILDING] = 3;
            cards->development_cards[INVENTION] = 3;
            cards->development_cards[KNIGHT] = 20;
            cards->development_cards[VICTORY_POINT] = 5;

            cards->resource_cards[BRICK] = 24;
            cards->resource_cards[WOOD] = 24;
            cards->resource_cards[WOOL] = 24;
            cards->resource_cards[WHEAT] = 24;
            cards->resource_cards[ORE] = 24;
            break;
    }
}
