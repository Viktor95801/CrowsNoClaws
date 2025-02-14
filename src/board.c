#include "board.h"
#include "constant.h"

// external
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Get a bit from a 64-bit board at a given square.
 * @param board A 64-bit board.
 * @param square The square to get the bit from.
 * @return The bit at the given square.
 */
bool get_bit(uint64_t board, uint8_t square) {
    return (board >> square) & 1;
}
/**
 * @brief Get a 64-bit bitboard with only the given square set.
 * @param square The square to set in the bitboard.
 * @return A 64-bit bitboard with only the given square set.
 */
uint64_t sqr2bit(uint8_t square) {
    return 1ULL << square;
}

/**
 * @brief Initialize a board with the starting position.
 * @param b The board to initialize.
 */
void init_board(Board *b) {
    memset(b, 0, sizeof(Board));
    
    b->side = WHITE;

    // pawns
    b->pawn[WHITE] = A2 | B2 | C2 | D2 | E2 | F2 | G2 | H2;
    b->pawn[BLACK] = A7 | B7 | C7 | D7 | E7 | F7 | G7 | H7;
    // rook
    b->rook[WHITE] = A1 | H1;
    b->rook[BLACK] = A8 | H8;
    // knight
    b->knight[WHITE] = B1 | G1;
    b->knight[BLACK] = B8 | G8;
    // bishop
    b->bishop[WHITE] = C1 | F1;
    b->bishop[BLACK] = C8 | F8;
    // queen
    b->queen[WHITE] = D1;
    b->queen[BLACK] = D8;
    // king
    b->king[WHITE] = E1;
    b->king[BLACK] = E8;
}

/**
 * @brief Get the piece at the given square.
 * @param b The board to get the piece from.
 * @param square The square to get the piece from.
 * @return The piece at the given square, or '.' if there is no piece.
 */
char get_piece(Board *b, uint8_t square) {
    if (square < 0 || square > 63) {
        fprintf(stderr, "Invalid square: %u\n", square);
        exit(1);
    }
    
    uint64_t pieces[12] = {
        b->pawn[WHITE], b->pawn[BLACK],
        b->rook[WHITE], b->rook[BLACK],
        b->knight[WHITE], b->knight[BLACK],
        b->bishop[WHITE], b->bishop[BLACK],
        b->queen[WHITE], b->queen[BLACK],
        b->king[WHITE], b->king[BLACK]
    };
    char piece_char[] = {'P', 'p', 'R', 'r', 'N', 'n', 'B', 'b', 'Q', 'q', 'K', 'k'};

    for (int i = 0; i < 12; i++) {
        if (get_bit(pieces[i], square)) {
            return piece_char[i];
        }    
    }
    return '.';
}

/**
 * @brief Print the chess board to the console.
 * 
 * This function prints the current state of the chess board
 * by iterating over each square, retrieving the piece at that
 * square, and printing its character representation. The board
 * is printed with ranks (1-8) and files (a-h).
 * 
 * @param b Pointer to the Board structure representing the chess board.
 */
void print_board(Board *b) {
    printf(" \n");
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            uint8_t square = rank * 8 + file;
            printf("%c ", get_piece(b, square));
        }
        printf("%d\n", rank + 1);
    }
    printf("a b c d e f g h\n");
}
