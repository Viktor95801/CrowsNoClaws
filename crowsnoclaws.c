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
    #ifdef CALL_INIT
    bishop_cacheInit();
    rook_cacheInit();
    #endif
    uint64_t bocc = 0;

    Board b;
    init_board(&b);

    printf("*********************\n   Pop Bit Test   \n*********************\n");
    bocc = set_bit(E4)
        | set_bit(E5);
    print_bitboard(bocc);
    pop_bit(&bocc, E4);
    print_bitboard(bocc);


    bocc = 0;
    bocc |= set_bit(D3) | set_bit(E3) | set_bit(F5) | set_bit(D4) | set_bit(B7) | set_bit(H1) | set_bit(E7) | set_bit(H4) | set_bit(D6);
    printf("*********************\n    Piece Move    \n*********************\n");

    printf("Board Occupancy: ");
    print_bitboard(bocc);

    printf("King attacks: ");
    print_bitboard(gen_kingAtk(E4, bocc));

    printf("Knight attacks: ");
    print_bitboard(gen_horseAtk(E4));

    printf("Pawn Atks: ");
    b.queen[BLACK] = set_bit(A3);
    print_board(&b);
    print_bitboard(gen_pawnAtk(b));
    printf("*********************\nKindergarten tests\n*********************\n");

    printf("Board Occupancy: ");
    print_bitboard(bocc);

    printf("Rook attacks: ");
    print_bitboard(gen_rookAtk(E4, bocc));

    printf("Bishop attacks: ");
    print_bitboard(gen_bishopAtk(E4, bocc));

    printf("Queen attacks: ");
    print_bitboard(gen_queenAtk(E4, bocc));
    
    system("pause");
    return 0;
}

