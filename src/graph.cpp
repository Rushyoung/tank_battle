//
// Created by rushy on 24-5-24.
//
#include "../include/grap.hpp"
/*
 * @img:源图像
 * @mask:掩码
 * @angle:角度（弧度）
 * @centerX:屏幕坐标系
 * @centerY:屏幕坐标系
 * */
void rotate_draw(IMAGE* img, hiex::Canvas* canvas, double angle, int centerX, int centerY) {
    // 计算图像的中心点
    int imgCenterX = img->getwidth() / 2;
    int imgCenterY = img->getheight() / 2;

    // 设置坐标系的原点为旋转中心
    setorigin(centerX, centerY);

    // 旋转图像和掩码
    HiEasyX::RotateImage_Alpha(img, Radians(angle));
    //easyx废案
//    rotateimage(mask, mask, Radians(angle), WHITE);

//    // 使用 SRCAND ROP 代码将旋转后的掩码图像绘制到屏幕上
//    putimage(-imgCenterX, -imgCenterY, mask, SRCAND);
//
//    // 使用 SRCPAINT ROP 代码将旋转后的图像绘制到屏幕上
//    putimage(-imgCenterX, -imgCenterY, img, SRCPAINT);

    // 恢复坐标系的原点
    setorigin(0, 0);
}

void render(){

    Tank_info ai[AI_AMOUNT];
    Tank_info remote[REMOTE_MAX];

    for(int i = 0; i < AI_AMOUNT; i++){
        ai[i] = chan<Tank_info>("ai" + std::to_string(i)).receive();
    }
    for(int i = 0; i < remote_amount; i++){
        remote[i] = chan<Tank_info>("remote" + std::to_string(i)).receive();
    }
    local = chan<Tank_info>("local").receive();
    struct draw_data{
        double degree_now;
        hiex::Canvas* dst;

    };
    //render begin



}


//转换为使用origin为屏幕中心的坐标系
struct position map_convert_screen(position& base, position& origin){
    position dst(SCREEN_LENGTH/2, SCREEN_WIDTH/2);
    return (dst + (origin - base));
}

void draw_tank(hiex::ImageBlock *body, hiex::ImageBlock *turret, double head_degree, double turret_degree, int center_x,
               int center_y, int body_width, int turret_width, int turretOffsetX, int turretOffsetY) {
    // 计算新的炮塔偏移量
    int newOffsetX = turretOffsetX * cos(Radians(head_degree)) - turretOffsetY * sin(Radians(head_degree));
    int newOffsetY = turretOffsetX * sin(Radians(head_degree)) + turretOffsetY * cos(Radians(head_degree));

    // 将 body 和 turret 绘制到屏幕上





    //easyx ruined
//    rotate_draw(body, body_mask, head_degree, center_x, center_y);
//    rotate_draw(turret, turret_mask, turret_degree, center_x+newOffsetX, center_y+newOffsetY);
}
void tank_turret(IMAGE* original, IMAGE* body, IMAGE* turret,
                 position body_pos, position turret_pos,
                 int bodyWidth, int turretWidth) {
    int bodyHeight = bodyWidth;
    int turretHeight = turretWidth;
    // 从 original 中裁剪出 body 和 turret 的图像
    SetWorkingImage(original);
    getimage(body, body_pos.x, body_pos.y, bodyWidth, bodyHeight);
    getimage(turret, turret_pos.x, turret_pos.y, turretWidth, turretHeight);
    SetWorkingImage(NULL);
}

