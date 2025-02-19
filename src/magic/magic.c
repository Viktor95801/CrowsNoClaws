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
#include <time.h>

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

//region Helpers
uint64_t occupancySet(int index, int bits_in_mask, uint64_t attack_mask) {
    // occupancy map
    uint64_t occupancy = 0ULL;

    // loop over the range of bits within attack mask
    for (int count = 0; count < bits_in_mask; count++)
    {
        // get LS1B index of attacks mask
        //#ifdef __GNUC__
        //int square = __builtin_ctzll(attack_mask & -attack_mask);
        //#else
        int square = LSB(attack_mask);
        //#endif

        // readable code is for noobs
        ((attack_mask & (1ULL << square)) ? (attack_mask ^= (1ULL << square)) : 0);

        if (index & (1 << count))
            // populate occupancy map
            occupancy |= (1ULL << square);
    }
    //printf("Occupancy: 0x%" PRIX64 "\n", occupancy);
    //print_bitboard(occupancy);
    return occupancy;
}

uint32_t seed = 1804289383;
uint32_t uRandom32() {
    // XOR shift algorithm
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;

    // PCG
    //uint64_t state = (uint64_t)seed * 6364136223846793005ULL + 128301763864ULL;
    //seed = (uint32_t)(state >> 2) ^ state;

/*     uint32_t x = state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state = x; */
    return seed;
}

uint64_t uRandom64() {
    uint64_t x1,x2,x3,x4;

    x1 = (uint64_t)(uRandom32()) & 0xFFFF;
    x2 = (uint64_t)(uRandom32()) & 0xFFFF;
    x3 = (uint64_t)(uRandom32()) & 0xFFFF;
    x4 = (uint64_t)(uRandom32()) & 0xFFFF;

    return x1 | (x2 << 16) | (x3 << 32) | (x4 << 48);
}

//endregion

uint64_t findMagicBishop(int sqr) {
    int index_bits = bishopIndexBits[sqr];

    uint64_t occs[512];
    uint64_t attacks[512];
    uint64_t attacksUsed[512];

    uint64_t mask = bishopAtk(sqr2bit(sqr));
    int occ_vary = 1 << index_bits;

    for (int cur_occ = 0; cur_occ < occ_vary; cur_occ++) {
        occs[cur_occ] = occupancySet(cur_occ, index_bits, mask);
        attacks[cur_occ] = bishopAtk_OnTheFly(sqr2bit(sqr), occs[cur_occ]);
    }

    int max = 100000000;
    while (max--) {
        uint64_t magic = uRandom64() & uRandom64() & uRandom64();
        
        // skip if inappropriate
        if (COUNT_BITS(((mask * magic) & 0xFF00ULL)) < 6)
            continue;
        
        memset(attacksUsed, 0, sizeof(attacksUsed));

        bool fail = false;

        for (int cur_occ = 0; !fail && (cur_occ < occ_vary); cur_occ++) {
            uint64_t magic_index = (uint64_t)(occs[cur_occ] * magic) >> (64 - index_bits);

            if (attacksUsed[magic_index] == 0) 
                attacksUsed[magic_index] = attacks[cur_occ];
            else // fail on collision
                if (attacksUsed[magic_index] != attacks[cur_occ])
                    fail = true; 
        }

        if (!fail) // works
            return magic;
    }

    printf("Failed to find magic number for square (bishop): %d\n", sqr);
    return 0;
}
uint64_t findMagicRook(int sqr) {
    int index_bits = rookIndexBits[sqr];

    uint64_t occs[4096];
    uint64_t attacks[4096];
    uint64_t attacksUsed[4096];

    uint64_t mask = rookAtk(sqr2bit(sqr));
    int occ_vary = 1 << index_bits;

    for (int cur_occ = 0; cur_occ < occ_vary; cur_occ++) {
        occs[cur_occ] = occupancySet(cur_occ, index_bits, mask);
        attacks[cur_occ] = rookAtk_OnTheFly(sqr2bit(sqr), occs[cur_occ]);
    }

    int max = 100000000;
    while (max--) {
        uint64_t magic = uRandom64() & uRandom64() & uRandom64();
        
        // skip if inappropriate
        if (COUNT_BITS(((mask * magic) & 0xFF00ULL)) < 6)
            continue;
        
        memset(attacksUsed, 0, sizeof(attacksUsed));

        bool fail = false;

        for (int cur_occ = 0; !fail && (cur_occ < occ_vary); cur_occ++) {
            uint64_t magic_index = (uint64_t)(occs[cur_occ] * magic) >> (64 - index_bits);

            if (attacksUsed[magic_index] == 0) 
                attacksUsed[magic_index] = attacks[cur_occ];
            else // fail on collision
                if (attacksUsed[magic_index] != attacks[cur_occ])
                    fail = true; 
        }

        if (!fail) // works
            return magic;
    }

    printf("Failed to find magic number for square (rook): %d\n", sqr);
    return 0;
}

