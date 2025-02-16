#include "board.h"
#include "constant.h"
#include "magic/magic_interface.h"


// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

    horseAtkCache = bbHorse_cache();
    kingAtkCache = bbKing_cache();

    print_bitboard(rookAtk(sqr2bit(E1), sqr2bit(E3)));
    print_bitboard(bishopAtk(sqr2bit(E1), sqr2bit(G3)));
    print_bitboard(kingAtkCache.data[E1]);
    print_bitboard(horseAtkCache.data[E1]);

    return 0;
}
