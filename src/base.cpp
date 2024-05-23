//
// Created by 小小喵姬 on 24-5-13.
//
#include "../include/base.hpp"
#define ROTATE_SPEED 0.1
#define Radians(x) {(x)*PI/180.0}
void Tank_local::control(double _degree) {
    while(true){
        if(!enable){return;}
        _mouse = GetMouseMsg();
        switch(_mouse.uMsg){
            case WM_MOUSEMOVE:
                turrent_degree = atan2(_mouse.y - pos.y, _mouse.x - pos.x);
        }
        //move forward
        {
            if (pos.x + speed * cos(Radians(head_degree)) >= MAP_X ||
                pos.x + speed * cos(Radians(head_degree)) <= 0 ||
                pos.y + speed * sin(Radians(head_degree)) >= MAP_Y ||
                pos.y + speed * sin(Radians(head_degree)) <= 0) {
                return;
            } else {
                pos.x += speed * cos(Radians(head_degree));
                pos.y += speed * sin(Radians(head_degree));
            }
        }
        //move backward
        {
            if (pos.x - speed * cos(Radians(head_degree)) >= MAP_X ||
                pos.x - speed * cos(Radians(head_degree)) <= 0 ||
                pos.y - speed * sin(Radians(head_degree)) >= MAP_Y ||
                pos.y - speed * sin(Radians(head_degree)) <= 0) {
                return;
            } else {
                pos.x -= speed * cos(Radians(head_degree));
                pos.y -= speed * sin(Radians(head_degree));
            }
        }
        //rotate+
        {
            head_degree += ROTATE_SPEED;
            while (head_degree >= 360) {
                head_degree -= 360;
            }
        }
        //rotate-
        {
            head_degree -= ROTATE_SPEED;
            while (head_degree < 0) {
                head_degree += 360;
            }
        }
    }
}