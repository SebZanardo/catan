#ifndef CARDS_H
#define CARDS_H

#include "core.h"

#define RESOURCE_CARD_TYPE_COUNT 5
#define DEVELOPMENT_CARD_TYPE_COUNT 5
#define MAX_DEVELOPMENT_CARDS 34

typedef enum {
	BRICK,
	WOOD,
	WOOL,
	WHEAT,
	ORE,
} ResourceCard;

typedef enum {
	MONOPOLY,
	ROAD_BUILDING,
	INVENTION,
	KNIGHT,
	VICTORY_POINT,
} DevelopmentCard;

typedef struct {
	DevelopmentCard development_cards[MAX_DEVELOPMENT_CARDS];
	u8 resource_cards[RESOURCE_CARD_TYPE_COUNT];
	u8 development_card_count;
} Cards;

void cards_setup(Cards* cards, GameType game_type);
DevelopmentCard card_draw_development_card(Cards* cards);

#endif  /* CARDS_H */
