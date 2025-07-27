#ifndef PLAYER_H
#define PLAYER_H

#include "core.h"
#include "board.h"
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

// TODO: Once final, order struct properly so largest elements at top
typedef struct {
	PlayerColour colour;
	char name[MAX_PLAYER_NAME_LENGTH];

	// TODO: Combine these and use bitmasking /////////////////////////////////
	// Pretty sure this data layout covers every case efficiently
	// But program rest of logic before converting to bitmasking

	// For every road location true or false if possible to place there
	bool available_edge_positions[MAX_BOARD_EDGES];

	// True or false if we have a road placed at specific index
	bool placed_road_positions[MAX_BOARD_EDGES];

	// For every settlemenet location true or false if possible to place there
	bool available_vertex_positions[MAX_BOARD_VERTICES];

	// True or false if we have a settlement placed at specific index
	bool placed_settlement_positions[MAX_BOARD_VERTICES];

	// True or false if we have a settlement placed at specific index
	bool placed_city_positions[MAX_BOARD_VERTICES];

	///////////////////////////////////////////////////////////////////////////
	
	u8 victory_points;

	u8 resource_cards[RESOURCE_CARD_TYPE_COUNT];
	u8 development_cards_held[DEVELOPMENT_CARD_TYPE_COUNT];
	u8 development_cards_played[DEVELOPMENT_CARD_TYPE_COUNT];

	u8 placed_roads;
	u8 placed_settlements;
	u8 placed_cities;
} Player;

void player_setup(Player* player);

void player_collect_resource(Player* player, ResourceCard resource);
void player_spend_resource(Player* player, ResourceCard resource);

void player_build_road(Player* player, u8 edge_index);
void player_build_settlement(Player* player, u8 vertex_index);
void player_build_city(Player* player, u8 vertex_index);
void player_build_development_card(Player* player, DevelopmentCard card);

void player_spend_development_card(Player* player, DevelopmentCard card);

#endif  /* PLAYER_H */
