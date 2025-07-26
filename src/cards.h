#ifndef CARDS_H
#define CARDS_H

#include "core.h"

#define RESOURCE_CARD_TYPE_COUNT 5
#define DEVELOPMENT_CARD_TYPE_COUNT 5

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
	u8 development_cards[DEVELOPMENT_CARD_TYPE_COUNT];
	u8 resource_cards[RESOURCE_CARD_TYPE_COUNT];
} Cards;

void cards_setup(Cards* cards, GameType game_type);

#endif  /* CARDS_H */
