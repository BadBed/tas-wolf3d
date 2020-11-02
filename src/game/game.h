#pragma once

#include <vector>

#include "game_instances.h"
#include "player.h"
#include "consts.h"
#include "door.h"

enum TileType {
    T_FREE,
    T_DOOR,
    T_SOLID
};

class Game {
public:
    void play_frame(ControlInput input);
    void doors_frame();
    void actors_frame();

    int gen_rnd();
    Door* find_door(int tile_x, int tile_y);

    int rnd_index;

    std::vector<Door> door_list;
    std::vector<Actor> actor_list;
    Player player;

    int map_size;
    std::vector<std::vector<TileType> > map;
    std::vector<std::vector<Actor*> > actor_at;
};
