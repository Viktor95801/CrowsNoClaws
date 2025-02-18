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

// Constant Variables

extern uint64_t rookMagics[64];
extern uint64_t bishopMagics[64];

/**
 * @brief Returns the least significant bit of a bitboard.
 *
 * @param bitboard The bitboard to get the LSB of.
 * @return The index of the least significant bit of the bitboard, -1 if the bitboard is empty.
 */
static inline int LSB(uint64_t bitboard) {
    if (!bitboard) {
        /* If the bitboard is empty return -1 */
        return -1;
    }

    int count = 0;
    bitboard = (bitboard & -bitboard) - 1;

    while (bitboard) {
        /* Increment the count for each bit we flip */
        count++;
        bitboard &= bitboard - 1;
    }
    return count;
}

static inline int COUNT_BITS(uint64_t integer) {
    int count = 0;
    while (integer) {
        count++;
        integer &= integer - 1;
    }
    return count;
}

#endif // CONSTANTS_H