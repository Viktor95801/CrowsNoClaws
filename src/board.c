#include "board.h"
#include "constant.h"

// external
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

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
 * @brief Return a 64-bit bitboard with all squares set that are empty.
 * 
 * This function takes a Board structure and returns a 64-bit bitboard with all
 * squares set that are empty (i.e. not occupied by any piece) on the board.
 * 
 * @param board The Board structure to calculate the empty squares for.
 * @return A 64-bit bitboard with all squares set that are empty.
 */
uint64_t emptySqrs(Board board) {
    uint64_t out = 0;
    out |= board.pawn[WHITE]   | board.pawn[BLACK];
    out |= board.rook[WHITE]   | board.rook[BLACK];
    out |= board.knight[WHITE] | board.knight[BLACK];
    out |= board.bishop[WHITE] | board.bishop[BLACK];
    out |= board.queen[WHITE]  | board.queen[BLACK];
    out |= board.king[WHITE]   | board.king[BLACK];
    return ~out;
}
uint64_t filledSqrs(Board board) {
    uint64_t out = 0;
    out |= board.pawn[WHITE]   | board.pawn[BLACK];
    out |= board.rook[WHITE]   | board.rook[BLACK];
    out |= board.knight[WHITE] | board.knight[BLACK];
    out |= board.bishop[WHITE] | board.bishop[BLACK];
    out |= board.queen[WHITE]  | board.queen[BLACK];
    out |= board.king[WHITE]   | board.king[BLACK];
    return out;
}

/**
 * @brief Initialize a board with the starting position.
 * @param b The board to initialize.
 */
void init_board(Board *b) {
    memset(b, 0, sizeof(Board));
    
    b->side = WHITE;

    // pawns
    b->pawn[WHITE] = sqr2bit(A2) | sqr2bit(B2) | sqr2bit(C2) | sqr2bit(D2) | sqr2bit(E2) | sqr2bit(F2) | sqr2bit(G2) | sqr2bit(H2);
    b->pawn[BLACK] = sqr2bit(A7) | sqr2bit(B7) | sqr2bit(C7) | sqr2bit(D7) | sqr2bit(E7) | sqr2bit(F7) | sqr2bit(G7) | sqr2bit(H7);
    // rook
    b->rook[WHITE] = sqr2bit(A1) | sqr2bit(H1);
    b->rook[BLACK] = sqr2bit(A8) | sqr2bit(H8);
    // knight
    b->knight[WHITE] = sqr2bit(B1) | sqr2bit(G1);
    b->knight[BLACK] = sqr2bit(B8) | sqr2bit(G8);
    // bishop
    b->bishop[WHITE] = sqr2bit(C1) | sqr2bit(F1);
    b->bishop[BLACK] = sqr2bit(C8) | sqr2bit(F8);
    // queen
    b->queen[WHITE] = sqr2bit(D1);
    b->queen[BLACK] = sqr2bit(D8);
    // king
    b->king[WHITE] = sqr2bit(E1);
    b->king[BLACK] = sqr2bit(E8);
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

/**
 * @brief Print a 64-bit bitboard to the console.
 *
 * This function takes a 64-bit bitboard and prints it to the console
 * in a human-readable format. The bitboard is printed with ranks
 * (1-8) and files (a-h). The bit at each square is represented as
 * either 0 or 1.
 */
void print_bitboard(uint64_t board) {
    printf(" \n");
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            uint8_t square = rank * 8 + file;
            printf("%d ", get_bit(board, square));
        }
        printf("\"%d\"\n", rank + 1);
    }
    printf("a b c d e f g h\n");
    printf("\n\tbitboard: 0x%" PRIx64 " \n", board);  // Use PRIx64 for hexadecimal output
}


