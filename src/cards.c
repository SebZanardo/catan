#include "cards.h"

DEFINE_SHUFFLE_FUNCTION(DevelopmentCard, cards_shuffle, MAX_DEVELOPMENT_CARDS);

void cards_setup(Cards* cards) {
    // TODO: Implement this by passing information from reading from file
    cards_shuffle(&cards->development_cards, cards->development_card_count);
}

DevelopmentCard card_draw_development_card(Cards* cards) {
    return cards->development_cards[--cards->development_card_count];
}
