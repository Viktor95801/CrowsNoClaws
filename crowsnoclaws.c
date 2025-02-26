#include "board.h"
#include "constants.h"
#include "atk_gen/kindergarten/kindergarten.h"

// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <assert.h>

int main(/* int argc, char *argv[] */) {
    Board b;
    init_board(&b);
    b.enpass_sqr = E2;
    print_board(&b);
    Board b2 = {.white = {0}, .black = {0}, .side = WHITE, .castling_rights = 0x0, .enpass_sqr = E2, .fifty_clock = 0, .fullmove_clock = 0};
    b2 = init_FENboard("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq e5 1 2 ");
    print_board(&b2);
    printf("enpass_sqr: %d E5: %d\n", b2.enpass_sqr, E5);
    assert(b2.enpass_sqr == E5);
    system("pause");
    return 0;
}

