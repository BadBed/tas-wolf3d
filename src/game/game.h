#pragma once

#include <vector>

#include "game_instances.h"
#include "player.h"
#include "consts.h"

enum TileType {
    T_FREE,
    T_DOOR,
    T_SOLID
};

class Game {
public:
    void play_frame(ControlInput input);

    Player player;

    int map_size;
    std::vector<std::vector<TileType> > map;
};
