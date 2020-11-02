#include "game.h"
#include "actor.h"

void Game::play_frame(ControlInput input)  {
    doors_frame();
    // move pwals
    player.do_actor(this, input);
    actors_frame();
}

void Game::actors_frame() {
    int alive_count = 0;
    for (auto& a : actor_list) {
        a.do_actor(this);
    }

    std::vector<Actor> new_actor_list;
    for (auto& a : actor_list) {
        if (a.is_alive()) {
            new_actor_list.emplace_back(std::move(a));
        }
    }
    actor_list = new_actor_list;
}

int Game::gen_rnd() {
    int res = RND_TABLE[rnd_index];
    rnd_index++;
    rnd_index %= RND_TABLE.size();
    return res;
}

void Game::doors_frame() {
    for (auto& d : door_list) {
        d.move(this);
    }
}