uint64_t horseAtk(uint64_t bbhsqr) {
    return northOne(noWeOne(bbhsqr)) | westOne(noWeOne(bbhsqr)) | southOne(soWeOne(bbhsqr)) | southOne(soEaOne(bbhsqr)) | westOne(soWeOne(bbhsqr)) | eastOne(soEaOne(bbhsqr)) | northOne(noEaOne(bbhsqr)) | eastOne(noEaOne(bbhsqr));
}
/**
 * @brief Compute and return a pre-computed cache of all the attacks of a horse at each square on the board.
 * 
 * This function pre-computes all of the attacks of a horse at each square on the board and returns a pre-computed
 * cache of all of these attacks. This cache can then be queried to retrieve the set of squares that a horse at a given
 * square can attack. This cache is computed by calling the horseAtk() function on each square on the board, and storing
 * the resulting set of squares that the horse can attack in the cache.
 * 
 * @return A pre-computed cache of all of the attacks of a horse at each square on the board.
 */
BBCache bbHorse_cache() {
    BBCache cache = {0};
    for (int i = 0; i < 64; i++) {
        uint64_t horse = sqr2bit(i);
        cache.data[i] = horseAtk(horse);
    }
    return cache;
}

/**
 * @brief Calculate the attack bitboard for a king on a given square.
 * 
 * This function computes the set of squares that a king can attack from its
 * current position on the board. It takes into account all possible king moves,
 * which include moving one square in any direction (north, south, east, west, 
 * northeast, northwest, southeast, southwest).
 * 
 * @param bbksqr A 64-bit bitboard with only the king's current square set.
 * @return A 64-bit bitboard representing all squares the king can attack.
 */
uint64_t kingAtk(uint64_t bbksqr) {
    return northOne(bbksqr) | westOne(bbksqr) | southOne(bbksqr) | eastOne(bbksqr) |
           noWeOne(bbksqr)  | noEaOne(bbksqr) | soWeOne(bbksqr)  | soEaOne(bbksqr);
}
BBCache bbKing_cache() {
    BBCache cache = {0};
    for (int i = 0; i < 64; i++) {
        uint64_t king = sqr2bit(i);
        cache.data[i] = kingAtk(king);
    }
    return cache;
}

/**
 * @brief Compute and return the set of squares that a pawn at a given square
 *        can attack with a single push.
 *
 * This function takes a 64-bit bitboard with only the pawn's current square set
 * and a 64-bit bitboard with all empty squares set, and returns a 64-bit
 * bitboard representing all squares the pawn can attack with a single push.
 *
 * @param bbpsqr A 64-bit bitboard with only the pawn's current square set.
 * @param bbemptsqr A 64-bit bitboard with all empty squares set.
 * @param side The side of the pawn (WHITE or BLACK).
 * @return A 64-bit bitboard representing all squares the pawn can attack.
 */
uint64_t pawnSinglePushAtk(uint64_t bbpsqr, uint64_t bbemptsqr, bool side) {
    return ((bbpsqr << 8) >> (side << 4)) & bbemptsqr;
}
/**
 * @brief Compute and return the set of squares that a pawn at a given square
 *        can attack with a double push.
 *
 * This function takes a 64-bit bitboard with only the pawn's current square set,
 * a 64-bit bitboard with all empty squares set, and the side of the pawn, and
 * returns a 64-bit bitboard representing all squares the pawn can attack with a
 * double push from its initial rank. The function considers whether the pawn is
 * on its starting rank and whether the destination squares are unoccupied.
 *
 * @param bbpsqr A 64-bit bitboard with only the pawn's current square set.
 * @param bbemptsqr A 64-bit bitboard with all empty squares set.
 * @param side The side of the pawn (WHITE or BLACK).
 * @return A 64-bit bitboard representing all squares the pawn can attack with
 *         a double push.
 */
