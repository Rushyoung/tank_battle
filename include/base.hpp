//
// Created by 小小喵姬 on 24-5-13.
//
#define MAP_X 2000
#define MAP_Y 2000

#define SCREEN_WIDTH 1080
#define SCREEN_LENGTH 1920

#include <cmath>
#include <graphics.h>

#ifndef TANK_BATTLE_BASE_HPP
#define TANK_BATTLE_BASE_HPP
#define PI 3.14159265359
#define millisecond(x) std::chrono::milliseconds(x)
#define FLASH_TIME 33
#define FRAME_TIME

extern MOUSEMSG _mouse;
struct position{
    int x;
    int y;
    position(int x,int y):x(x), y(y){}
    //distance
    double operator-(const position& a) const{
        return sqrt((a.x-x)*(a.x-x) + (a.y-y)*(a.y-y));
    }
};

class Collision{
public:
    Collision(int x, int y, int length, double angle = 0): pos(x, y), length(length), angle(angle){}
    double edge(double _angele){
//        if(type == 'C'){
//            return length;
//        }
//        else if(type == 'S'){
//
//        }
        return length;
    }
    void update_pos(int x, int y){
        pos.x = x;
        pos.y = y;
    }
    /*
     * @return:碰撞1，没碰0
     * */
    bool is_coincide(Collision other){
        double center_distance = other.pos - pos;
        double real_distance = center_distance - other.edge(0) - edge(0);//temp
        return real_distance < 0;
    }
private:
    //时间缘故，先只做圆形碰撞箱
    struct position pos;
    double angle;
//    char type;//'C'-circle  'S'-square
    int length;
    int width;
    double rad;
};

class baseTank{
public:
    baseTank(int x, int y, int length): pos(x, y), col(x, y, length){ head_degree = 90; enable = true;}
    virtual void control(double _degree = 0) = 0;
    int getX(){return pos.x;}
    int getY(){return pos.y;}
    struct position getPos(){return pos;}
    double getDegree(){return head_degree;}

protected:
    struct position pos;
    Collision col;
    double head_degree;
    double turrent_degree;
    double speed;
    bool enable;
};

class Tank_local : public baseTank{
public:
    Tank_local(int x, int y, double speed, int length): baseTank(x, y, length), speed(speed){}
    void control(double _degree = 0) override;
protected:
    double speed;
};

class Tank_ai : public baseTank{
public:
    void control(double _degree = 0) override;
};

class Tank_remote : public baseTank{
public:
    void control(double _degree = 0) override;
};

class Bullet {
public:

};



#endif //TANK_BATTLE_BASE_HPP
