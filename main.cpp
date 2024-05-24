//
// Created by 小小喵姬 on 24-5-23.
//
#include "include/net.hpp"
#include "include/grap.hpp"
#include "include/chanel.hpp"

MOUSEMSG _mouse;
int main(){
    // 初始化图形窗口
    initgraph(640, 480);

    // 加载 PNG 图像
    IMAGE img, mask, bg;
    loadimage(&bg, _T("D:/temp/tank/temp.png"));
    loadimage(&img, _T("D:/temp/tank/churchill.png"));
    loadimage(&mask, _T("D:/temp/tank/churchill_mask.png"));
    putimage(100,100,&bg);
    // 使用 SRCAND ROP 代码将掩码图像绘制到屏幕上
    putimage(100, 100, &mask, SRCAND);

    // 使用 SRCPAINT ROP 代码将图像绘制到屏幕上
    putimage(100, 100, &img, SRCPAINT);
    rotate_draw_mask(&img, &mask, PI/2, 100+img.getwidth()/2, 100+img.getheight()/2);
    // 暂停
    system("pause");

    // 关闭图形窗口
    closegraph();
}