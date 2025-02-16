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

    uint64_t bbp = sqr2bit(E2);
    board.rook[BLACK] |= sqr2bit(D3);

    uint64_t attacks = pawnAtk(bbp, board, WHITE);
    print_bitboard(attacks);

    return 0;
}