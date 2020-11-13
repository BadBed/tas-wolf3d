#include "player.h"
#include "game.h"
#include "consts.h"

#include <cassert>

void Player::do_actor(Game *game, const ControlInput &input) {
//    update_face(game);
//    if (state == PS_BASIC) {
//        change_weapon(game, input);
//        if (input.is_use) {
//            cmd_use(game);
//        }
//        else if (input.is_attack) {
//            cmd_fire(game);
//        }
//    }
    move(game, input);
//    if (state == PS_ATTACK) {
//        do_attack(game, input);
//    }
}

void Player::update_face(Game *game) {
}

void Player::change_weapon(Game *game, const ControlInput &input) {
    assert(input.weapon >= 0 and input.weapon <= Weapon::W_CHAINGUN);

    if (input.weapon != 0 and ammo > 0 and input.weapon <= best_weapon) {
        weapon = static_cast<Weapon>(input.weapon);
    }
}

void Player::move(Game *game, const ControlInput &input) {
    assert(-1 <= input.dx and input.dx <= 1);
    assert(-1 <= input.dy and input.dy <= 1);

    if (input.is_strafe) {
        int dx = input.dx * move_speed;
        thrust(game, angle - 90, dx);
    }
    else {
        angle += input.dx * rotate_speed;
        angle = normalize_angle(angle);
    }

    if (input.dy == 1) {
        thrust(game, angle, move_speed);
    }
    else if (input.dy == -1) {
        thrust(game, angle + 180, move_back_speed);
    }
}

int Player::normalize_angle(int angel) {
    while (angel < 0) {
        angel += 360;
    }
    while (angel >= 360) {
        angel -= 360;
    }
    return angel;
}

void Player::thrust(Game *game, int angle, int dist) {
    angle = normalize_angle(angle);
    int dx = floor(dist * COS_TABLE[angle]);
    int dy = floor(dist * SIN_TABLE[angle]);
    clip_move(game, dx, dy);
}

void Player::clip_move(Game *game, int dx, int dy) {
    try_move(game, dx, dy) or try_move(game, dx, 0) or try_move(game, 0, dy);
}

bool Player::try_move(Game *game, int dx, int dy) {
    int new_x = x + dx;
    int new_y = y + dy;

    int txl = (new_x - PLAYER_SIZE) >> TILE_SHIFT;
    int txh = (new_x + PLAYER_SIZE) >> TILE_SHIFT;
    int tyl = (new_y - PLAYER_SIZE) >> TILE_SHIFT;
    int tyh = (new_y + PLAYER_SIZE) >> TILE_SHIFT;

    for (int tx = txl; tx <= txh; tx++) {
        for (int ty = tyl; ty <= tyh; ty++) {
            if (game->map[tx][ty] == T_SOLID) {
                return false;
            }
        }
    }


    if (txl > 0) txl--;
    if (tyl > 0) tyl--;
    if (txh < game->map_size - 1) txh++;
    if (tyh < game->map_size - 1) tyh++;

    // Check if there are actor

    this->x = new_x;
    this->y = new_y;
    return true;
}
