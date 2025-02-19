#ifndef MAGIC_H
#define MAGIC_H

#include <stdint.h>

extern uint64_t cacheRookMoves[64][4096];
extern uint64_t cacheBishopMoves[64][512];

extern uint64_t rookMasks[64];
extern uint64_t bishopMasks[64];

extern int rookIndexBits[64];
extern int bishopIndexBits[64];

void printMagics();

void initRookAtk_cache();
void initBishopAtk_cache();

uint64_t occupancySet(int index, int bits_in_mask, uint64_t attack_mask);

uint64_t rookAtkCache_get(uint64_t bbRsqrID, uint64_t occ);
uint64_t bishopAtkCache_get(uint64_t bbBsqrID, uint64_t occ);

#endif // MAGIC_H