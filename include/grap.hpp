//
// Created by rushy on 24-5-24.
//
#include "base.hpp"
#include "chanel.hpp"
#include <graphics.h>
#include <vector>
#ifndef TANK_BATTLE_GRAP_HPP
#define TANK_BATTLE_GRAP_HPP
void rotate_draw_mask(IMAGE* img, IMAGE* mask, double angle, int x, int y);

void render();
struct position map_convert_screen(position& origin);
#endif //TANK_BATTLE_GRAP_HPP
