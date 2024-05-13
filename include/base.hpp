//
// Created by 小小喵姬 on 24-5-13.
//

#ifndef TANK_BATTLE_BASE_HPP
#define TANK_BATTLE_BASE_HPP
#define PI 3.14159265359
class Position{
public:
    Position():x(-1), y(-1){}
    Position(int x, int y):x(x), y(y){}
    int getX(){return x;}
    int getY(){return y;}
private:
    int x;
    int y;
};

class object{
public:
    void virtual move();
    Position getPos(){return pos;}
private:
    Position pos;
    double degree;

};


#endif //TANK_BATTLE_BASE_HPP
