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

DEFINE_SHUFFLE_FUNCTION(DevelopmentCard, cards_shuffle, MAX_DEVELOPMENT_CARDS);

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
            break;
    }

    cards_shuffle(&cards->development_cards, cards->development_card_count);
}

DevelopmentCard card_draw_development_card(Cards* cards) {
    return cards->development_cards[--cards->development_card_count];
}
