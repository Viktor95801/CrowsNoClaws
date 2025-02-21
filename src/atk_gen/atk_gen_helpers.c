#include "../atk_gen/atk_gen_helpers.h"
#include "board.h"
#include "constant.h"

// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

DAtkMasks KrookAtk_OnTheFly(uint64_t bbrsqr, uint64_t blockers) {
    uint64_t attacks = 0;
    uint64_t copy_bbrsqr = bbrsqr;

    DAtkMasks out = {0, 0, 0, 0};

    // north
    for (int i = 0; i < 8; i++) {
        attacks |= northOne(copy_bbrsqr);
        copy_bbrsqr = northOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // south
    for (int i = 0; i < 8; i++) {
        attacks |= southOne(copy_bbrsqr);
        copy_bbrsqr = southOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    out.vertical = attacks;
    attacks = 0;

    // east
    for (int i = 0; i < 8; i++) {
        attacks |= eastOne(copy_bbrsqr);
        copy_bbrsqr = eastOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // west
    for (int i = 0; i < 8; i++) {
        attacks |= westOne(copy_bbrsqr);
        copy_bbrsqr = westOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    out.horizontal = attacks;

    return out;
}

DAtkMasks KbishopAtk_OnTheFly(uint64_t bbrsqr, uint64_t blockers) {
    uint64_t attacks = 0;
    uint64_t copy_bbrsqr = bbrsqr;

    DAtkMasks out = {0, 0, 0, 0};
    
    // anti diagonal top-left
    for (int i = 0; i < 8; i++) {
        attacks |= noWeOne(copy_bbrsqr);
        copy_bbrsqr = noWeOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // anti diagonal bottom-right
    for (int i = 0; i < 8; i++) {
        attacks |= soEaOne(copy_bbrsqr);
        copy_bbrsqr = soEaOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    out.anti_diagonal = attacks;
    attacks = 0;

    // diagonal bottom-right
    for (int i = 0; i < 8; i++) {
        attacks |= soWeOne(copy_bbrsqr);
        copy_bbrsqr = soWeOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }
    copy_bbrsqr = bbrsqr;
    // east
    for (int i = 0; i < 8; i++) {
        attacks |= noEaOne(copy_bbrsqr);
        copy_bbrsqr = noEaOne(copy_bbrsqr);
        if (blockers & copy_bbrsqr) break;
    }

    out.diagonal = attacks;

    return out;
}
