#pragma once

#include "game_instances.h"
#include "general_actor.h"
#include "consts.h"

enum Weapon {W_KNIFE = 1, W_PISTOL, W_SMG, W_CHAINGUN};

struct ControlInput {
    int dx, dy;
    bool is_strafe, is_attack, is_use;
    int weapon;
};

enum PlayerState {PS_BASIC, PS_ATTACK};

class Player {
public:
    void do_actor(Game* game, const ControlInput& input);

    void update_face(Game* game);
    void change_weapon(Game* game, const ControlInput& input);
    void cmd_use(Game* game);
    void cmd_fire(Game* game);
    void do_attack(Game* game, const ControlInput& input);

    void move(Game* game, const ControlInput& input);
    void thrust(Game* game, int angle, int dist);
    void clip_move(Game* game, int dx, int dy);
    bool try_move(Game* game, int dx, int dy);

    int get_tile_x() const;
    int get_tile_y() const;

    static int normalize_angle(int angel);

    int x, y;

    int rotate_speed{5}, move_speed{14999}, move_back_speed{9999};

    PlayerState state;
    int angle;

    int ammo;
    Weapon weapon, best_weapon;

    int face_count;
};