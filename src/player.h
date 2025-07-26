#ifndef PLAYER_H
#define PLAYER_H

#include "core.h"
#include "cards.h"

#define MAX_PLAYER_NAME_LENGTH 16
#define MAX_PLAYER_ROADS 15
#define MAX_PLAYER_SETTLEMENTS 5
#define MAX_PLAYER_CITIES 4

typedef enum {
	PLAYER_RED,
	PLAYER_ORANGE,
	PLAYER_YELLOW,
	PLAYER_GREEN,
	PLAYER_BLUE,
	PLAYER_PURPLE,
} PlayerColour;

typedef struct {
	char name[MAX_PLAYER_NAME_LENGTH];

	// u8 for roads will correspond to board->edges index
	u8 placed_road_positions[MAX_PLAYER_ROADS];

	// u8 for settlements will correspond to board->vertices index
	u8 placed_settlement_positions[MAX_PLAYER_SETTLEMENTS];

	// u8 for cities will correspond to board->vertices index
	u8 placed_city_positions[MAX_PLAYER_CITIES];

	u8 resource_cards[RESOURCE_CARD_TYPE_COUNT];
	u8 development_cards_held[DEVELOPMENT_CARD_TYPE_COUNT];
	u8 development_cards_played[DEVELOPMENT_CARD_TYPE_COUNT];

	u8 placed_roads;
	u8 placed_settlements;
	u8 placed_cities;

	PlayerColour colour;
} Player;

void player_setup(Player* player);
void player_build_road(Player* player, u8 edge_index);
void player_build_settlement(Player* player, u8 vertex_index);
void player_build_city(Player* player, u8 vertex_index);
void player_build_development_card(Player* player, DevelopmentCard card);

void player_spend_development_card(Player* player, DevelopmentCard card);

#endif  /* PLAYER_H */
