#include "magic/magic.h"
#include "board.h"
#include "constant.h"

// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/**************************************\
 ======================================
        
         Plain magic bitboards implementation
                    heavily inspired by Code Monkey King BBC chess engine
 ======================================
\**************************************/

/**
 * @brief Computes a set of squares that occupy a given attack mask according to a given index.
 *
 * This function takes an index, the number of bits in the attack mask, and the attack mask itself
 * and returns a set of squares that occupy the attack mask according to the index.
 *
 * The function uses a bit population count to find the first set bit in the index, and from there
 * it iterates over the range of bits in the attack mask, and for each bit, if the index has that
 * bit set, it adds the corresponding square to the occupancy map.
 *
 * @param index The index to use for generating the occupancy map.
 * @param bits_in_mask The number of bits in the attack mask.
 * @param attack_mask The attack mask to use for generating the occupancy map.
 * @return A set of squares that occupy the attack mask according to the index.
 */
uint64_t occupancySet(int index, int bits_in_mask, uint64_t attack_mask) {
    // occupancy map
    uint64_t occupancy = 0ULL;
    
    // loop over the range of bits within attack mask
    for (int count = 0; count < bits_in_mask; count++)
    {
        // find first set bit in index
        int square = LSB(index);
        
        // make sure occupancy is on board
        if (square < 64)
            // populate occupancy map
            occupancy |= (1ULL << square);
        
        // clear LS1B of index
        index &= ~(1ULL << square);
    }
    
    // return occupancy map
    return occupancy;
}

uint64_t rook_magics[64] = {
    0x8a80104000800020ULL,
    0x140002000100040ULL,
    0x2801880a0017001ULL,
    0x100081001000420ULL,
    0x200020010080420ULL,
    0x3001c0002010008ULL,
    0x8480008002000100ULL,
    0x2080088004402900ULL,
    0x800098204000ULL,
    0x2024401000200040ULL,
    0x100802000801000ULL,
    0x120800800801000ULL,
    0x208808088000400ULL,
    0x2802200800400ULL,
    0x2200800100020080ULL,
    0x801000060821100ULL,
    0x80044006422000ULL,
    0x100808020004000ULL,
    0x12108a0010204200ULL,
    0x140848010000802ULL,
    0x481828014002800ULL,
    0x8094004002004100ULL,
    0x4010040010010802ULL,
    0x20008806104ULL,
    0x100400080208000ULL,
    0x2040002120081000ULL,
    0x21200680100081ULL,
    0x20100080080080ULL,
    0x2000a00200410ULL,
    0x20080800400ULL,
    0x80088400100102ULL,
    0x80004600042881ULL,
    0x4040008040800020ULL,
    0x440003000200801ULL,
    0x4200011004500ULL,
    0x188020010100100ULL,
    0x14800401802800ULL,
    0x2080040080800200ULL,
    0x124080204001001ULL,
    0x200046502000484ULL,
    0x480400080088020ULL,
    0x1000422010034000ULL,
    0x30200100110040ULL,
    0x100021010009ULL,
    0x2002080100110004ULL,
    0x202008004008002ULL,
    0x20020004010100ULL,
    0x2048440040820001ULL,
    0x101002200408200ULL,
    0x40802000401080ULL,
    0x4008142004410100ULL,
    0x2060820c0120200ULL,
    0x1001004080100ULL,
    0x20c020080040080ULL,
    0x2935610830022400ULL,
    0x44440041009200ULL,
    0x280001040802101ULL,
    0x2100190040002085ULL,
    0x80c0084100102001ULL,
    0x4024081001000421ULL,
    0x20030a0244872ULL,
    0x12001008414402ULL,
    0x2006104900a0804ULL,
    0x1004081002402ULL,
};

