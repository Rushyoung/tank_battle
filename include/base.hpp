//
// Created by 小小喵姬 on 24-5-13.
//
#define MAP_X 2000
#define MAP_Y 2000
#include <cmath>
#ifndef TANK_BATTLE_BASE_HPP
#define TANK_BATTLE_BASE_HPP
#define PI 3.14159265359

struct position{
    int x;
    int y;
    position(int x,int y):x(x), y(y){}
    //distance
    double operator-(const position& a) const{
        return sqrt((a.x-x)*(a.x-x) + (a.y-y)*(a.y-y));
    }
};

class baseTank{
public:
    baseTank(int x, int y): pos(x, y){degree = PI/2;}
    virtual void move(double _degree = 0) = 0;
    int getX(){return pos.x;}
    int getY(){return pos.y;}
    struct position getPos(){return pos;}
    double getDegree(){return degree;}

protected:
    struct position pos;
    double degree;
};

class Tank_local : public baseTank{
public:
    Tank_local(int x, int y, double speed): baseTank(x, y), speed(speed){}
    void move(double _degree = 0) override;
protected:
    double speed;
};

class Tank_ai : public baseTank{
public:
    void move(double _degree = 0) override;
};

class Tank_remote : public baseTank{
public:
    void move(double _degree = 0) override;
};

class Bullet : public baseTank{
public:
    void move(double _degree = 0) override;
};

class Collision{
public:
    double edge(double _angele){
//        if(type == 'C'){
//            return length;
//        }
//        else if(type == 'S'){
//
//        }
        return length;
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

#endif //TANK_BATTLE_BASE_HPP
