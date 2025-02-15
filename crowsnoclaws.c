#include "board.h"
#include "constant.h"

// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

    horseAtkCache = bbHorse_cache();

    Board board;
    init_board(&board);
    print_board(&board);

    Board board2;
    memset(&board2, 0, sizeof(Board));
    uint64_t h_atk = horseAtkCache.data[H4];
    print_bitboard(h_atk);
    uint64_t board3;
    board3 = pawnDoublePushAtk(board.pawn[WHITE], emptySqrs(board), WHITE);
    print_bitboard(board3);
    board3 = pawnSinglePushAtk(board.pawn[WHITE], emptySqrs(board), WHITE);
    print_bitboard(board3);
    
    uint64_t k_atk = kingAtk(board.king[WHITE]);
    print_bitboard(k_atk);

    board2.rook[BLACK] = sqr2bit(E3) | sqr2bit(A4);
    print_bitboard(pawnDoublePushAtk(board.pawn[WHITE], emptySqrs(board2), WHITE));
    board3 = pawnSinglePushAtk(board.pawn[WHITE], emptySqrs(board2), WHITE);
    print_bitboard(board3);
    print_bitboard(emptySqrs(board2));
    print_bitboard(~emptySqrsS(board2, BLACK));
    print_bitboard(pawnAtk(board.pawn[WHITE], board2, WHITE));


    return 0;
}