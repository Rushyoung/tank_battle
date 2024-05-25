//
// Created by rushy on 24-5-24.
//

#ifndef TANK_BATTLE_BASETYPE_HPP
#define TANK_BATTLE_BASETYPE_HPP

#include <propidl.h>


#include <cmath>
//#include <graphics.h>
//#include <easyx.h>
#include "../HiEasyX.h"
#include <random>
#include <thread>
#include <mutex>


#define Radians(x) ((x)*PI/180.0)
#define Degree(x) ((x)*180/PI)
//#define PI 3.14159265359
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


struct Tank_info{
    Tank_info(Tank_info const &info): pos(info.pos) {}
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



enum tank_type{churchil,is2,sherman,t34_85,tiger};

struct tank_data
{
    int offset;
    int body_width;
    int turret_width;
    hiex::Canvas body;
    hiex::Canvas turret;
    tank_data(enum tank_type type){
        switch (type) {
            case churchil:
                body_width=150;
                turret_width=150;
                offset=5;
                body.Load_Image_Alpha("../source/tank/churchill_body.png");
                turret.Load_Image_Alpha("../source/tank/churchill_turret.png");
                //test

                std::cerr << "load";
//                if (original.getwidth() == 0 || original.getheight() == 0) {
//                    std::cerr << "Failed to load image for original tank." << std::endl;
//                }
//                if (original_mask.getwidth() == 0 || original_mask.getheight() == 0) {
//                    std::cerr << "Failed to load image for original tank mask." << std::endl;
//                }
//                if (body.getwidth() == 0 || body.getheight() == 0) {
//                    std::cerr << "Failed to load image for tank body." << std::endl;
//                }
//                if (body_mask.getwidth() == 0 || body_mask.getheight() == 0) {
//                    std::cerr << "Failed to load image for tank body mask." << std::endl;
//                }
//                if (turret.getwidth() == 0 || turret.getheight() == 0) {
//                    std::cerr << "Failed to load image for tank turret." << std::endl;
//                }
//                if (turret_mask.getwidth() == 0 || turret_mask.getheight() == 0) {
//                    std::cerr << "Failed to load image for tank turret mask." << std::endl;
//                }

                break;
            case is2:
                body_width=150;
                turret_width=240;
                offset=15;
                body.Load_Image_Alpha("../source/tank/is2_body.png");
                turret.Load_Image_Alpha("../source/tank/is2_turret.png");
                break;
            case sherman:
                body_width=150;
                turret_width=150;
                offset=0;
                body.Load_Image_Alpha("../source/tank/sherman_body.png");
                turret.Load_Image_Alpha("../source/tank/sherman_turret.png");
                break;
            case t34_85:
                body_width=150;
                turret_width=240;
                offset=18;
                body.Load_Image_Alpha("../source/tank/t34_85_body.png");
                turret.Load_Image_Alpha("../source/tank/t34_85_turret.png");
                break;
            case tiger:
                body_width=150;
                turret_width=240;
                offset=0;
                body.Load_Image_Alpha("../source/tank/tiger_body.png");
                turret.Load_Image_Alpha("../source/tank/tiger_turret.png");
                break;
        }
    };
};
#endif //TANK_BATTLE_BASETYPE_HPP
