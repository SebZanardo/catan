# Technical Details

## Player Representation
Every player stores their name and player colour
```c
char name[MAX_PLAYER_NAME_LENGTH];
PlayerColour colour;
```

Keep track of number of structures placed and where they are placed on the map
```c
u8 placed_roads;
u8 placed_settlements;
u8 placed_cities;

// u8 for roads will correspond to board->edges index
u8 placed_road_positions[MAX_PLAYER_ROADS];

// u8 for settlements will correspond to board->vertices index
u8 placed_settlement_positions[MAX_PLAYER_SETTLEMENTS];

// u8 for cities will correspond to board->vertices index
u8 placed_city_positions[MAX_PLAYER_CITIES];
```

Keep track of number of each card type for easy adding and removal
```c
u8 resource_cards[RESOURCE_CARD_TYPE_COUNT];
u8 development_cards[DEVELOPMENT_CARD_TYPE_COUNT];
```

Played knight cards are the development card that needs to be tracked after use
```c
u8 knights_played;
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
Set to `MAX_PLAYER_COUNT` when empty and player index when structure is placed
```c
u8 edges[MAX_BOARD_EDGES];
u8 vertices[MAX_BOARD_VERTICES];
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

## \[REGULAR] (2-4 players)
### Edge Index Mapping
```c
               ---       ---       ---
            000   001 002   003 004   005
           |         |         |         |
          006       007       008       009
           |         |         |         |
       010   011 012   013 014   015 016   017
      |         |         |         |         |
     018       019       020       021       022
      |         |         |         |         |
  023   024 025   026 027   028 029   030 031   032
 |         |         |         |         |         |
033       034       035       036       037       038
 |         |         |         |         |         |
  039   040 041   042 043   044 045   046 047   048
      |         |         |         |         |
     049       050       051       052       053
      |         |         |         |         |
       054   055 056   057 058   059 060   061
           |         |         |         |
          062       063       064       065
           |         |         |         |
            066   067 068   069 070   071
               ---       ---       ---
```

### Vertex Index Mapping
```c
               000       001       002
             --   --   --   --   --   --
          003       004       005       006
           |         |         |         |
          007       008       009       010
        --   --   --   --   --   --   --   --
     011       012       013       014       015
      |         |         |         |         |
     016       017       018       019       020
   --   --   --   --   --   --   --   --   --   --
021       022       023       024       025       026
 |         |         |         |         |         |
027       028       029       030       031       032
   --   --   --   --   --   --   --   --   --   --
     033       034       035       036       037
      |         |         |         |         |
     038       039       040       041       042
        --   --   --   --   --   --   --   --
          043       044       045       046
           |         |         |         |
          047       048       049       050
             --   --   --   --   --   --
               051       052       053
```

### Terrain Index Mapping
```c
               ---       ---       ---
             --   --   --   --   --   --
           |         |         |         |
           |   002   |   001   |   000   |
           |         |         |         |
        --   --   --   --   --   --   --   --
      |         |         |         |         |
      |   003   |   013   |   012   |   011   |
      |         |         |         |         |
   --   --   --   --   --   --   --   --   --   --
 |         |         |         |         |         |
 |   004   |   014   |   018   |   017   |   010   |
 |         |         |         |         |         |
   --   --   --   --   --   --   --   --   --   --
      |         |         |         |         |
      |   005   |   015   |   016   |   009   |
      |         |         |         |         |
        --   --   --   --   --   --   --   --
           |         |         |         |
           |   006   |   007   |   008   |
           |         |         |         |
             --   --   --   --   --   --
               ---       ---       ---
```

### Port Index Mapping
```c
               -x-       -x-       ---
            000   --   --   001  --   --
           x         |         x         |
           |         |         |         |
           |         |         |         x
        --   --   --   --   --   --   --   002
      x         |         |         |         x
     008        |         |         |         |
      x         |         |         |         |
   --   --   --   --   --   --   --   --   --   --
 |         |         |         |         |         x
 |         |         |         |         |        003
 |         |         |         |         |         x
   --   --   --   --   --   --   --   --   --   --
      x         |         |         |         |
     007        |         |         |         |
      x         |         |         |         x
        --   --   --   --   --   --   --   004
           |         |         |         x
           |         |         |         |
           x         |         x         |
            006   --   --   005  --   --
               -x-       -x-       ---
```