void printMagics() {
    
    // rook
    printf("\nconst uint64_t rookMagics[64] = {\n");
    for (int sqr = 0; sqr < 64; sqr++) { // goes trough squares
        uint64_t magic = findMagicRook(sqr);
        //for (int retry = 0; retry < 100 && magic == 0; retry++) { // retry if error
        //    magic = findMagicRook(sqr);
        //}
        printf("\t0x%" PRIX64 ",\n", magic);   
    }
    printf("};\n");

    // bishop
    printf("\nconst uint64_t bishopMasks[64] = {\n");
    for (int sqr = 0; sqr < 64; sqr++) {// goes trough squares
        uint64_t magic = findMagicBishop(sqr);
        //for (int retry = 0; retry < 100 && magic == 0; retry++) { // retry if error
        //    magic = findMagicBishop(sqr);
        //}
        printf("\t0x%" PRIX64 ",\n", magic);
    }
    printf("};\n");

    printf("******************\ndone\n******************\n");
}

uint64_t rookAtkCache_get(uint64_t bbRsqrID, uint64_t occ) {
    printf("Calculating rook attack cache for square: %" PRIu64 " and occupancy: 0x%" PRIX64 "\n", bbRsqrID, occ);
    occ &= rookMasks[bbRsqrID];
    occ *= rookMagics[bbRsqrID];
    occ >>= 64 - rookIndexBits[bbRsqrID];
    printf("RookMasks, Magics and IndexBits: 0x%" PRIX64 ", 0x%" PRIX64 ", %d\n", rookMasks[bbRsqrID], rookMagics[bbRsqrID], rookIndexBits[bbRsqrID]);
    printf("Computed hash: %" PRIu64 "\n", occ);
    uint64_t result = cacheRookMoves[bbRsqrID][occ];
    printf("Rook attack result from cache: %" PRIu64 "\n", result);
    return result;
}
uint64_t bishopAtkCache_get(uint64_t bbBsqrID, uint64_t occ) {
    printf("Calculating bishop attack cache for square: %" PRIu64 " and occupancy: 0x%" PRIX64 "\n", bbBsqrID, occ);
    occ &= bishopMasks[bbBsqrID];
    occ *= bishopMagics[bbBsqrID];
    occ >>= 64 - bishopIndexBits[bbBsqrID];
    printf("BishopMasks, Magics and IndexBits: 0x%" PRIX64 ", 0x%" PRIX64 ", %d\n", bishopMasks[bbBsqrID], bishopMagics[bbBsqrID], bishopIndexBits[bbBsqrID]);
    printf("Computed hash: %" PRIu64 "\n", occ);
    uint64_t result = cacheBishopMoves[bbBsqrID][occ];
    printf("Bishop attack result from cache: %" PRIu64 "\n", result);
    return result;
}

void initRookAtk_cache() {
    for (int sqr = 0; sqr < 64; sqr++) {
        uint64_t mask = rookAtk(sqr2bit(sqr));
        rookMasks[sqr] = mask;
    
        //#ifdef __GNUC__
        //int bit_count = __builtin_popcountll(mask);
        //#else
        int bit_count = COUNT_BITS(mask);
        printf("bit count: %d\n", bit_count);
        //#endif

        int occ_vary = 1 << bit_count;

        for (int cur_occ = 0; cur_occ < occ_vary; cur_occ++) {
            uint64_t occ = occupancySet(cur_occ, bit_count, mask);
            uint64_t magic_index = (occ * rookMagics[sqr]) >> (64 - rookIndexBits[sqr]);
            cacheRookMoves[sqr][magic_index] = rookAtk_OnTheFly(sqr2bit(sqr), occ);
            //if (magic_index == 0)
            //    printf("initRookAtk_cache: square: %d occupancy: 0x%" PRIX64 " magic index is zero \n", sqr, occ);
        }
    }
}
void initBishopAtk_cache() {
    for (int sqr = 0; sqr < 64; sqr++) {
        uint64_t mask = bishopAtk(sqr2bit(sqr));
        bishopMasks[sqr] = mask;
    
        //#ifdef __GNUC__
        //int bit_count = __builtin_popcountll(mask);
        //#else
        int bit_count = COUNT_BITS(mask);
        //#endif

        int occ_vary = 1 << bit_count;

        for (int cur_occ = 0; cur_occ < occ_vary; cur_occ++) {
            uint64_t occ = occupancySet(cur_occ, bit_count, mask);
            uint64_t magic_index = (occ * bishopMagics[sqr]) >> (64 - bishopIndexBits[sqr]);
            cacheBishopMoves[sqr][magic_index] = bishopAtk_OnTheFly(sqr2bit(sqr), occ);
            //if (magic_index == 0)
            //    printf("initBishopAtk_cache: square: %d occupancy: 0x%" PRIX64 " magic index is zero \n", sqr, occ);
        }
    }
}
