#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t U64;

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

enum pieceIndex {
    PAWN,
    ROOK,
    HORSE,
    BISHOP,
    QUEEN,
    KING,
};
typedef struct {
    U64 white[6];
    U64 black[6];

    bool side;
    uint8_t enpass_sqr;
    uint8_t castling_rights;
    uint8_t fifty_clock;
    uint8_t fullmove_clock;
} Board;
static inline bool board_get_castlingRight(const Board *board, bool side, bool queen_side) {
    return ((board->castling_rights >> (side * 2 + queen_side)) & 1);
}
static inline void board_set_castlingRight(Board *board, bool side, bool queen_side) {
    board->castling_rights |= (uint8_t)1 << (side * 2 + queen_side);
}

static inline void set_bit(U64 *board, int index) {
    *board |= (U64)1 << index;
}
static inline bool get_bit(const U64 *board, int index) {
    return *board & (U64)1 << index;
}
static inline void clear_bit(U64 *board, int index) {
    *board ^= (U64)1 << index;
}
static inline bool pop_bit(U64 *board, int index) {
    *board ^= (U64)1 << index;
    return get_bit(board, index);
}
static inline U64 LSB(const U64 *board) {
    return *board & -(*board);
}

void init_board(Board *board);
Board init_FENboard(const char *FEN);
void print_board(const Board *board);
void print_bitboard(const U64 *board);

U64 rook_mask(int sqr);
U64 bishop_mask(int sqr);
U64 king_mask(int sqr);
U64 horse_mask(int sqr);

U64 gen_horseAtk(Board *board, int sqr);
