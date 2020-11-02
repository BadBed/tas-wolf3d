#include "door.h"
#include "game.h"
#include "util.h"

void Door::move(Game* game) {
    switch (state) {
        case D_OPEN:
            move_open(game);
            break;
        case D_CLOSING:
            move_closing(game);
            break;
        case D_OPENING:
            move_opening(game);
            break;
        case D_CLOSED:
            break;
    }
}

void Door::open(Game* game) {
    if (state == D_OPEN) {
        tic_count = 0;
    }
    else {
        state = D_OPENING;
    }
}

void Door::close(Game* game) {
    if (can_be_closed(game)) {
        return;
    }
    state = D_CLOSING;
    game->map[tile_x][tile_y] = T_DOOR;
}

void Door::operate_door(Game* game) {
    if (check_key(game)) {
        switch (state) {
            case D_CLOSED:
            case D_CLOSING:
                open(game);
                break;
            case D_OPEN:
            case D_OPENING:
                close(game);
                break;
        }
    }
}

bool Door::can_be_closed(Game* game) const {
    if (game->actor_at[tile_x][tile_y]) {
        return false;
    }

    if (game->player.get_tile_x() == tile_x and game->player.get_tile_y() == tile_y) {
        return false;
    }

    if (is_collide_with_object(game->player.x, game->player.y)) {
        return false;
    }

    Actor* check[2];
    if (is_vertical) {
        check[0] = game->actor_at[tile_x-1][tile_y];
        check[1] = game->actor_at[tile_x+1][tile_y];
    }
    else {
        check[0] = game->actor_at[tile_x][tile_y-1];
        check[1] = game->actor_at[tile_x][tile_y+1];
    }

    for (Actor* obj : check) {
        if (is_collide_with_object(obj->x, obj->y)) {
            return false;
        }
    }

    return true;
}

bool Door::is_collide_with_object(int obj_x, int obj_y) const {
    constexpr int DX[5] = {0, 0, 0, MIN_DIST, -MIN_DIST};
    constexpr int DY[5] = {0, MIN_DIST, -MIN_DIST, 0, 0};

    for (int i = 0; i < 5; ++i) {
        int x = obj_x + DX[i];
        int y = obj_y + DY[i];

        if (coord2tile(x) == tile_x and coord2tile(y) == tile_y) {
            return false;
        }
    }
    return true;
}

void Door::move_open(Game* game) {
    tic_count++;
    if (tic_count >= OPEN_TICS) {
        close(game);
    }
}

void Door::move_closing(Game* game) {
    // open door if something blocks it
    if (game->actor_at[tile_x][tile_y] or
            (game->player.get_tile_x() == tile_x and game->player.get_tile_y() == tile_y)) {
        open(game);
    }

    position--;

    if (position == 0) {
        state = D_CLOSED;
        disconnect_areas(game);
    }
}

void Door::move_opening(Game* game) {
    if (position == 0) {
        connect_areas(game);
    }

    position++;

    if (position == MAX_DOOR_POS) {
        state = D_OPEN;
        tic_count = 0;
        game->map[tile_x][tile_y] = T_FREE;
    }
}
