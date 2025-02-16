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
    rookAtkMaskCache = bbMaskRook_Cache();
    kingAtkCache = bbKing_cache();
    bishopAtkMaskCache = bbMaskBishop_Cache();

    print_bitboard(rookAtkMaskCache.data[E1]);
    print_bitboard(bishopAtkMaskCache.data[E1]);
    print_bitboard(kingAtkCache.data[E1]);
    print_bitboard(horseAtkCache.data[E1]);
    print_bitboard(queenAtk(rookAtkMaskCache.data[E1],bishopAtkMaskCache.data[E1]));

    return 0;
}
