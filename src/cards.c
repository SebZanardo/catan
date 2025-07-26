#include "cards.h"

#define REGULAR_DEVELOPMENT_CARD_COUNT 25
static_assert(REGULAR_DEVELOPMENT_CARD_COUNT <= MAX_DEVELOPMENT_CARDS, "");
DevelopmentCard regular_development_cards[REGULAR_DEVELOPMENT_CARD_COUNT] = {
    MONOPOLY, MONOPOLY, ROAD_BUILDING, ROAD_BUILDING, INVENTION, INVENTION,
    KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT,
    KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, VICTORY_POINT, VICTORY_POINT,
    VICTORY_POINT, VICTORY_POINT, VICTORY_POINT
};

#define EXPANSION_DEVELOPMENT_CARD_COUNT 34
static_assert(EXPANSION_DEVELOPMENT_CARD_COUNT <= MAX_DEVELOPMENT_CARDS, "");
DevelopmentCard expansion_development_cards[EXPANSION_DEVELOPMENT_CARD_COUNT] = {
    MONOPOLY, MONOPOLY, MONOPOLY, ROAD_BUILDING, ROAD_BUILDING, ROAD_BUILDING,
    INVENTION, INVENTION, INVENTION, KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT,
    KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT,
    KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, KNIGHT, VICTORY_POINT,
    VICTORY_POINT, VICTORY_POINT, VICTORY_POINT, VICTORY_POINT
};

void cards_setup(Cards* cards, GameType game_type) {
    switch (game_type) {
        case GAME_REGULAR:
            cards->resource_cards[BRICK] = 19;
            cards->resource_cards[WOOD] = 19;
            cards->resource_cards[WOOL] = 19;
            cards->resource_cards[WHEAT] = 19;
            cards->resource_cards[ORE] = 19;

            cards->development_card_count = REGULAR_DEVELOPMENT_CARD_COUNT;
            for (int i = 0; i < REGULAR_DEVELOPMENT_CARD_COUNT; i++) {
                cards->development_cards[i] = regular_development_cards[i];
            }
            cards_random_shuffle(cards);
            break;
        case GAME_EXPANSION:
            cards->resource_cards[BRICK] = 24;
            cards->resource_cards[WOOD] = 24;
            cards->resource_cards[WOOL] = 24;
            cards->resource_cards[WHEAT] = 24;
            cards->resource_cards[ORE] = 24;

            cards->development_card_count = EXPANSION_DEVELOPMENT_CARD_COUNT;
            for (int i = 0; i < EXPANSION_DEVELOPMENT_CARD_COUNT; i++) {
                cards->development_cards[i] = expansion_development_cards[i];
            }
            cards_random_shuffle(cards);
            break;
    }
}

DevelopmentCard card_draw_development_card(Cards* cards) {
    return cards->development_cards[--cards->development_card_count];
}

// Fair random in-place shuffle
// https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
void cards_random_shuffle(Cards* cards) {
    for (u8 i = cards->development_card_count - 1; i > 0; i--) {
        u8 j = GetRandomValue(0, i);
        DevelopmentCard temp = cards->development_cards[i];
        cards->development_cards[i] = cards->development_cards[j];
        cards->development_cards[j] = temp;
    }
}
