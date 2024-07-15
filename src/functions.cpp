#ifndef DEBUG
#include "functions.hpp"
#endif

#include <cmath>

#include "render.hpp"

double angle_between_points(double x1, double y1, double x2, double y2){
    double dx = x2 - x1;
    double dy = y2 - y1;
    double angle = atan2(dy, dx) * 180 / PI;
    return -angle;
}
double angle_between_points(render::position p1, render::position p2){
    return angle_between_points(p1.x, p1.y, p2.x, p2.y);
}