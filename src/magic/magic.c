#include "magic/magic.h"
#include "board.h"
#include "constant.h"

// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

uint64_t bishopAttacks(uint64_t occ, int sq) {
   occ &= cacheBishopTbl[sq].mask;
   occ *= cacheBishopTbl[sq].magic;
   occ >>= 64-9;
   return cacheBishopAtk[sq][occ];
}

uint64_t rookAttacks(uint64_t occ, int sq) {
    occ &= cacheBishopTbl[sq].mask;
    occ *= cacheBishopTbl[sq].magic;
    occ >>= 64-9;
    return cacheBishopAtk[sq][occ];
}
