#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

// Helper

 uint64_t eastOne (uint64_t b);
 uint64_t noEaOne (uint64_t b);
 uint64_t soEaOne (uint64_t b);
 uint64_t westOne (uint64_t b);
 uint64_t soWeOne (uint64_t b);
 uint64_t noWeOne (uint64_t b);
 uint64_t northOne (uint64_t b);
 uint64_t southOne (uint64_t b);


// Constants

#define WHITE 0
#define BLACK 1

#define PAWN 100
#define KNIGHT 350
#define BISHOP 320
#define ROOK 500
#define QUEEN 900
#define KING 90000

#define LSB 1
#define MSB 1ULL << 63

#endif // CONSTANTS_H