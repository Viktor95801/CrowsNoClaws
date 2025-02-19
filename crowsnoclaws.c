#include "board.h"
#include "constant.h"
#include "magic/magic.h"

// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

int main(/* int argc, char *argv[] */) {
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
    
    printf("Board Occupancy: ");
    print_bitboard(bocc);

    print_bitboard(bishopAtkCache_get(E4, bocc));
    print_bitboard(rookAtkCache_get(E4, bocc));

    print_bitboard(bishopAtkCache_get(E4, 0ULL));
    print_bitboard(rookAtkCache_get(E4, 0ULL));

    /* // bishop

    int count = 0;

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 512; j++) {
            if (!cacheBishopMoves[i][j])
                count++;
//            else
//                print_bitboard(cacheBishopMoves[i][j]);
        }
        printf("0 count on square %d: %d\n", i, count);
        count = 0;
    }

    // rook
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 4096; j++) {
            if (!cacheRookMoves[i][j])
                count++;
//            else
//                print_bitboard(cacheRookMoves[i][j]);
        }
        printf("0 count on square %d: %d\n", i, count);
        count = 0;
    }
 */
    system("pause");
    return 0;
}

