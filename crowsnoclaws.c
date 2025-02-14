#include "board.h"
#include "constant.h"

// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    Board board;
    init_board(&board);
    print_board(&board);

    return 0;
}