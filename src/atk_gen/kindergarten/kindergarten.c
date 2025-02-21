#include "../atk_gen/kindergarten/kindergarten.h"

uint64_t rookVertical(uint64_t occ, uint8_t sqr) {
    return subsetVertical[sqr][(((occ & maskVertical[sqr]) * verticalMult[sqr]) >> 58)];
}
uint64_t rookHorizontal(uint64_t occ, uint8_t sqr) {
    return subsetHorizontal[sqr][((occ >> horizontalShiftTbl[sqr]) & 0xff)];
}
uint64_t bishopDiagonal(uint64_t occ, uint8_t sqr) {
    return subsetDiagonal[sqr][(((occ & maskDiagonal[sqr]) * B2_B7) >> 58)];  
}
uint64_t bishopAntiDiagonal(uint64_t occ, uint8_t sqr) {
    return subsetAntiDiagonal[sqr][(((occ & maskAntiDiagonal[sqr]) * B2_B7) >> 58)];
}

uint64_t gen_rookAtk(int sqr, uint64_t occ) {
    return rookVertical(occ, sqr) | rookHorizontal(occ, sqr);
}
uint64_t gen_bishopAtk(int sqr, uint64_t occ) {
    return bishopDiagonal(occ, sqr) | bishopAntiDiagonal(occ, sqr);
}
uint64_t gen_queenAtk(int sqr, uint64_t occ) {
    return gen_rookAtk(sqr, occ) | gen_bishopAtk(sqr, occ);
}