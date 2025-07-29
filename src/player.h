#ifndef PLAYER_H
#define PLAYER_H

#include "core.h"
#include "board.h"
#include "cards.h"

#define MAX_PLAYER_NAME_LENGTH 16
#define MAX_PLAYER_ROADS 15
#define MAX_PLAYER_SETTLEMENTS 5
#define MAX_PLAYER_CITIES 4

#define BITMASK_TURN             0b10000000
#define BITMASK_AVAILABLE_EDGE   0b01000000
#define BITMASK_AVAILABLE_VERTEX 0b00100000
#define BITMASK_CONNECTED_EDGE   0b00010000
#define BITMASK_CONNECTED_VERTEX 0b00001000
#define BITMASK_OWN_ROAD         0b00000100
#define BITMASK_OWN_SETTLEMENT   0b00000010
#define BITMASK_OWN_CITY         0b00000001

typedef enum {
	PLAYER_RED,
	PLAYER_ORANGE,
	PLAYER_YELLOW,
	PLAYER_GREEN,
	PLAYER_BLUE,
	PLAYER_PURPLE,
} PlayerColour;

typedef struct {
	// Bitmasked u8 of boolean values
	// 0 --> Player turn?
	// 0 --> Available edge
	// 0 --> Availale vertex
	// 0 --> Connected edge
	// 0 --> Connected vertex
	// 0 --> Owned road
	// 0 --> Owned settlement
	// 0 --> Owned city
	u8 data[MAX_BOARD_EDGES];

	char name[MAX_PLAYER_NAME_LENGTH];

	u8 resource_cards[RESOURCE_CARD_TYPE_COUNT];
	u8 development_cards_held[DEVELOPMENT_CARD_TYPE_COUNT];
	u8 development_cards_played[DEVELOPMENT_CARD_TYPE_COUNT];

	u8 placed_roads;
	u8 placed_settlements;
	u8 placed_cities;

	u8 victory_points;

	PlayerColour colour;
} Player;

void player_setup(Player* player);

void player_buy_road(Player* player);
void player_buy_settlement(Player* player);
void player_buy_city(Player* player);
void player_buy_development_card(Player* player);

void player_add_road(Player* player, u8 edge_index);
void player_add_settlement(Player* player, u8 vertex_index);
void player_add_city(Player* player, u8 vertex_index);
void player_add_development_card(Player* player, DevelopmentCard card);

void player_use_development_card(Player* player, DevelopmentCard card);

#endif  /* PLAYER_H */