uint64_t bishop_magics[64] = {
    0x40040844404084ULL,
    0x2004208a004208ULL,
    0x10190041080202ULL,
    0x108060845042010ULL,
    0x581104180800210ULL,
    0x2112080446200010ULL,
    0x1080820820060210ULL,
    0x3c0808410220200ULL,
    0x4050404440404ULL,
    0x21001420088ULL,
    0x24d0080801082102ULL,
    0x1020a0a020400ULL,
    0x40308200402ULL,
    0x4011002100800ULL,
    0x401484104104005ULL,
    0x801010402020200ULL,
    0x400210c3880100ULL,
    0x404022024108200ULL,
    0x810018200204102ULL,
    0x4002801a02003ULL,
    0x85040820080400ULL,
    0x810102c808880400ULL,
    0xe900410884800ULL,
    0x8002020480840102ULL,
    0x220200865090201ULL,
    0x2010100a02021202ULL,
    0x152048408022401ULL,
    0x20080002081110ULL,
    0x4001001021004000ULL,
    0x800040400a011002ULL,
    0xe4004081011002ULL,
    0x1c004001012080ULL,
    0x8004200962a00220ULL,
    0x8422100208500202ULL,
    0x2000402200300c08ULL,
    0x8646020080080080ULL,
    0x80020a0200100808ULL,
    0x2010004880111000ULL,
    0x623000a080011400ULL,
    0x42008c0340209202ULL,
    0x209188240001000ULL,
    0x400408a884001800ULL,
    0x110400a6080400ULL,
    0x1840060a44020800ULL,
    0x90080104000041ULL,
    0x201011000808101ULL,
    0x1a2208080504f080ULL,
    0x8012020600211212ULL,
    0x500861011240000ULL,
    0x180806108200800ULL,
    0x4000020e01040044ULL,
    0x300000261044000aULL,
    0x802241102020002ULL,
    0x20906061210001ULL,
    0x5a84841004010310ULL,
    0x4010801011c04ULL,
    0xa010109502200ULL,
    0x4a02012000ULL,
    0x500201010098b028ULL,
    0x8040002811040900ULL,
    0x28000010020204ULL,
    0x6000020202d0240ULL,
    0x8918844842082200ULL,
    0x4010011029020020ULL,
};

// rook rellevant occupancy bits
int rookRellevantBits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

// bishop rellevant occupancy bits
int bishopRellevantBits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

uint64_t bishopAttacksMgc(uint64_t occ, int sq) {
   occ &= bishop_magics[sq];
   occ *= bishop_magics[sq];
   occ >>= 64-9;
   return cacheBishopAtk[sq][occ];
}

uint64_t rookAttacksMgc(uint64_t occ, int sq) {
    occ &= rook_magics[sq];
    occ *= rook_magics[sq];
    occ >>= 64-9;
    return cacheRookAtk[sq][occ];
}

void initBishopAtk_cache() {
    for (int sqr = 0; sqr < 64; sqr++) {
        printf("initBishopAtk_cache: sqr \'%d\' \n", sqr);
        uint64_t mask = bishopAtk(sqr);
        bishopMask[sqr] = mask;

        int bit_count = count_bits(mask);

        int occupancy_variations = 1 << bit_count;

        for (int i = 0; i < occupancy_variations; i++) {
            // init occupancies, magic index & attacks
            uint64_t occupancy = occupancySet(i, bit_count, mask);
            uint64_t magic_index = occupancy * bishop_magics[sqr] >> (64 - bishopRellevantBits[sqr]);
            cacheBishopAtk[sqr][magic_index] = bishopAtk_OnTheFly(sqr, occupancy);                
        }
    }
}
void initRookAtk_cache() {
    for (int sqr = 0; sqr < 64; sqr++) {
        printf("initRookAtk_cache: Currently on square \'%d\' \n", sqr);
        rookMask[sqr] = rookAtk(sqr);

        uint64_t mask = rookAtk(sqr);
        int bit_count = count_bits(mask);

        int occupancy_variations = 1 << bit_count;

        for (int i = 0; i < occupancy_variations; i++) {
            // init occupancies, magic index & attacks
            uint64_t occupancy = occupancySet(i, bit_count, mask);
            uint64_t magic_index = occupancy * rook_magics[sqr] >> (64 - rookRellevantBits[sqr]);
            cacheRookAtk[sqr][magic_index] = rookAtk_OnTheFly(sqr, occupancy);                
        }
    }
}

uint32_t state = 1804289383;
/**
 * @brief Generates a random 32-bit integer using the XOR algorithm.
 * @return A random 32-bit integer.
 */
uint32_t u32Random() {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

/**
 * @brief Generates a random 64-bit integer.
 * @return A random 64-bit integer.
 */
uint64_t u64Random() {
    uint64_t u1, u2, u3, u4;
    // randomize numbers
    u1 = (uint64_t)(u32Random()) & 0xFFFF;
    u2 = (uint64_t)(u32Random()) & 0xFFFF;
    u3 = (uint64_t)(u32Random()) & 0xFFFF;
    u4 = (uint64_t)(u32Random()) & 0xFFFF;

    return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

/**
 * @brief Count the number of set bits in a 64-bit bitboard.
 *
 * This function takes a 64-bit bitboard as input and returns the number
 * of bits that are set to 1. It uses an efficient bit manipulation technique
 * to count the set bits.
 *
 * @param bitboard The 64-bit bitboard to count set bits in.
 * @return The number of set bits in the bitboard.
 */

uint32_t count_bits(uint64_t bitboard) {
    uint32_t count = 0;
    while (bitboard) {
        count += bitboard & 1;
        bitboard >>= 1;
    }
    return count;
}