## \[EXPANSION] (5-6 players)
### Edge Index Mapping
```c
                    ---       ---       ---
                 000   001 002   003 004   005
                |         |         |         |
               006       007       008       009
                |         |         |         |
            010   011 012   013 014   015 016   017
           |         |         |         |         |
          018       019       020       021       022
           |         |         |         |         |
       023   024 025   026 027   028 029   030 031   032
      |         |         |         |         |         |
     033       034       035       036       037       038
      |         |         |         |         |         |
  039   040 041   042 043   044 045   046 047   048 049   050
 |         |         |         |         |         |         |
051       052       053       054       055       056       057
 |         |         |         |         |         |         |
  058   059 060   061 062   063 064   065 066   067 068   069
      |         |         |         |         |         |
     070       071       072       073       074       075
      |         |         |         |         |         |
       076   077 078   079 080   081 082   083 084   085
           |         |         |         |         |
          086       087       088       089       090
           |         |         |         |         |
            091   092 093   094 095   096 097   098
                |         |         |         |
               099       100       101       102
                |         |         |         |
                 103   104 105   106 107   108
                    ---       ---       ---
```

### Vertex Index Mapping
```c
                    000       001       002
                  --   --   --   --   --   --
               003       004       005       006
                |         |         |         |
               007       008       009       010
             --   --   --   --   --   --   --   --
          011       012       013       014       015
           |         |         |         |         |
          016       017       018       019       020
        --   --   --   --   --   --   --   --   --   --
     021       022       023       024       025       026
      |         |         |         |         |         |
     027       028       029       030       031       032
   --   --   --   --   --   --   --   --   --   --   --   --
033       034       035       036       037       038       039
 |         |         |         |         |         |         |
040       041       042       043       044       045       046
   --   --   --   --   --   --   --   --   --   --   --   --
     047       048       049       050       051       052
      |         |         |         |         |         |
     053       054       055       056       057       058
        --   --   --   --   --   --   --   --   --   --
          059       060       061       062       063
           |         |         |         |         |
          064       065       066       067       068
             --   --   --   --   --   --   --   --
               069       070       071       072
                |         |         |         |
               073       074       075       076
                  --   --   --   --   --   --
                    077       078       079
```

### Terrain Index Mapping
```c
                    ---       ---       ---
                  --   --   --   --   --   --
                |         |         |         |
                |   002   |   001   |   000   |
                |         |         |         |
             --   --   --   --   --   --   --   --
           |         |         |         |         |
           |   003   |   017   |   016   |   015   |
           |         |         |         |         |
        --   --   --   --   --   --   --   --   --   --
      |         |         |         |         |         |
      |   004   |   018   |   026   |   025   |   014   |
      |         |         |         |         |         |
   --   --   --   --   --   --   --   --   --   --   --   --
 |         |         |         |         |         |         |
 |   005   |   019   |   027   |   029   |   024   |   013   |
 |         |         |         |         |         |         |
   --   --   --   --   --   --   --   --   --   --   --   --
      |         |         |         |         |         |
      |   006   |   020   |   028   |   023   |   012   |
      |         |         |         |         |         |
        --   --   --   --   --   --   --   --   --   --
           |         |         |         |         |
           |   007   |   021   |   022   |   011   |
           |         |         |         |         |
             --   --   --   --   --   --   --   --
                |         |         |         |
                |   008   |   009   |   010   |
                |         |         |         |
                  --   --   --   --   --   --
                    ---       ---       ---
```

### Port Index Mapping
```c
                    -x-       -x-       ---
                 000   --   --   001  --   --
                x         |         x         |
                |         |         |         |
                |         |         |         x
             --   --   --   --   --   --   --   002
           |         |         |         |         x
           |         |         |         |         |
           |         |         |         |         |
        --   --   --   --   --   --   --   --   --   --
      x         |         |         |         |         |
     010        |         |         |         |         |
      x         |         |         |         |         |
   --   --   --   --   --   --   --   --   --   --   --   --
 |         |         |         |         |         |         x
 |         |         |         |         |         |        003
 x         |         |         |         |         |         x
  009   --   --   --   --   --   --   --   --   --   --   --
      x         |         |         |         |         |
      |         |         |         |         |         |
      |         |         |         |         |         x
        --   --   --   --   --   --   --   --   --   004
           x         |         |         |         x
          008        |         |         |         |
           x         |         |         |         |
             --   --   --   --   --   --   --   --
                |         |         |         x
                |         |         |        005
                x         |         x         x
                 007   --   --   006  --   --
                    -x-       -x-       ---
```
