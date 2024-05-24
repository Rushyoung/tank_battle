//
// Created by rushy on 24-5-24.
//

#ifndef TANK_BATTLE_BASETYPE_HPP
#define TANK_BATTLE_BASETYPE_HPP

#include <graphics.h>
#include <cmath>
#include <graphics.h>
#include <easyx.h>
#include <random>
#include <thread>



#define Radians(x) ((x)*PI/180.0)
#define Degree(x) ((x)*180/PI)
#define PI 3.14159265359
#define millisecond(x) std::chrono::milliseconds(x)
#define FLASH_TIME 33
#define FRAME_TIME 10
#define BULLET_LENGTH 10
int random(int min, int max);
extern MOUSEMSG _mouse;
struct position{
    int x;
    int y;
    position(int x,int y):x(x), y(y){}
    position operator+(const position& dst){
        return position(x + dst.x, y + dst.y);
    }
    position operator-(const position& base){
        return position(x - base.x, y - base.y);
    }


};
double distance(const position& a, const position& b);
#include <mutex>

struct Tank_info{
    std::mutex mtx;  // 用于保护这个结构体的互斥锁
    struct position pos;
    double head_degree;
    double turret_degree;
    bool enable;
    Tank_info(): pos(-1, -1){enable = false;}
    Tank_info(struct position pos, double head_degree, double turret_degree, bool enable): pos(pos), head_degree(head_degree), turret_degree(turret_degree), enable(enable){}
    Tank_info& operator=(const Tank_info& other){
        if(other.pos.x < 0 || other.pos.y < 0){
            return *this;
        }
        else{
            std::lock_guard<std::mutex> lock(mtx);  // 锁定互斥锁
            pos = other.pos;
            head_degree = other.head_degree;
            turret_degree = other.turret_degree;
            enable = other.enable;
            return *this;
        }
    }
};
#endif //TANK_BATTLE_BASETYPE_HPP
