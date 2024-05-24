//
// Created by rushy on 24-5-24.
//
#include "../include/grap.hpp"
/*
 * @img:源图像
 * @mask:掩码
 * @angle:角度（弧度）
 * @centerX:
 * @centerY:
 * */
void rotate_draw_mask(IMAGE* img, IMAGE* mask, double angle, int centerX, int centerY) {
    // 计算图像的中心点
    int imgCenterX = img->getwidth() / 2;
    int imgCenterY = img->getheight() / 2;

    // 设置坐标系的原点为旋转中心
    setorigin(centerX, centerY);

    // 旋转图像和掩码
    rotateimage(img, img, angle, BLACK);
    rotateimage(mask, mask, angle, WHITE);

    // 使用 SRCAND ROP 代码将旋转后的掩码图像绘制到屏幕上
    putimage(-imgCenterX, -imgCenterY, mask, SRCAND);

    // 使用 SRCPAINT ROP 代码将旋转后的图像绘制到屏幕上
    putimage(-imgCenterX, -imgCenterY, img, SRCPAINT);

    // 恢复坐标系的原点
    setorigin(0, 0);
}

void render(){
    std::vector<Tank_info> info;
    info[0] = chan("local").receive();
}