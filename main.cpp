#include <windows.h>

int main() {
    PlaySoundA(TEXT("C:/Users/Administrator/Desktop/素材/music/start.wav"), NULL, SND_FILENAME);
    return 0;
}
//
// Created by 小小喵姬 on 24-5-23.
//
#include "include/net.hpp"
#include "include/grap.hpp"
#include "include/chanel.hpp"
#include "src/ui.cpp"
#include "HiEasyX.h"
//temp
int remote_amount;
Tank_info local;

//channel_map chan<Tank_info>::msg_set;
MOUSEMSG _mouse;
int main(){

    // 初始化图形窗口
//    initgraph(1200, 1000);

//    // 加载 PNG 图像
//    IMAGE img, mask, bg;
//    struct tank_data a(tiger);
//
////    BeginBatchDraw();
//    tank_turret(&a.original, &a.body, &a.turret, position(a.body_x, a.body_y), position(a.turret_x, a.turret_y), a.body_width, a.turret_width);
//    tank_turret(&a.original_mask, &a.body_mask, &a.turret_mask, position(a.body_x, a.body_y), position(a.turret_center_x, a.turret_center_y), a.body_width, a.turret_width);
////    putimage(10, 10, &a.turret_mask);
////    cout << "a" << a.turret.getwidth() << endl;
//    loadimage(&bg, _T("D:/temp/tank/temp.png"));
////    putimage(100,100,&bg);
//    draw_tank(&a.body, &a.body_mask, &a.turret, &a.turret_mask, 90.0, 0.0, 500, 500, a.offsite);
//    FlushBatchDraw();

//    loadimage(&img, _T("D:/temp/tank/churchill.png"));
//    loadimage(&mask, _T("D:/temp/tank/churchill_mask.png"));
//
//    // 使用 SRCAND ROP 代码将掩码图像绘制到屏幕上
//    putimage(100, 100, &mask, SRCAND);
//
//    // 使用 SRCPAINT ROP 代码将图像绘制到屏幕上
//    putimage(100, 100, &img, SRCPAINT);
//    rotate_draw_mask(&img, &mask, PI/2, 100+img.getwidth()/2, 100+img.getheight()/2);
    // 暂停
    system("pause");

    // 关闭图形窗口
    closegraph();
}