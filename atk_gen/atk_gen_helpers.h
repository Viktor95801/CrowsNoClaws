#ifndef ATK_GEN_HELPERS_H
#define ATK_GEN_HELPERS_H

#include <stdint.h>


// *init is only called if "__CALL_INIT__" is defined
// init the bishop cache from global variables
void bishop_cacheInit(); 
// init the rook cache fromm global variables
void rook_cacheInit(); 
// run both the rook and the bishop cache init
void slider_cacheInit(); 

// get the attacks of a bishop at a given square and occupancy
uint64_t gen_bishopAtk(int sqr, uint64_t occ); 
// get the attacks of a rook at a given square and occupancy
uint64_t gen_rookAtk(int sqr, uint64_t occ); 
// get the attacks of a queen at a given square and occupancy
uint64_t gen_queenAtk(int sqr, uint64_t occ);

#pragma region Kindergarten
#define file(sqr) (sqr & 7)
#define rank(sqr) (sqr >> 3)

typedef struct {
    uint64_t horizontal;
    uint64_t vertical;
    uint64_t diagonal;
    uint64_t anti_diagonal;
} DAtkMasks;

DAtkMasks KrookAtk_OnTheFly(uint64_t bbrsqr, uint64_t blockers);
DAtkMasks KbishopAtk_OnTheFly(uint64_t bbrsqr, uint64_t blockers);
#pragma endregion

#endif // ATK_GEN_HELPERS_H