#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include <stdint.h>
#include <stdbool.h>


#define MAKE_MOVE(from, to, flag) {from, to, flag}
typedef struct {
    uint64_t from;
    uint64_t to;
    char flag;
} Move;

#endif // MOVE_GENERATOR_H