uint64_t pawnDoublePushAtk(uint64_t bbpsqr, uint64_t bbemptsqr, bool side) {
    uint64_t rank = 0x000000FF00000000 | 0x00000000FF000000;
    bbpsqr = pawnSinglePushAtk(bbpsqr, bbemptsqr, side);
    uint64_t result = pawnSinglePushAtk(bbpsqr, bbemptsqr, side) & rank;
    return result;
}
uint64_t pawnAtk(uint64_t bbp, Board b, bool side) {
    uint64_t attackSquares = !side ? noWeOne(bbp) | noEaOne(bbp) :soWeOne(bbp) | soEaOne(bbp);
    print_bitboard(attackSquares);
    uint64_t other_board = b.pawn[!side] | b.rook[!side] | b.knight[!side] | b.bishop[!side] | b.queen[!side] | b.king[!side];
    uint64_t result = attackSquares & other_board;
    return result;
}

uint64_t rookAtk_OnTheFly(uint64_t bbrsqr, uint64_t blockers) {
    uint64_t attacks = 0;
    uint64_t copy_bbrsqr = bbrsqr;
    // north
    for (int i = 0; i < 9; i++) {
        attacks |= northOne(copy_bbrsqr);
        copy_bbrsqr = northOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // south
    for (int i = 0; i < 9; i++) {
        attacks |= southOne(copy_bbrsqr);
        copy_bbrsqr = southOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // east
    for (int i = 0; i < 9; i++) {
        attacks |= eastOne(copy_bbrsqr);
        copy_bbrsqr = eastOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // west
    for (int i = 0; i < 9; i++) {
        attacks |= westOne(copy_bbrsqr);
        copy_bbrsqr = westOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    return attacks;
}

uint64_t bishopAtk_OnTheFly(uint64_t bbrsqr, uint64_t blockers) {
    uint64_t attacks = 0;
    uint64_t copy_bbrsqr = bbrsqr;
    // north
    for (int i = 0; i < 9; i++) {
        attacks |= noWeOne(copy_bbrsqr);
        copy_bbrsqr = noWeOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // south
    for (int i = 0; i < 9; i++) {
        attacks |= soWeOne(copy_bbrsqr);
        copy_bbrsqr = soWeOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // east
    for (int i = 0; i < 9; i++) {
        attacks |= noEaOne(copy_bbrsqr);
        copy_bbrsqr = noEaOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // west
    for (int i = 0; i < 9; i++) {
        attacks |= soEaOne(copy_bbrsqr);
        copy_bbrsqr = soEaOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    return attacks;
}

uint64_t rookAtk(uint64_t bbrsqr) {
    uint64_t attacks = 0;
    uint64_t copy_bbrsqr = bbrsqr;
    // north
    for (int i = 0; i < 9; i++) {
        attacks |= northOne(copy_bbrsqr);
        copy_bbrsqr = northOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // south
    for (int i = 0; i < 9; i++) {
        attacks |= southOne(copy_bbrsqr);
        copy_bbrsqr = southOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // east
    for (int i = 0; i < 9; i++) {
        attacks |= eastOne(copy_bbrsqr);
        copy_bbrsqr = eastOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // west
    for (int i = 0; i < 9; i++) {
        attacks |= westOne(copy_bbrsqr);
        copy_bbrsqr = westOne(copy_bbrsqr);
    }
    return attacks;
}

uint64_t bishopAtk(uint64_t bbrsqr) {
    uint64_t attacks = 0;
    uint64_t copy_bbrsqr = bbrsqr;
    // north
    for (int i = 0; i < 9; i++) {
        attacks |= noWeOne(copy_bbrsqr);
        copy_bbrsqr = noWeOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // south
    for (int i = 0; i < 9; i++) {
        attacks |= soWeOne(copy_bbrsqr);
        copy_bbrsqr = soWeOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // east
    for (int i = 0; i < 9; i++) {
        attacks |= noEaOne(copy_bbrsqr);
        copy_bbrsqr = noEaOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // west
    for (int i = 0; i < 9; i++) {
        attacks |= soEaOne(copy_bbrsqr);
        copy_bbrsqr = soEaOne(copy_bbrsqr);
    }
    return attacks;
}
