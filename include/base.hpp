//
// Created by 小小喵姬 on 24-5-13.
//
#define MAP_X
#define MAP_Y
#ifndef TANK_BATTLE_BASE_HPP
#define TANK_BATTLE_BASE_HPP
#define PI 3.14159265359


class baseTank{
public:
    virtual void move(double _degree = 0);
    int getX(){return x;}
    int getY(){return y;}
    double getDegree(){return degree;}

protected:
    int x;
    int y;
    double degree;
};

class Tank_local : public baseTank{
public:
    void move(double _degree = 0) override;
};

class Tank_ai : public baseTank{
public:
    void move(double _degree = 0) override;
};

class Tank_remote : public baseTank{
public:
    void move(double _degree = 0) override;
};


#endif //TANK_BATTLE_BASE_HPP
