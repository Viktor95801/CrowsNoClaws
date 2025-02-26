#include "board.h"
#include "constants.h"

// external
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

void init_board(Board *board) {
    memset(board, 0, sizeof(*board));

/*     set_bit(&board->white[PAWN], A2); set_bit(&board->white[PAWN], B2);
    set_bit(&board->white[PAWN], C2); set_bit(&board->white[PAWN], D2);
    set_bit(&board->white[PAWN], E2); set_bit(&board->white[PAWN], F2);
    set_bit(&board->white[PAWN], G2); set_bit(&board->white[PAWN], H2);

    set_bit(&board->black[PAWN], A7); set_bit(&board->black[PAWN], B7);
    set_bit(&board->black[PAWN], C7); set_bit(&board->black[PAWN], D7);
    set_bit(&board->black[PAWN], E7); set_bit(&board->black[PAWN], F7);
    set_bit(&board->black[PAWN], G7); set_bit(&board->black[PAWN], H7); */
    board->white[PAWN] = 0xFF00ull;
    board->black[PAWN] = 0xFF000000000000ull;

    set_bit(&board->white[ROOK], A1); set_bit(&board->white[ROOK], H1);
    set_bit(&board->black[ROOK], A8); set_bit(&board->black[ROOK], H8);

    set_bit(&board->white[HORSE], B1); set_bit(&board->white[HORSE], G1);
    set_bit(&board->black[HORSE], B8); set_bit(&board->black[HORSE], G8);

    set_bit(&board->white[BISHOP], C1); set_bit(&board->white[BISHOP], F1);
    set_bit(&board->black[BISHOP], C8); set_bit(&board->black[BISHOP], F8);

    set_bit(&board->white[QUEEN], D1);
    set_bit(&board->black[QUEEN], D8);

    set_bit(&board->white[KING], E1);
    set_bit(&board->black[KING], E8);

    board->castling_rights = 0xF;
    board->side = WHITE;
}
Board init_FENboard(const char *FEN) {
    Board b;
    memset(&b, 0, sizeof(b));

    int rank = 7;
    int file = 0;

    int i = 0;
    while (FEN[i] != ' ') {
        if (FEN[i] == '/') {
            rank--;
            file = 0;
            i++;
            continue;
        } else if (FEN[i] >= '0' && FEN[i] <= '9') {
            file += FEN[i] - '0';
            i++;
            continue;
        } else {
            int index = rank * 8 + file;
            switch (FEN[i]) {
                case 'P': set_bit(&b.white[PAWN], index); break;
                case 'R': set_bit(&b.white[ROOK], index); break;
                case 'N': set_bit(&b.white[HORSE], index); break;
                case 'B': set_bit(&b.white[BISHOP], index); break;
                case 'Q': set_bit(&b.white[QUEEN], index); break;
                case 'K': set_bit(&b.white[KING], index); break;
                case 'p': set_bit(&b.black[PAWN], index); break;
                case 'r': set_bit(&b.black[ROOK], index); break;
                case 'n': set_bit(&b.black[HORSE], index); break;
                case 'b': set_bit(&b.black[BISHOP], index); break;
                case 'q': set_bit(&b.black[QUEEN], index); break;
                case 'k': set_bit(&b.black[KING], index); break;
            }
            file++;
            i++;
            continue;
        }
        i++;
    }
    if (FEN[i] == 'w') {b.side = WHITE; printf("white\n");} else {b.side = BLACK; printf("black\n");}
    i+=3; // sorry for the magic number, but it works (the index got a bit off for some reason)
    while (FEN[i] != ' ') {
        if (FEN[i] == 'K') {
            board_set_castlingRight(&b, WHITE, false);
        }
        if (FEN[i] == 'Q') {
            board_set_castlingRight(&b, WHITE, true);
        }
        if (FEN[i] == 'k') {
            board_set_castlingRight(&b, BLACK, false);
        }
        if (FEN[i] == 'q') {
            board_set_castlingRight(&b, BLACK, true);
        }
        i++;
    }
    i++;

    rank = 0;
    file = 0;
    while (FEN[i] != ' ') {
        if (FEN[i] >= '0' && FEN[i] <= '9') {
            rank = FEN[i] - '0';
        } else if (FEN[i] >= 'a' && FEN[i] <= 'h') {
            file = FEN[i] - 'a';
        }
        i++;
    }
    i++;
    b.enpass_sqr = (rank - 1) * 8 + file;

    char tmp[4] = {0};
    int j = 0;
    while (FEN[i] != ' ') {
        if (FEN[i] >= '0' && FEN[i] <= '9') {
            tmp[j] = FEN[i];
        }
        j++; i++;
    }
    b.fifty_clock = atoi(tmp);
    i++;

    memset(tmp, 0, sizeof(tmp));
    j = 0;
    while (FEN[i] != ' ') {
        if (FEN[i] >= '0' && FEN[i] <= '9') {
            tmp[j] = FEN[i];
        }
        j++; i++;
    }
    b.fullmove_clock = atoi(tmp);

    return b;
}

void print_board(const Board *board) {
    char* wht_blck[] = {"White", "Black"};
    printf("%s to move\n", wht_blck[board->side]);
    printf("Castling rights: %x\n", board->castling_rights);
    printf("Enpassant square: %d\n", board->enpass_sqr);
    printf("Halfmove clock: %d\n", board->fifty_clock);
    printf("Fullmove clock: %d\n", board->fullmove_clock);
    
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int index = rank * 8 + file;
            if (get_bit(&board->white[PAWN], index)) printf("P ");
            else if (get_bit(&board->white[ROOK], index)) printf("R ");
            else if (get_bit(&board->white[HORSE], index)) printf("H ");
            else if (get_bit(&board->white[BISHOP], index)) printf("B ");
            else if (get_bit(&board->white[QUEEN], index)) printf("Q ");
            else if (get_bit(&board->white[KING], index)) printf("K ");
            else if (get_bit(&board->black[PAWN], index)) printf("p ");
            else if (get_bit(&board->black[ROOK], index)) printf("r ");
            else if (get_bit(&board->black[HORSE], index)) printf("h ");
            else if (get_bit(&board->black[BISHOP], index)) printf("b ");
            else if (get_bit(&board->black[QUEEN], index)) printf("q ");
            else if (get_bit(&board->black[KING], index)) printf("k ");
            else printf(". ");
        }
        printf("%d\n", rank + 1);
    }
    printf("a b c d e f g h\n");
}

void print_bitboard(const U64 *board) {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int index = rank * 8 + file;
            if (get_bit(board, index)) printf("1 ");
            else printf("0 ");
        }
        printf("%d\n", rank + 1);
    }
    printf("a b c d e f g h\n");
}