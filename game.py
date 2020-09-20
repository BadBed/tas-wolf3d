import default_values as dv
from typing import List, Optional
from actor import Actor
from player import Player


class Game:
    def __init__(self):
        self.rnd_index: Optional[int] = None
        self.rnd_table: List[int] = dv.rnd_table
        self.actor_list: List[Actor] = []
        self.player: Player = Player()

    def play_frame(self):
        # ! self.move_doors()
        # ! self.move_pwals()
        self.actors_frame()

    def actors_frame(self):
        for act in self.actor_list:
            act.do_actor(self)
        self.actor_list = [a for a in self.actor_list if a.state is not None]

    def move_walls(self):
        # NOT IMPLEMENTED
        pass

    def gen_rnd(self) -> int:
        res = self.rnd_table[self.rnd_index]
        self.rnd_index += 1
        self.rnd_index %= len(self.rnd_table)
        return res
