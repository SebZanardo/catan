# .CATAN file format
Custom designed for this project!
  
`NOTE: Pre-launch the format may be changed`
  
This file format was designed to be:
* Human readable/editable --> although using map editor is recommended
* Simply parsed in sequential order from top to bottom
* Scalable to allow for small, medium and large custom maps
* Customisability to allow for whacky games whilst obeying catan rules
  
Alongside the game we will supplying players with a level editor to create,
modify and share custom maps in the `.catan` file format.
  
This file documents the expected type of each piece of data in the `.catan`
file format. We have also included the validity checks our map parser performs
to ensure the supplied map is game ready.

## Comments
Any line with first character as `#` is ignored by the parser

## Recommended max player count
### list(u8)
Description:  
Minimum player count (inclusive), maximum player count (inclusive)
```
min_players max_players
```
Example:  
```
2 4
```
Validity checks:  
* number of columns == 2
* `min_players` <= `max_players`

## Recommended victory points to win
### u8
Description:  
A count for how many victory points are needed for a player to win the game
```
points_to_win
```
Example:  
```
10
```
Validity checks:  
* number of columns == 1

## Max building counts
### list(u8)
Description:  
Specifies for each player the number of roads, settlements and cities they have
available to place on the board.
```
max_roads max_settlements max_cities
```
Example:  
```
15 5 4
```
Validity checks:  
* number of columns == 3

## Free starting placements count
### list(u8)
Description:  
The number free starting placements per players get is described here. The
second number is how many of their turns starting from the end they get
resources for when they place a settlement or city
```
free_placements resources_for_last_turns
```
Example:  
```
2 1
```
Validity checks:  
* number of columns == 2
* `free_placements` >= `resources_for_last_turns`

## Free starting placements map
### list(list(u8))
Description:  
Each free placement turn that the players get and what they can place. Roads
are placed after settlements or cities and must be connected to one of the
settlements or cities that was placed, or if only road on turn then can connect
to any previously placed structures. Players always place in forward order
then reverse order alternating until their free placements are finished.
```
free_roads free_settlements free_cities
```
Example:  
```
1 1 0
1 1 0
```
Validity checks:  
* number of columns == 3
* number of rows == `free_placements`
* sum(`free_roads`) <= `max roads`
* sum(`free_settlements`) <= `max settlements`
* sum(`free_cities`) <= `max cities`

## Bank resources
### list(u16)
Description:  
These are counts of how many of each resource are stored in the bank.
```
brick wood wool wheat ore
```
Example:  
```
19 19 19 19 19
```
Validity checks:  
* number of columns == 5

## Development cards
### list(u16)
Description:  
These are the counts of how many of each development card are shuffled into the
starting development card deck.
```
monopoly road_building invention knight victory_point
```
Example:  
```
2 2 2 14 5
```
Validity checks:  
* number of columns == 5

## Board dimensions
### list(u8)
Description:  
All boards are stored in part as a 2D matrix to allow for ease of rendering and
generating lookup tables for hex, edge and vertex mappings. 
```
width height
```
Example:  
```
5 5
```
Validity checks:  
* number of columns == 2
* `width` > 0
* `height` > 0

## Hex type map
### list(list(u8))
Description:  
For each hex on the board specify its type
```
0       water
1       any         (randomly picked from hex type pool)
2       hill        (brick)
3       forest      (wood)
4       pasture     (wool)
5       field       (wheat)
6       mountain    (ore)
7       desert
```
Example:  
```
0 7 5 4 0
2 4 3 6 0
3 5 2 3 4
5 2 6 3 0
0 6 5 4 0
```
Validity checks:  
* number of columns == `width`
* number of rows == `height`
* each value < 8

## Hex type pool
### list(u8)
Description:  
The count of each hex type in the pool to assign to hexes on the board. All
type specified hexes are removed from the pool first then remaining any hexes
are randomly selected from what is left over in the pool.
```
brick wood wool wheat ore desert
```
Example:  
```
3 4 4 4 3 1
```
Validity checks:  
* number of columns == 6
* sum(all values) >= number of non-zero values in hex type map
* value >= number of value in hex type map

## Hex value map
### list(list(u8))
Description:  
Same as the hex types but for hex values. Water tiles should always be 0. Any
fixed deserts must be 0. Any set values are removed from pool first then any
values are randomly picked from the remaining values.
```
0       unrollable 
1       random from hex value pool
2-12    this is value of the hex (all possible rolls of 2 six sided dice)
```
Example:  
```
0 0 8 11 0
6 3 4 9 0
10 5 12 11 5
2 9 4 8 0
0 6 3 10 0
```
Validity checks:  
* number of columns == `width`
* number of rows == `height`
* each value <= 12
* any water or fixed deserts must == 0

## Hex value pool
### list(u8)
Description:  
The number of each hex value that can appear. 7 should be left to zero unless
you want to collect resources before robber is activated for some maps. This
should match up to the value map supplied before this. First all set values are
removed from the pool then any values are picked randomly from the remaining
values.
```
0 2 3 4 5 6 7 8 9 10 11 12
```
Example:  
```
1 1 2 2 2 2 0 2 2 2 2 1
```
Validity checks:  
* number of columns == 12
* sum(all values) >= number of non-zero in hex value map
* value >= number of value in hex value map

## Port type map
### list(u8)
Description:  
The 
```
0       any (will pick from port type pool)
1       three for one port
2       brick port
3       wood port
4       wool port
5       wheat port
6       ore port
```
Example:  
```
1 4 1 1 2 3 1 5 6
```
Validity checks:  
* each value < 7
* sum(all values) >= number of non-zero in port type map
* value >= number of value in port type map

## Port type pool
### list(u8)
Description:  
The count of each port type in the pool to assign to ports on the board. All
type specified ports are removed from the pool first then remaining any ports
are randomly selected from what is left over in the pool.
```
empty three brick wood wool wheat ore
```
Example:  
```
0 4 1 1 1 1
```
Validity checks:  
* number of columns == 6
* sum(all values) >= number of non-zero in port type map
* value >= number of value in port type map

## Port vertices map
### list(u16)
Description:  
This is a list of pairs for where all ports reside on the board. Each port
must be connected to two vertices. The vertices are indexed using the grid
format specified in `src/README.md`.
```
port1vertex1 port1vertex2 port2vertex1 port2vertex2 ...
```
Example:  
```
1 6 2 8 15 21 34 40 51 57 62 67 60 66 41 47 17 23
```
Validity checks:  
* number of pairs == length(port type map)
* vertex <= within board vertices

