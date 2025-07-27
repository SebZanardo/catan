#ifndef CORE_H
#define CORE_H

/*#include <stdio.h>*/
#include <stdlib.h>  // for rand(), srand()
#include <assert.h>  // for assert(), static_assert()
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "raylib.h"
/*#include "raymath.h"*/
/*#include "rlgl.h"*/

///////////////////////////////////////////////////////////////////////////////

typedef int8_t   i8 ;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef uint8_t  u8 ;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

///////////////////////////////////////////////////////////////////////////////

// This is where the heavenly macro magic lives

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define RANDOM_INDEX(max) ((u16) (rand() % ((max) + 1)))

// Fair random in-place shuffle
// https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
#define DEFINE_SHUFFLE_FUNCTION(type, name, size)                              \
    static inline void name(type (*arr)[size], u16 count) {                    \
        assert(count <= size);                                                 \
        if (count == 0) return;                                                \
        for (u16 i = count - 1; i > 0; --i) {                                  \
            u16 j = RANDOM_INDEX(i);                                           \
            type tmp = (*arr)[i];                                              \
            (*arr)[i] = (*arr)[j];                                             \
            (*arr)[j] = tmp;                                                   \
        }                                                                      \
    }

///////////////////////////////////////////////////////////////////////////////

#define MAX_PLAYERS 6

typedef enum {
    GAME_REGULAR,    // 2-4 players
    GAME_EXPANSION,  // 5-6 players
} GameType;

#endif  /* CORE_H */
