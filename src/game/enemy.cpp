//
// Created by yWX952783 on 9/24/2020.
//

#include "enemy.h"
#include "game.h"

int dir_to_dx(Direction dir) {
    constexpr int RES[9] = {0, 1, 1, 1, 0, -1, -1, -1, 0};
    return RES[dir];
}

int dir_to_dy(Direction dir) {
    constexpr int RES[9] = {-1, -1, 0, 1, 1, 1, 0, -1, 0};
    return RES[dir];
}

void damage_actor(Enemy* enemy, Game* game, int dmg) {
    // ! ATTACK MODE?
    if (!enemy->is_active()) {
        dmg *= 2;
    }
    enemy->hp -= dmg;
    if (enemy->hp <= 0) {
        kill_actor(enemy, game);
    }
    else {
        if (!enemy->is_active()) {
            first_sight(enemy, game);
        }

        if (enemy->type_data->when_damaged) {
            enemy->new_state(enemy->type_data->when_damaged);
        }
    }
}

void kill_actor(Enemy *enemy, Game *game) {
    // ! give score and drop item

    game->actor_at[enemy->get_tile_x()][enemy->get_tile_y()] = nullptr;
}

void first_sight(Enemy *enemy, Game *game) {
    enemy->is_active_field = true;
    enemy->new_state(enemy->type_data->first_sight);
    // ! ignore the door opening command
}

bool check_sight(Enemy *enemy, Game *game) {
    int dx = game->player.x - enemy->x;
    int dy = game->player.y - enemy->y;

    // ! if different area - don't try

    if (abs(dx) < MIN_SIGHT or abs(dy) < MIN_SIGHT) {
        return true;
    }

    switch (enemy->dir)
    {
        case DIR_NORTH:
            if (dy > 0)
                return false;
            break;
        case DIR_EAST:
            if (dx < 0)
                return false;
            break;
        case DIR_SOUTH:
            if (dy < 0)
                return false;
            break;
        case DIR_WEST:
            if (dx > 0)
                return false;
            break;
    }

    return check_line(enemy, game);
}

bool check_line(Enemy *enemy, Game *game) {
    int	x1,y1,xt1,yt1,x2,y2,xt2,yt2;
    int	x,y;
    int	xdist,ydist,xstep,ystep;
    int	temp;
    int	partial,delta;
    long	ltemp;
    int	xfrac,yfrac,deltafrac;
    unsigned intercept;

    x1 = enemy->x >> UNSIGNED_SHIFT;		// 1/256 tile precision
    y1 = enemy->y >> UNSIGNED_SHIFT;
    xt1 = x1 >> 8;
    yt1 = y1 >> 8;

    x2 = game->player.x >> UNSIGNED_SHIFT;
    y2 = game->player.y >> UNSIGNED_SHIFT;
    xt2 = game->player.get_tile_x();
    yt2 = game->player.get_tile_y();


    xdist = abs(xt2-xt1);

    if (xdist > 0) {
        if (xt2 > xt1)
        {
            partial = 256-(x1&0xff);
            xstep = 1;
        }
        else
        {
            partial = x1&0xff;
            xstep = -1;
        }

        deltafrac = abs(x2-x1);
        delta = y2-y1;
        ltemp = ((long)delta<<8)/deltafrac;
        if (ltemp > 0x7fffl)
            ystep = 0x7fff;
        else if (ltemp < -0x7fffl)
            ystep = -0x7fff;
        else
            ystep = ltemp;
        yfrac = y1 + (((long)ystep*partial) >>8);

        x = xt1+xstep;
        xt2 += xstep;
        do
        {
            y = yfrac>>8;
            yfrac += ystep;

            auto value = game->map[x][y];
            x += xstep;

            if (value == T_SOLID)
                return false;

            intercept = yfrac-ystep/2;


            if (value == T_DOOR && intercept>game->find_door(x, y)->position * DOOR_POS_FRAC)
                return false;

        } while (x != xt2);
    }

    ydist = abs(yt2-yt1);

    if (ydist > 0)
    {
        if (yt2 > yt1)
        {
            partial = 256-(y1&0xff);
            ystep = 1;
        }
        else
        {
            partial = y1&0xff;
            ystep = -1;
        }

        deltafrac = abs(y2-y1);
        delta = x2-x1;
        ltemp = ((long)delta<<8)/deltafrac;
        if (ltemp > 0x7fffl)
            xstep = 0x7fff;
        else if (ltemp < -0x7fffl)
            xstep = -0x7fff;
        else
            xstep = ltemp;
        xfrac = x1 + (((long)xstep*partial) >>8);

        y = yt1 + ystep;
        yt2 += ystep;
        do
        {
            x = xfrac>>8;
            xfrac += xstep;

            auto value = game->map[x][y];
            y += ystep;

            if (value == T_SOLID)
                return false;

            //
            // see if the door is open enough
            //
            intercept = xfrac-xstep/2;

            if (value == T_DOOR && intercept>game->find_door(x, y)->position * DOOR_POS_FRAC)
                return false;
        } while (y != yt2);
    }

    return true;
}

bool Enemy::is_alive() const {
    return hp > 0;
}

bool Enemy::is_shootable() const {
    return is_alive();
}

bool Enemy::is_active() const {
    return is_alive() and is_active_field;
}
