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

    printf("************\nMagic Tests\n************\n");
    print_bitboard(bishopAtkCache_get(E4, sqr2bit(D3)));
    print_bitboard(rookAtkCache_get(E4, sqr2bit(E3)));

    print_bitboard(bishopAtkCache_get(E3, 0ULL));
    print_bitboard(rookAtkCache_get(D3, 0ULL));

    return 0;
}

