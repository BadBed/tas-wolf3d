#pragma once

#include "game_instances.h"

enum DoorState {D_OPEN, D_CLOSED, D_OPENING, D_CLOSING};

class Door {
public:
    int tile_x, tile_y;
    int tic_count, position;
    bool is_vertical;
    DoorState state;

    void move(Game*);

    void move_open(Game*);
    void move_closing(Game*);
    void move_opening(Game*);

    void open(Game*);
    void close(Game*);
    void operate_door(Game*);

    bool can_be_closed(Game*) const;
    bool check_key(Game*) const;
    bool is_collide_with_object(int obj_x, int obj_y) const;
    void connect_areas(Game*);
    void disconnect_areas(Game*);
};
