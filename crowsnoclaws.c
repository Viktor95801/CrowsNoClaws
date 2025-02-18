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

    uint64_t bocc = 0;
    bocc |= sqr2bit(D3) | sqr2bit(E3) | sqr2bit(F5) | sqr2bit(D4);
    
    printf("*********************\nOn The Fly tests\n*********************\n");
    
    printf("Board Occupancy: ");
    print_bitboard(bocc);
    
    print_bitboard(rookAtk_OnTheFly(sqr2bit(E4), bocc));
    print_bitboard(bishopAtk_OnTheFly(sqr2bit(E4), bocc));
    printf("************\nMagic Tests\n************\n");
    
    printf("Bishop Occupancy: ");
    print_bitboard(bocc);

    print_bitboard(bishopAtkCache_get(E4, sqr2bit(D3)));
    
    print_bitboard(rookAtkCache_get(E4, sqr2bit(E3)));

    print_bitboard(bishopAtkCache_get(E3, 0ULL));
    print_bitboard(rookAtkCache_get(D3, 0ULL));


    system("pause");
    return 0;
}

