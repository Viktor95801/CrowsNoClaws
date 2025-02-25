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

enum m_flags {
    NORMAL, CAPTURE, ENPASSANT, PROMOTION,
    CASTLE_KW, CASTLE_QW, CASTLE_KB, CASTLE_QB,
    PROMO_Q, PROMO_R, PROMO_B, PROMO_H,
};

#define MAX_MOVES 320

#define WHITE 0
#define BLACK 1

#define PAWN 100
#define HORSE 350
#define BISHOP 320
#define ROOK 500
#define QUEEN 900
#define KING 90000

#define LOSS -1000000
#define DRAW 0
#define WIN 10000000

// Constant Variables

extern int COUNT_BITS(uint64_t integer);

/**
 * @brief Returns the least significant bit of a bitboard.
 *
 * @param bitboard The bitboard to get the LSB of.
 * @return The index of the least significant bit of the bitboard, -1 if the bitboard is empty.
 */
extern int LSB(uint64_t bitboard);

#endif // CONSTANTS_H