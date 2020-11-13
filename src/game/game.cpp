#include "game.h"

void Game::play_frame(ControlInput input)  {
    player.do_actor(this, input);
}

