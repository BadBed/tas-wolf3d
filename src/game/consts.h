#pragma once
#include <functional>
#include <vector>
#include <cmath>

constexpr int TILE_SHIFT = 16;
constexpr int PLAYER_SIZE = 0x5800;

constexpr double PI = 3.141592657;

void init_tables();
constexpr int TABLES_SIZE = 360;
extern double SIN_TABLE[TABLES_SIZE];
extern double COS_TABLE[TABLES_SIZE];
