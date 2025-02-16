#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    char piece;
    uint64_t from;
    uint64_t to;
} Move;

Move moveInit(char piece, uint64_t from, uint64_t to);

#endif // MOVE_GENERATOR_H