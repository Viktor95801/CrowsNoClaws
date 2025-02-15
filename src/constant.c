#include "constant.h"

// external
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

uint64_t eastOne (uint64_t b) {return (b << 1) & 0xfefefefefefefefe;}
uint64_t noEaOne (uint64_t b) {return (b << 9) & 0xfefefefefefefefe;}
uint64_t soEaOne (uint64_t b) {return (b >> 7) & 0xfefefefefefefefe;}
uint64_t westOne (uint64_t b) {return (b >> 1) & 0x7f7f7f7f7f7f7f7f;}
uint64_t soWeOne (uint64_t b) {return (b >> 9) & 0x7f7f7f7f7f7f7f7f;}
uint64_t noWeOne (uint64_t b) {return (b << 7) & 0x7f7f7f7f7f7f7f7f;}
uint64_t northOne (uint64_t b) {return (b << 8);}
uint64_t southOne (uint64_t b) {return (b >> 8);}
