#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdbool.h>

enum {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8
};

typedef struct {
    uint64_t pawn[2];
    uint64_t rook[2];
    uint64_t knight[2];
    uint64_t bishop[2];
    uint64_t queen[2];
    uint64_t king[2];

    bool side;
} Board;

void init_board(Board *board);
void print_board(Board *board);
void print_bitboard(uint64_t board);

/**
 * @brief Get a bit from a 64-bit board at a given square.
 * @param board A 64-bit board.
 * @param square The square to get the bit from.
 * @return The bit at the given square.
 */
static inline bool get_bit(uint64_t board, uint8_t square) {
    return (board >> square) & 1;
}
/**
 * @brief Get a 64-bit bitboard with only the given square set.
 * @param square The square to set in the bitboard.
 * @return A 64-bit bitboard with only the given square set.
 */
static inline uint64_t set_bit(uint8_t square) {
    return 1ULL << square;
}
/**
 * @brief Remove a bit from a 64-bit board at a given square.
 * 
 * This function toggles the bit at the specified square in the given 64-bit board,
 * effectively removing the bit if it was set.
 * 
 * @param board A 64-bit board.
 * @param square The square to toggle the bit.
 * @return Wheter the bit was set or not.
 */

static inline bool pop_bit(uint64_t* board, uint8_t square) {
    *board = *board ^ (1ULL << square);
    return get_bit(*board, square);
}

uint64_t boardPieces(Board board, bool side);
uint64_t emptySqrs(Board board);
uint64_t filledSqrs(Board board);

// (Pre)-Cache
typedef struct {
    uint64_t data[64];
} BBCache;

BBCache bbHorse_cache();
BBCache bbKing_cache();

uint64_t kingAtk(uint64_t bbksqr);
uint64_t rookAtk_OnTheFly(uint64_t bbrsqr, uint64_t blockers);
uint64_t bishopAtk_OnTheFly(uint64_t bbrsqr, uint64_t blockers);
uint64_t bishopAtk(uint64_t bbrsqr);
uint64_t rookAtk(uint64_t bbrsqr);

uint64_t pawnSinglePushAtk(uint64_t bbpsqr, uint64_t bbemptsqr, bool side);
uint64_t pawnDoublePushAtk(uint64_t bbpsqr, uint64_t bbemptsqr, bool side);
uint64_t pawnAtk(Board b);

uint64_t gen_pawnAtk(Board b);
uint64_t gen_horseAtk(int sqr);
uint64_t gen_kingAtk(int sqr, uint64_t attacked_sqr);

extern BBCache horseAtkCache;
extern BBCache kingAtkCache;

#endif // BOARD_H
