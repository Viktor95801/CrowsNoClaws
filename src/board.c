#include "board.h"
#include "constant.h"

// external
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

BBCache horseAtkCache;
BBCache kingAtkCache;

uint64_t boardPieces(Board board, bool side) {
    return board.rook[side]
        | board.knight[side]
        | board.bishop[side] 
        | board.queen[side] 
        | board.king[side] 
        | board.pawn[side];
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
    return ~(
        boardPieces(board, WHITE) | boardPieces(board, BLACK)
    );
}
uint64_t filledSqrs(Board board) {
    return (
        boardPieces(board, WHITE) | boardPieces(board, BLACK)
    );
}

/**
 * @brief Initialize a board with the starting position.
 * @param b The board to initialize.
 */
void init_board(Board *b) {
    memset(b, 0, sizeof(Board));
    
    b->side = WHITE;
    b->move_count = 1;
    b->fifty_clock = 0;
    b->enpassantSqr = -1;

    // pawns
    b->pawn[WHITE] = set_bit(A2) | set_bit(B2) | set_bit(C2) | set_bit(D2) | set_bit(E2) | set_bit(F2) | set_bit(G2) | set_bit(H2);
    b->pawn[BLACK] = set_bit(A7) | set_bit(B7) | set_bit(C7) | set_bit(D7) | set_bit(E7) | set_bit(F7) | set_bit(G7) | set_bit(H7);
    // rook
    b->rook[WHITE] = set_bit(A1) | set_bit(H1);
    b->rook[BLACK] = set_bit(A8) | set_bit(H8);
    // knight
    b->knight[WHITE] = set_bit(B1) | set_bit(G1);
    b->knight[BLACK] = set_bit(B8) | set_bit(G8);
    // bishop
    b->bishop[WHITE] = set_bit(C1) | set_bit(F1);
    b->bishop[BLACK] = set_bit(C8) | set_bit(F8);
    // queen
    b->queen[WHITE] = set_bit(D1);
    b->queen[BLACK] = set_bit(D8);
    // king
    b->king[WHITE] = set_bit(E1);
    b->king[BLACK] = set_bit(E8);
}

char get_piece(Board *b, uint8_t square) {
    if (square > 63) {
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
    return northOne(noWeOne(bbhsqr)) 
        | westOne(noWeOne(bbhsqr))
        | southOne(soWeOne(bbhsqr)) 
        | southOne(soEaOne(bbhsqr)) 
        | westOne(soWeOne(bbhsqr)) 
        | eastOne(soEaOne(bbhsqr)) 
        | northOne(noEaOne(bbhsqr)) 
        | eastOne(noEaOne(bbhsqr));
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
        uint64_t horse = set_bit(i);
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
    return northOne(bbksqr) 
        | westOne(bbksqr) 
        | southOne(bbksqr) 
        | eastOne(bbksqr) 
        | noWeOne(bbksqr)  
        | noEaOne(bbksqr) 
        | soWeOne(bbksqr)  
        | soEaOne(bbksqr);
}
BBCache bbKing_cache() {
    BBCache cache = {0};
    for (int i = 0; i < 64; i++) {
        uint64_t king = set_bit(i);
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
 * @param pawn A 64-bit bitboard with only the pawn's current square set.
 * @param empty A 64-bit bitboard with all empty squares set.
 * @param side The side of the pawn (WHITE or BLACK).
 * @return A 64-bit bitboard representing all squares the pawn can attack with
 *         a double push.
 */
uint64_t pawnDoublePushAtk(uint64_t pawn, uint64_t empty, bool side) {
    uint64_t singlePush = pawnSinglePushAtk(pawn, empty, side);
    return pawnSinglePushAtk(singlePush, empty, side) & (0x000000FF00000000 | 0x00000000FF000000);
}
uint64_t pawnAtk(Board b) {
    bool side = b.side;
    uint64_t bbp = b.pawn[side];
    uint64_t attackSquares = !side ? noWeOne(bbp) | noEaOne(bbp) :soWeOne(bbp) | soEaOne(bbp);
    //print_bitboard(attackSquares);
    return attackSquares;
}

uint64_t rookAtk_OnTheFly(uint64_t bbrsqr, uint64_t blockers) {
    uint64_t attacks = 0;
    uint64_t copy_bbrsqr = bbrsqr;
    // north
    for (int i = 0; i < 8; i++) {
        attacks |= northOne(copy_bbrsqr);
        copy_bbrsqr = northOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // south
    for (int i = 0; i < 8; i++) {
        attacks |= southOne(copy_bbrsqr);
        copy_bbrsqr = southOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // east
    for (int i = 0; i < 8; i++) {
        attacks |= eastOne(copy_bbrsqr);
        copy_bbrsqr = eastOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // west
    for (int i = 0; i < 8; i++) {
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
    for (int i = 0; i < 8; i++) {
        attacks |= noWeOne(copy_bbrsqr);
        copy_bbrsqr = noWeOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // south
    for (int i = 0; i < 8; i++) {
        attacks |= soWeOne(copy_bbrsqr);
        copy_bbrsqr = soWeOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // east
    for (int i = 0; i < 8; i++) {
        attacks |= noEaOne(copy_bbrsqr);
        copy_bbrsqr = noEaOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // west
    for (int i = 0; i < 8; i++) {
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
    for (int i = 0; i < 8; i++) {
        attacks |= northOne(copy_bbrsqr);
        copy_bbrsqr = northOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // south
    for (int i = 0; i < 8; i++) {
        attacks |= southOne(copy_bbrsqr);
        copy_bbrsqr = southOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // east
    for (int i = 0; i < 8; i++) {
        attacks |= eastOne(copy_bbrsqr);
        copy_bbrsqr = eastOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // west
    for (int i = 0; i < 8; i++) {
        attacks |= westOne(copy_bbrsqr);
        copy_bbrsqr = westOne(copy_bbrsqr);
    }
    return attacks;
}

uint64_t bishopAtk(uint64_t bbrsqr) {
    uint64_t attacks = 0;
    uint64_t copy_bbrsqr = bbrsqr;
    // north
    for (int i = 0; i < 8; i++) {
        attacks |= noWeOne(copy_bbrsqr);
        copy_bbrsqr = noWeOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // south
    for (int i = 0; i < 8; i++) {
        attacks |= soWeOne(copy_bbrsqr);
        copy_bbrsqr = soWeOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // east
    for (int i = 0; i < 8; i++) {
        attacks |= noEaOne(copy_bbrsqr);
        copy_bbrsqr = noEaOne(copy_bbrsqr);
    }
    copy_bbrsqr = bbrsqr;
    // west
    for (int i = 0; i < 8; i++) {
        attacks |= soEaOne(copy_bbrsqr);
        copy_bbrsqr = soEaOne(copy_bbrsqr);
    }
    return attacks;
}

uint64_t gen_pawnAtk(Board b) {
    return (
        pawnAtk(b) & (
            boardPieces(b, !b.side) | (b.enpassantSqr != -1 ? set_bit(b.enpassantSqr) : 0)
        )
    );
}
uint64_t gen_horseAtk(int sqr) {
    return (
        horseAtkCache.data[sqr]
    );
}
uint64_t gen_kingAtk(int sqr, uint64_t attacked_sqr) {
    return (
        kingAtkCache.data[sqr] & ~attacked_sqr
    );
}