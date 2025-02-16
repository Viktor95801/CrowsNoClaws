#include "board.h"
#include "constant.h"
#include "move_generator.h"

// external

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

Move moveInit(char piece, uint64_t from, uint64_t to) {
    Move m = {0, 0, 0};
    m.piece = piece;
    m.from = from;
    m.to = to; 
    return m;
}

