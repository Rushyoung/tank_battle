#pragma once

#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

#include <cmath>

#include "render.hpp"

/**
 * @brief 计算两个点之间连线，与x轴正方向的夹角
*/
double angle_between_points(double, double, double, double);
double angle_between_points(render::position, render::position);





#endif // __FUNCTIONS_HPP__