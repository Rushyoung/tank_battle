//
// Created by 小小喵姬 on 24-5-13.
//
#define MAP_X 2000
#define MAP_Y 2000

#define SCREEN_WIDTH 1080
#define SCREEN_LENGTH 1920

#include "basetype.hpp"
#include "chanel.hpp"
#ifndef TANK_BATTLE_BASE_HPP
#define TANK_BATTLE_BASE_HPP
#define AI_AMOUNT 20
#define REMOTE_MAX 2


//extern int ai_amount;
extern bool is_host;
extern int remote_amount;

enum TankType{

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
        double center_distance = distance(other.pos, pos);
        double real_distance = center_distance - other.edge(0) - edge(0);//temp
        return real_distance < 0;
    }
    int getLength(){return length;}
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
    /*
     * @x:逻辑x坐标（地图）
     * @y:逻辑y坐标（地图）
     * @length:圆形碰撞箱半径
     * @body_image:tank的模型图片
     * */
    baseTank(int x, int y, int length, int id, double speed):pos(x, y), col(x, y, length), id(id), speed(speed) { head_degree = 90; enable = true; turret_degree = 90;}
    virtual void control(double _degree = 0) = 0;
    int getX(){return pos.x;}
    int getY(){return pos.y;}
    int getLength(){return col.getLength();}
    struct position getPos(){return pos;}
    double getDegree(){return head_degree;}
    double getTurrent_degree(){return turret_degree;}
    void broken();
protected:
    int id;
    enum TankType type;
    struct position pos;
    Collision col;
    double head_degree;
    double turret_degree;
    double speed;
    bool enable;

};

class Tank_local : public baseTank{
public:
    Tank_local(int x, int y, int length, int id, double speed): baseTank(x, y, length, id, speed), speed(speed){chan<Tank_info>("local").send(Tank_info(pos, head_degree, turret_degree, true));}
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
    Bullet(baseTank* tank): origin_pos(tank->getPos()), degree(tank->getDegree()),
                            col(tank->getX() + tank->getLength() * cos(Radians(tank->getTurrent_degree())),
        tank->getY() + tank->getLength() * sin(Radians(tank->getTurrent_degree())),
        BULLET_LENGTH,
        tank->getTurrent_degree()){}
    void move();
private:
    struct position origin_pos;
    double degree;
    Collision col;
    long long fire_timestamp;
};



#endif //TANK_BATTLE_BASE_HPP
