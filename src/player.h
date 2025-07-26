#ifndef PLAYER_H
#define PLAYER_H

#include "core.h"
#include "cards.h"

typedef enum {
	PLAYER_RED,
	PLAYER_ORANGE,
	PLAYER_YELLOW,
	PLAYER_GREEN,
	PLAYER_BLUE,
	PLAYER_PURPLE,
} PlayerColour;

typedef struct {
	char name[16];
	u8 resource_cards_held[5];
	u8 development_cards_held[5];
	u8 development_cards_played[5];

	u8 placed_road_positions[15];
	u8 placed_settlement_positions[5];
	u8 placed_city_positions[4];
	u8 placed_roads;
	u8 placed_settlements;
	u8 placed_cities;

	PlayerColour colour;
} Player;

#endif  /* PLAYER_H */
