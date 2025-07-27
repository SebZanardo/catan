#ifndef LOOKUP_H
#define LOOKUP_H

#include "board.h"

#define REGULAR_HEXES 19
#define REGULAR_EDGES 72
#define REGULAR_VERTICES 54
#define REGULAR_PORTS 9

#define EXPANSION_HEXES 30
#define EXPANSION_EDGES 109
#define EXPANSION_VERTICES 80
#define EXPANSION_PORTS 11

extern const TerrainHex regular_hexes[REGULAR_HEXES];
extern const Port regular_ports[REGULAR_PORTS];
extern const u8 regular_hex_values[REGULAR_HEXES];
extern const u8 regular_port_locations[REGULAR_PORTS][2];
extern const u8 regular_hex_to_vertices[REGULAR_HEXES][6];
extern const u8 regular_vertices_to_edges[REGULAR_VERTICES][3];
extern const u8 regular_edge_to_vertices[REGULAR_EDGES][2];

extern const TerrainHex expansion_hexes[EXPANSION_HEXES];
extern const Port expansion_ports[EXPANSION_PORTS];
extern const u8 expansion_hex_values[EXPANSION_HEXES];
extern const u8 expansion_port_locations[EXPANSION_PORTS][2];
extern const u8 expansion_hex_to_vertices[EXPANSION_HEXES][6];
extern const u8 expansion_vertices_to_edges[EXPANSION_VERTICES][3];
extern const u8 expansion_edge_to_vertices[EXPANSION_EDGES][2];

#endif  /* LOOKUP_C */
