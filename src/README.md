# Technical Details

## Game Representation
```
NOTE: The current Game representation is subject to change as it will need
to store a state for the phase of the current turn.
```

Gametype can be `REGULAR` (2-4 players) or `EXPANSION` (5-6 players)
```c
GameType game_type;
```

Store board and cards
```c
Board board;
Cards cards;
```

Store players in order as they join. If someone leaves then shift list down
```c
Player players[MAX_PLAYERS];
u8 player_count;
```

Randomise playing order at the start of the game. Store references
```c
u8 player_order[MAX_PLAYERS];
Player* active_player;
u8 player_turn;
```

## Player Representation
Every player stores their name and player colour

```c
char name[MAX_PLAYER_NAME_LENGTH];
PlayerColour colour;
```

Keep track of number of structures placed
```c
u8 placed_roads;
u8 placed_settlements;
u8 placed_cities;
```

Keep track of placements, available and connected with O(1) lookup
```c
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
```

Keep track of number of each card type for easy adding and removal and tracking
```c
u8 resource_cards[RESOURCE_CARD_TYPE_COUNT];
u8 development_cards_held[DEVELOPMENT_CARD_TYPE_COUNT];
u8 development_cards_played[DEVELOPMENT_CARD_TYPE_COUNT];
```

## Cards Representation
Only count remaining needs to be tracked for easy adding and removal
```c
u8 resource_cards[RESOURCE_CARD_TYPE_COUNT];
```

Development cards shuffled _fairly_ at the start of the game so set seed works
```c
DevelopmentCard development_cards[MAX_DEVELOPMENT_CARDS];
u8 development_card_count;
```

## Board Representation
To keep track of length of arrays for various things
```c
u8 edges_count;
u8 vertices_count;
u8 hex_count;
u8 port_count;
```

Store how the board has been setup for this game
```c
TerrainHex hexes[MAX_BOARD_HEXES];
u8 hex_values[MAX_BOARD_HEXES];  // Dice roll needed to collect
Port ports[MAX_BOARD_PORTS];
```

Track the robber position
```c
u8 robber_position;
u8 robber_moved_by;  // Store what player moved the robber last
```
