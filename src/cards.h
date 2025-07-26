#ifndef CARDS_H
#define CARDS_H

#include "core.h"

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
	DevelopmentCard development_cards[34];
	u8 development_cards_remaining;
	u8 resource_cards[5];
} Cards;

#endif  /* CARDS_H */
