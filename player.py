from game import Game
from enum import Enum
import math
import util


class Weapon(Enum):
    knife = 1
    pistol = 2
    smg = 3
    chaingun = 4


class InputData:
    def __init__(self, x_dir, y_dir, weapon, is_strafe, is_fire, is_use):
        assert x_dir in {-1, 0, 1}
        assert y_dir in {-1, 0, 1}
        assert weapon is None or type(weapon) == Weapon
        assert type(is_strafe) == type(is_fire) == type(is_use) == bool
        self.x_dir = x_dir
        self.y_dir = y_dir
        self.weapon = weapon
        self.is_strafe = is_strafe
        self.is_fire = is_fire
        self.is_use = is_use

    def __setattr__(self, key, value):
        raise RuntimeError("InputData is immutable")


class State(Enum):
    simple = 0
    attack = 1


class Player:
    def __init__(self):
        self.state = State.simple
        self.face_count = 0
        self.weapon = self.best_weapon = Weapon.knife
        self.ammo = 0
        self.angle = 0
        self.c_rotate_speed = 5
        self.c_move_speed = 14999
        self.c_move_back_speed = 9999

    def do_actor(self, game: Game, input_data: InputData):
        if self.state == State.simple:
            self.act_simple(game, input_data)
        elif self.state == State.attack:
            self.act_attack(game, input_data)

    def act_simple(self, game: Game, input_data: InputData):
        self.update_face(game)
        self.change_weapon(game, input_data)
        if input_data.is_use:
            self.cmd_use(game)
        if input_data.is_fire:
            self.cmd_fire(game)
        self.move(game, input_data)

    def act_attack(self, game: Game, input_data: InputData):
        self.update_face(game)
        self.move(game, input_data)
        self.do_attack(game)

    def update_face(self, game: Game):
        self.face_count += 1
        if self.face_count > game.gen_rnd():
            self.face_count += 1
            game.gen_rnd()

    def change_weapon(self, game: Game, input_data: InputData):
        w = input_data.weapon
        if w is not None and self.ammo > 0 and self.best_weapon >= w:
            self.weapon = w

    def cmd_use(self, game: Game):
        # NOT IMPLEMENTED
        pass

    def cmd_fire(self, game: Game):
        # NOT IMPLEMENTED
        pass

    def move(self, game: Game, input_data: InputData):
        # x move
        if input_data.is_strafe:
            dx = input_data.x_dir * self.c_move_speed
            self.thrust(self.angle - 90, dx, game)
        else:
            self.angle += input_data.x_dir * self.c_rotate_speed

        # y move
        if input_data.y_dir == 1:
            dy = self.c_move_speed
        else:
            dy = -self.c_move_back_speed
        self.thrust(self.angle, dy, game)

    def thrust(self, angle: int, dist: int, game: Game):
        dx = int(math.floor(dist * util.cos_table[angle]))
        dy = -int(math.floor(dist * util.sin_table[angle]))
        self.clip_move(dx, dy, game)

    def clip_move(self, dx: int, dy: int, game: Game):
        if self.try_move(dx, dy, game):
            return None
        if self.try_move(dx, 0, game):
            return None
        if self.try_move(0, dy, game):
            return None

    def try_move(self, dx: int, dy: int, game: Game):
        # NOT IMPLEMENTED
        pass

    def do_attack(self, game: Game):
        # NOT IMPLEMENTED
        pass

    @staticmethod
    def correct_angle(angle, maxval=360):
        while angle < 0:
            angle += maxval
        while angle >= maxval:
            angle -= maxval
