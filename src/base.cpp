//
// Created by 小小喵姬 on 24-5-13.
//
#include "../include/base.hpp"
#include "../include/grap.hpp"
#include <iostream>

#define ROTATE_SPEED 0.1
#define FOR_STRAIGHT_CRITICAL_VALUE 6.0
#define FOR_TURN_CRITICAL_VALUE 8.0
#define FIRST_DECISION 5

int whether_first=0;//0为第一次，1为后续

int for_condition=0;//0为前进，1为转弯

int probability_judge(int for_con){
    //初次时判断AI前进还是转弯
    if(whether_first==0){
        int random_number = random(1,10);
        if(random_number<=FIRST_DECISION){
            whether_first=1;
            for_condition=0;
            return probability_judge(for_condition);
        }else{
            whether_first=1;
            for_condition=1;
            return probability_judge(for_condition);
        }
    }
    //后续判断
    else{
        for_con=for_condition;
        int random_number = random(1,10);
        if(for_con==0){
            if(random_number<=FOR_STRAIGHT_CRITICAL_VALUE){
                for_condition=0;
                return 0;//返回值0为前进，1为左转，2为右转
            }
            else if(random_number<=FOR_STRAIGHT_CRITICAL_VALUE/2+5){
                for_condition=1;
                return 1;
            }
            else{
                for_condition=1;
                return 2;
            }
        }
        else{
            if(random_number<=FOR_TURN_CRITICAL_VALUE){
                for_condition=0;
                return 0;//返回值0为前进，1为左转，2为右转
            }
            else if(random_number<=FOR_TURN_CRITICAL_VALUE/2+5){
                for_condition=1;
                return 1;
            }
            else{
                for_condition=1;
                return 2;
            }
        }
    }
}



void Tank_local::control() {
    chan<Tank_info>("local").send(Tank_info(pos, head_degree, turret_degree, true));
    chan<tank_draw_data*> ("local").send(draw);
    while(true){
        if(!enable){return;}//destruct & broken
        bool changed;
        changed = false;
        _mouse = GetMouseMsg();
        switch(_mouse.uMsg){
            case WM_MOUSEMOVE:
                std::cerr << "mouse" << _mouse.x << std::endl;
                turret_degree = atan2(_mouse.y - pos.y, _mouse.x - pos.x);
                changed = true;
                //wait for adjust
            case WM_LBUTTONDOWN:
                turret_degree = atan2(_mouse.y - pos.y, _mouse.x - pos.x);
                changed = true;
                //wait for fire & adjust
        }
        //move forward
        if(GetAsyncKeyState(VK_UP)&0x80000){
            std::cerr << "up" << std::endl;
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
        if(GetAsyncKeyState(VK_DOWN)&0x8000){
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
        if(GetAsyncKeyState(VK_RIGHT)&0x8000){
            head_degree += ROTATE_SPEED;
            while (head_degree >= 360) {
                head_degree -= 360;
            }
            changed = true;
        }
        //rotate-
        if(GetAsyncKeyState(VK_LEFT)&0x8000){
            head_degree -= ROTATE_SPEED;
            while (head_degree < 0) {
                head_degree += 360;
            }
            changed = true;
        }
        //send
        if(changed){
            chan<Tank_info>("local").send(Tank_info(pos, head_degree, turret_degree, true));
        }
        //sleep
        std::this_thread::sleep_for(millisecond(FRAME_TIME));
    }
}

void baseTank::broken() {

}

position Bullet::get_Bullet_pos() {
    return position(origin_pos.x + BULLET_SPEED * fire_timestamp * cos(Radians(degree)),
                    origin_pos.y + BULLET_SPEED * fire_timestamp * sin(Radians(degree)));
}


void Tank_ai::control() {
    bool changed=false;
    while(true) {

        int move_judge=probability_judge(for_condition);

        //move forward
        if(move_judge==0){
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
        //rotate+，顺时针旋转
        else if(move_judge==1){
            head_degree += ROTATE_SPEED;
            while (head_degree >= 360) {
                head_degree -= 360;
            }
            changed = true;
        }
        //rotate-，逆时针旋转
        else{
            head_degree -= ROTATE_SPEED;
            while (head_degree < 0) {
                head_degree += 360;
            }
            changed = true;
        }


        //AI与主机玩家同屏幕的时候，炮塔转向自动攻击
        if(abs((pos-local.pos).x)<=SCREEN_LENGTH/2 && abs((pos-local.pos).y)<=SCREEN_WIDTH/2){
            turret_degree = Degree(atan2(local.pos.y - pos.y, local.pos.x - pos.x));
            //wait for adjust or fire
            changed = true;
        }



        //send
        if(changed){
            chan<Tank_info>("local").send(Tank_info(pos, head_degree, turret_degree, true));
        }
        //sleep
        std::this_thread::sleep_for(millisecond(FRAME_TIME));
    }
}
