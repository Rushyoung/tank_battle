//
// Created by 小小喵姬 on 24-5-13.
//
#include "../include/base.hpp"
#define ROTATE_SPEED 0.1

void Tank_local::control(double _degree) {
    while(true){
        if(!enable){return;}//destruct & broken
        bool changed;
        changed = false;
        _mouse = GetMouseMsg();
        switch(_mouse.uMsg){
            case WM_MOUSEMOVE:
                turret_degree = Degree(atan2(_mouse.y - pos.y, _mouse.x - pos.x));
                changed = true;
                //wait for adjust
            case WM_LBUTTONDOWN:
                turret_degree = Degree(atan2(_mouse.y - pos.y, _mouse.x - pos.x));
                changed = true;
                //wait for fire & adjust
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
                changed = true;
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
                changed = true;
            }
        }
        //rotate+
        {
            head_degree += ROTATE_SPEED;
            while (head_degree >= 360) {
                head_degree -= 360;
            }
            changed = true;
        }
        //rotate-
        {
            head_degree -= ROTATE_SPEED;
            while (head_degree < 0) {
                head_degree += 360;
            }
            changed = true;
        }
        //send
        if(changed){
            chan("local").send(Tank_info(pos, head_degree, turret_degree, true));
        }
        //sleep
        std::this_thread::sleep_for(millisecond(FRAME_TIME));
    }
}

void baseTank::broken() {

}
