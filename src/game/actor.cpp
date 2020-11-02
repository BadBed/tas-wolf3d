#include "actor.h"

ActorState::ActorState(int tic_time, ActorState *next, std::function<void(Actor *, Game *)> think,
                       std::function<void(Actor *, Game *)> action)
        :
        tic_time(tic_time),
        next(next),
        think(std::move(think)),
        action(std::move(action)) {
}

void Actor::do_actor(Game *game) {
    if (!is_active()) {
        return;
    }
    // flags

    if (tic_count == 0) {
        state->think(this, game);
        // set actor_at
    }
    else {
        tic_count--;
        if (tic_count == 0) {
            state->action(this, game);
            state = state->next;
            tic_count = state->tic_time;
        }
        state->think(this, game);
        // set actor_at
    }
}

void Actor::new_state(ActorState* nstate) {
    state = nstate;
    tic_count = state->tic_time;
}
