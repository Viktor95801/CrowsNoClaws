#include "board.h"
#include "constant.h"
#include "atk_gen/kindergarten/kindergarten.h"

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
    #ifdef __CALL_INIT__
    bishop_cacheInit();
    rook_cacheInit();
    #endif
    uint64_t bocc = 0;
    bocc |= set_bit(D3) | set_bit(E3) | set_bit(F5) | set_bit(D4) | set_bit(B7) | set_bit(H1) | set_bit(E7) | set_bit(H4);
    
    printf("*********************\nKindergarten tests\n*********************\n");

    //printf("Horizontal hash: 0x%" PRIX16 "\n", (uint16_t)hashHorizontal((bocc & rookAtk(E4)), E4));

    printf("Board Occupancy: ");
    print_bitboard(bocc);

    printf("Rook attacks: ");
    print_bitboard(gen_rookAtk(E4, bocc));

    printf("Bishop attacks: ");
    print_bitboard(gen_bishopAtk(E4, bocc));

    printf("Queen attacks: ");
    print_bitboard(gen_queenAtk(E4, bocc));

    /* printf("*********************\nOn The Fly tests\n*********************\n");
    
    printf("File index method test (E4) %d\n", file(E4));
    printf("Rank index method test (E4) %d\n", rank(E4));

    printf("\nBoard Occupancy: ");
    print_bitboard(bocc);
    
    DAtkMasks to_print = KrookAtk_OnTheFly(set_bit(E4), bocc);
    uint64_t attacks = to_print.anti_diagonal | to_print.diagonal | to_print.horizontal | to_print.vertical;
    print_bitboard(attacks);
    to_print = KbishopAtk_OnTheFly(set_bit(E4), bocc);
    attacks = to_print.anti_diagonal | to_print.diagonal | to_print.horizontal | to_print.vertical;
    print_bitboard(attacks); */
/*     printf("************\nMagic Tests\n************\n"); */
    
    /* printf("Board Occupancy: ");
    print_bitboard(bocc);

    print_bitboard(bishopAtkCache_get(E4, bocc));
    print_bitboard(rookAtkCache_get(E4, bocc));

    print_bitboard(bishopAtkCache_get(E4, 0ULL));
    print_bitboard(rookAtkCache_get(E4, 0ULL)); */

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

