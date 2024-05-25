//
// Created by rushy on 24-5-24.
//
#include "base.hpp"
#include "basetype.hpp"
#include "chanel.hpp"
//#include <graphics.h>
#include "../HiEasyX.h"
#include <vector>
#ifndef TANK_BATTLE_GRAP_HPP
#define TANK_BATTLE_GRAP_HPP
extern Tank_info local;
extern hiex::Scene;
void rotate_draw_mask(IMAGE* img, IMAGE* mask, double angle, int x, int y);

void tank_turret(IMAGE* original, IMAGE* body, IMAGE* turret,
                 position body_pos, position turret_pos,
                 int bodyWidth, int turretWidth);

void draw_tank(hiex::ImageBlock *body, hiex::ImageBlock *turret, double head_degree, double turret_degree, int center_x,
               int center_y, int body_width, int turret_width, int turretOffsetX, int turretOffsetY = 0);
void render();
struct position map_convert_screen(position& origin);

#endif //TANK_BATTLE_GRAP_HPP
