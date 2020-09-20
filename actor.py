from typing import Callable, Optional
from game import Game
from enum import Enum


class ObjType(Enum):
    player = 1
    guard = 2


class State:
    def __init__(self):
        self.tic_time: Optional[int] = None
        self.next: Optional[State] = None

        self.think: Callable[[Actor, Game], None] = (lambda a, g: None)
        self.action: Callable[[Actor, Game], None] = (lambda a, g: None)


class Actor:
    def __init__(self):
        self.state: Optional[State] = None
        self.tic_count: Optional[int] = None
        self.is_active: bool = False
        self.x: Optional[int] = None
        self.y: Optional[int] = None

    def do_actor(self, game: Game) -> None:
        if not self.is_active:
            return None
        # ! WL_PLAY 1264 - 1268
        if self.tic_count == 0:
            self.state.think(self, game)
            # ! Flags and actor_at
            return None

        self.tic_count -= 1
        if self.tic_count <= 0:
            self.state.action(self, game)

            if self.state is None or self.state.next is None:
                return None
            self.state = self.state.next

            if self.state.tic_time == 0:
                self.tic_count = 0
            else:
                self.tic_count += self.state.tic_time

        self.state.think(self, game)
        # ! Flags and actor_at
