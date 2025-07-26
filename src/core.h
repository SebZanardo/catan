#ifndef CORE_H
#define CORE_H

#include <stdio.h>
/*#include <stdlib.h>*/
#include <stdint.h>
#include <stdbool.h>
#include "raylib.h"
/*#include "raymath.h"*/
/*#include "rlgl.h"*/

typedef int8_t   i8 ;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef uint8_t  u8 ;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define MAX_PLAYERS 6

typedef enum {
	GAME_NONE,
	GAME_REGULAR,    // 2-4 players
	GAME_EXPANSION,  // 5-6 players
} GameType;

#endif  /* CORE_H */
