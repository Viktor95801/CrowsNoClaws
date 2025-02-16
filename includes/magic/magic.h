#ifndef MAGIC_H
#define MAGIC_H

#include <stdint.h>

uint64_t cacheBishopAtk[64][512]; // 256 K
uint64_t cacheRookAtk[64][4096];   // 2048K

uint64_t bishopMask[64];
uint64_t rookMask[64];

/* typedef struct {
   uint64_t mask;  // to mask relevant squares of both lines (no outer squares)
   uint64_t magic; // magic 64-bit factor
} SMagic;

SMagic cacheBishopTbl[64];
SMagic cacheRookTbl[64]; */

uint64_t rook_magics[64];
uint64_t bishop_magics[64];

void initBishopAtk_cache();
void initRookAtk_cache();

uint64_t bishopAttacksMgc(uint64_t occ, int sq);
uint64_t rookAttacksMgc(uint64_t occ, int sq);

uint32_t count_bits(uint64_t bitboard);

#endif // MAGIC_H