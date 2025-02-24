# Procedure for modular code

1. The attack generation should have only the functions to init the bishop and rook caches and the functions to get the attacks of a bishop and a rook.
2. any other function should be in the separeted "interface.h" file and shall not be only present in one file (i.e. it must be implemented for all atk_gen ways equally for modular code).

## In reference of "1."
The functions shall be named and typed as follows:
```c
// *init is only called if "CALL_INIT" is defined
void bishop_cacheInit(); // init the bishop cache from global variables
void rook_cacheInit(); // init the rook cache fromm global variables
void slider_cacheInit(); // run both the rook and the bishop cache init

// the following functions are declared in atk_gen_helpers.h and must be defined in the new atk_gen way

uint64_t gen_bishopAtk(int sqr, uint64_t occ); // get the attacks of a bishop at a given square and occupancy considering it disregards friendly pieces later on the program
uint64_t gen_rookAtk(int sqr, uint64_t occ); // get the attacks of a rook at a given square and occupancy considering it disregards friendly pieces later on the program
uint64_t gen_queenAtk(int sqr, uint64_t occ); // get the attacks of a queen at a given square and occupancy
```

## In reference of "atk_gen_helpers.h"
The functions implemented there should be the helper functions that you may use at the actual atk_gen configuration