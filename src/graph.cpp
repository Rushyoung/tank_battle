//
// Created by rushy on 24-5-24.
//
#include "../include/grap.hpp"
/*
 * @img:源图像
 * @angle:角度（弧度）
 * @centerX:屏幕坐标系
 * @centerY:屏幕坐标系
 * */
void rotate_draw(draw_buffer *buffer, double angle, int x, int y) {
    // 计算图像的中心点
    int imgCenterX = buffer->dst->getwidth() / 2;
    int imgCenterY = buffer->dst->getheight() / 2;

    // 设置坐标系的原点为旋转中心
//    setorigin(centerX, centerY);
    buffer->block->SetPos(x - imgCenterX, y - imgCenterY);
    // 旋转图像和掩码
    buffer->dst->RotateImage_Alpha(angle - buffer->degree_now);
    buffer->degree_now = angle;


    //easyx废案
//    rotateimage(mask, mask, Radians(angle), WHITE);

//    // 使用 SRCAND ROP 代码将旋转后的掩码图像绘制到屏幕上
//    putimage(-imgCenterX, -imgCenterY, mask, SRCAND);
//
//    // 使用 SRCPAINT ROP 代码将旋转后的图像绘制到屏幕上
//    putimage(-imgCenterX, -imgCenterY, img, SRCPAINT);

    // 恢复坐标系的原点
//    setorigin(0, 0);
}

void render(){

    initgraph(SCREEN_LENGTH, SCREEN_WIDTH);
    hiex::BindWindowCanvas(&Screen);
    Map_canvas.Load_Image_Alpha(_T("../source/map1.png"));
    map_block.SetCanvas(&Map_canvas);
    map_layer.push_back(&map_block);
    main_scene.push_back(&map_layer);
    main_scene.push_back(&body_layer);
    main_scene.push_back(&turret_layer);
    cout << "construct"<<std::endl;

    Tank_info ai[AI_AMOUNT];
    Tank_info remote[REMOTE_MAX];

    for(int i = 0; i < AI_AMOUNT; i++){
        ai[i] = chan<Tank_info>("ai" + std::to_string(i)).receive();
    }
    for(int i = 0; i < remote_amount; i++){
        remote[i] = chan<Tank_info>("remote" + std::to_string(i)).receive();
    }
    local = chan<Tank_info>("local").receive();
    tank_draw_data* local_draw = chan<tank_draw_data*> ("local").receive_safe();
    cout << local_draw->id <<"\n" << std::endl;
    //render begin

    while(true){
        local = chan<Tank_info>("local").receive();
        cout<<local.pos.y << std::endl;
        position temp = position(0, 0);
        temp = map_convert_screen(temp, local.pos);
        map_block.SetPos(temp.x, temp.y);
//        map_block.SetPos(1210, 680);
        BEGIN_TASK();
        cleardevice();
        body_layer.push_back(&local_draw->body_block);
        turret_layer.push_back(&local_draw->turret_block);
        draw_tank(local_draw, local.head_degree, local.turret_degree, map_convert_screen(local.pos, local.pos).x,
                  map_convert_screen(local.pos, local.pos).y,
                  local_draw->offset, 0);

                { main_scene.Render(Screen.GetImagePointer()); }
        END_TASK();
        REDRAW_WINDOW();
        std::this_thread::sleep_for(millisecond(100));
    }
    closegraph();

}


//转换为使用origin为屏幕中心的坐标系
position map_convert_screen(position& base, position& origin){
    position dst(SCREEN_LENGTH/2, SCREEN_WIDTH/2);
    return (dst + (origin - base));
}

void draw_tank(tank_draw_data* buffer, double head_degree, double turret_degree, int center_x, int center_y,  int turretOffsetX, int turretOffsetY) {
    // 计算新的炮塔偏移量
    int newOffsetX = turretOffsetX * cos(Radians(head_degree)) - turretOffsetY * sin(Radians(head_degree));
    int newOffsetY = turretOffsetX * sin(Radians(head_degree)) + turretOffsetY * cos(Radians(head_degree));

    // 将 body 和 turret 绘制到屏幕上





    //easyx ruined
    rotate_draw(&buffer->turret_info, head_degree, center_x, center_y);
    rotate_draw(&buffer->body_info,  turret_degree, center_x+newOffsetX, center_y+newOffsetY);
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

