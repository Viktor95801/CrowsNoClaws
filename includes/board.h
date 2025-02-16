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

bool get_bit(uint64_t board, uint8_t square);
uint64_t sqr2bit(uint8_t square);
uint64_t emptySqrs(Board board);
uint64_t filledSqrs(Board board);

// (Pre)-Cache
typedef struct {
    uint64_t data[64];
} BBCache;

BBCache bbHorse_cache();

uint64_t kingAtk(uint64_t bbksqr);

uint64_t pawnSinglePushAtk(uint64_t bbpsqr, uint64_t bbemptsqr, bool side);
uint64_t pawnDoublePushAtk(uint64_t bbpsqr, uint64_t bbemptsqr, bool side);
uint64_t pawnAtk(uint64_t bbp, Board b, bool side);

BBCache horseAtkCache;

#endif // BOARD_H
