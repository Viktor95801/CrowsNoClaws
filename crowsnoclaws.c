#include "board.h"
#include "constant.h"
#include "magic/magic.h"

// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

    horseAtkCache = bbHorse_cache();
    kingAtkCache = bbKing_cache();

    initBishopAtk_cache();
    initRookAtk_cache();

    print_bitboard(rookAttacksMgc(sqr2bit(E3), E1));
    print_bitboard(bishopAttacksMgc(sqr2bit(G3), E1));
    print_bitboard(kingAtkCache.data[E1]);
    print_bitboard(horseAtkCache.data[E1]);

    uint64_t bitboard = 0xFF00FF;
    printf("%u", count_bits(bitboard));

    return 0;
}
