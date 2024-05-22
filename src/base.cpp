//
// Created by 小小喵姬 on 24-5-13.
//
#include "../include/base.hpp"
#define ROTATE_SPEED 0.1
void Tank_local::control(double _degree) {
    //move forward
    {
        if (pos.x + speed * cos(head_degree) >= MAP_X || pos.x + speed * cos(head_degree) <= 0 || pos.y + speed * sin(head_degree) >= MAP_Y || pos.y + speed * sin(head_degree) <=0) {
            return;
        } else {
            pos.x += speed * cos(head_degree);
            pos.y += speed * sin(head_degree);
        }
    }
    //move backward
    {
        if (pos.x - speed * cos(head_degree) >= MAP_X || pos.x - speed * cos(head_degree) <= 0 || pos.y - speed * sin(head_degree) >= MAP_Y || pos.y - speed * sin(head_degree) <= 0) {
            return;
        } else {
            pos.x -= speed * cos(head_degree);
            pos.y -= speed * sin(head_degree);
        }
    }
    //rotate+
    {
        head_degree += ROTATE_SPEED;
        while(head_degree >= 2 * PI){
            head_degree -= 2*PI
        }
    }
}