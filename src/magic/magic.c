#include "magic/magic.h"
#include "board.h"
#include "constant.h"

// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

int rookIndexBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

int bishopIndexBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

uint64_t cacheRookMoves[64][4096];
uint64_t cacheBishopMoves[64][512];

uint64_t rookMasks[64];
uint64_t bishopMasks[64];

uint64_t rookAtkCache_get(uint64_t bbRsqr, uint64_t occ) {
    printf("Calculating rook attack cache for square: %" PRIu64 " and occupancy: %" PRIu64 "\n", bbRsqr, occ);
    uint64_t hash = ((occ & rookMasks[bbRsqr]) * rookMagics[bbRsqr]) >> (64 - rookIndexBits[bbRsqr]);
    printf("Computed hash: %" PRIu64 "\n", hash);
    uint64_t result = cacheRookMoves[bbRsqr][hash];
    printf("Rook attack result from cache: %" PRIu64 "\n", result);
    return result;
}
uint64_t bishopAtkCache_get(uint64_t bbBsqr, uint64_t occ) {
    printf("Calculating bishop attack cache for square: %" PRIu64 " and occupancy: %" PRIu64 "\n", bbBsqr, occ);
    uint64_t hash = ((occ & bishopMasks[bbBsqr]) * bishopMagics[bbBsqr]) >> (64 - bishopIndexBits[bbBsqr]);
    printf("Computed hash: %" PRIu64 "\n", hash);
    uint64_t result = cacheBishopMoves[bbBsqr][hash];
    printf("Bishop attack result from cache: %" PRIu64 "\n", result);
    return result;
}

uint64_t occupancySet(int index, int bits_in_mask, uint64_t attack_mask) {
    // occupancy map
    uint64_t occupancy = 0ULL;
    
    // loop over the range of bits within attack mask
    for (int count = 0; count < bits_in_mask; count++)
    {
        // get LS1B index of attacks mask
        #ifdef __GNUC__
        int square = __builtin_ctzll(attack_mask & -attack_mask);
        #else
        int square = LSB(attack_mask);
        #endif

        attack_mask ^= (1ULL << square);

        if (index & (1 << count))
            occupancy |= (1ULL << square);
    }
    
    return occupancy;
}

void initRookAtk_cache() {
    for (int sqr = 0; sqr < 64; sqr++) {
        uint64_t mask = rookAtk(sqr2bit(sqr));
        rookMasks[sqr] = mask;
    
        #ifdef __GNUC__
        int bit_count = __builtin_popcountll(mask);
        #else
        int bit_count = COUNT_BITS(mask);
        #endif

        int occ_vary = 1 << bit_count;

        for (int cur_occ = 0; cur_occ < occ_vary; cur_occ++) {
            uint64_t occ = occupancySet(cur_occ, bit_count, mask);
            uint64_t magic_index = (occ * rookMagics[sqr]) >> (64 - rookIndexBits[sqr]);
            cacheBishopMoves[sqr][magic_index] = rookAtk_OnTheFly(sqr2bit(sqr), occ);
        }
    }
}
void initBishopAtk_cache() {
    for (int sqr = 0; sqr < 64; sqr++) {
        uint64_t mask = bishopAtk(sqr2bit(sqr));
        bishopMasks[sqr] = mask;
    
        #ifdef __GNUC__
        int bit_count = __builtin_popcountll(mask);
        #else
        int bit_count = COUNT_BITS(mask);
        #endif

        int occ_vary = 1 << bit_count;

        for (int cur_occ = 0; cur_occ < occ_vary; cur_occ++) {
            uint64_t occ = occupancySet(cur_occ, bit_count, mask);
            uint64_t magic_index = (occ * bishopMagics[sqr]) >> (64 - bishopIndexBits[sqr]);
            cacheBishopMoves[sqr][magic_index] = bishopAtk_OnTheFly(sqr2bit(sqr), occ);
        }
    }
}
