#pragma once

#include <functional>
#include <utility>

#include "game_instances.h"

struct ActorState {
    int tic_time;
    const ActorState* next;
    std::function<void(Actor*, Game*)> think, action;

    ActorState(int tic_time, ActorState* next,
               std::function<void(Actor*, Game*)>  think,
               std::function<void(Actor*, Game*)> action);
};

class Actor  {
public:
    void do_actor(Game* game);

    void new_state(ActorState* nstate);

    virtual bool is_alive() const = 0;
    virtual bool is_active() const = 0;
    virtual bool is_shootable() const = 0;

    int get_tile_x() const;
    int get_tile_y() const;

    int x, y;

    const ActorState* state;
    int tic_count;
};