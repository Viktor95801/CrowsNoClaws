#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "board.h"

#include <stdint.h>
#include <stdbool.h>

#define MAKE_MOVE(from, to, flag) {from, to, flag}
typedef struct {
    uint64_t from;
    uint64_t to;
    uint8_t flag;
} Move;

void move(Board* b, Move move);
void capture(Board* b, Move move);

#endif // MOVE_GENERATOR_H