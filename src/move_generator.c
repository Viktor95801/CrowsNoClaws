#include "board.h"
#include "constant.h"
#include "move_generator.h"
#include "../atk_gen/kindergarten/kindergarten.h"

// external

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int gen_Moves(Move** moves, Board* b) {
    int movesCount = 0;

    // iterate trough board
    for (int sqr = 0; sqr < 64; sqr++) {
        char piece = get_piece(b, sqr);

        if (piece == '.') {
            continue;
        }
    }

    return movesCount;
}