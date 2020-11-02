#pragma once
#include "actor.h"

enum Direction {
    DIR_NORTH=0, DIR_NORTHEAST, DIR_EAST, DIR_SOUTHEAST, DIR_SOUTH,
    DIR_SOUTHWEST, DIR_WEST, DIR_NORTHWEST, DIR_NONE
};

struct EnemyTypeData {
    ActorState* when_damaged;
    ActorState* first_sight;
    int patrol_speed, active_speed;
};

class Enemy : public Actor {
public:
    bool is_alive() const override;
    bool is_active() const override;
    bool is_shootable() const override;

    bool is_active_field;
    int hp;
    Direction dir;
    EnemyTypeData* type_data;
};

void t_path(Actor* that, Game* game);
void t_chase(Actor* that, Game* game);
void t_shoot(Actor* that, Game* game);

bool try_walk(Enemy* enemy, Game* game);
void move_actor(Enemy* enemy, Game* game, int dist);

void kill_actor(Enemy* enemy, Game* game);
void damage_actor(Enemy* enemy, Game* game, int dmg);

bool check_sight(Enemy* enemy, Game* game);
bool check_line(Enemy* enemy, Game* game);
void first_sight(Enemy* enemy, Game* game);

int dir_to_dx(Direction dir);
int dir_to_dy(Direction dir);
