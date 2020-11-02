#include "util.h"
#include "consts.h"

int coord2tile(int x) {
    return x >> TILE_SHIFT;
}

