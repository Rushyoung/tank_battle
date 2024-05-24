#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include "include/base.hpp"
#pragma comment(lib, "winmm.lib")


// 图片的宽高
int imgWidth=250, imgHeight=250;
double rotationAngle = 0;

int bulletSpeed = 10;
double totalRotationChange = 180; // 停止旋转时计算我总角度变化

const char *background_path="D:\tankmissile.png";
//temp
int remote_amount;
Tank_info local;

channel_map chan::msg_set;
MOUSEMSG _mouse;



void updatePosition(int& imgXx, int& imgYy, int centerXx, int centerYy, int rotationAngle_) {
    double radian = rotationAngle_ * M_PI / 180.0;
    imgXx = centerXx - imgWidth / 2 * cos(radian) + imgHeight / 2 * sin(radian);
    imgYy = centerYy - imgWidth / 2 * sin(radian) - imgHeight / 2 * cos(radian);
}

int main() {

    initgraph(1920, 1080); // 初始化图形窗口，参数为窗口的宽度和高度



//    // 加载图片
//    loadimage(&img1, "D:/churchill.jpg");
//    loadimage(&img_bullet, "D:/tankmissile.png"); // 加载子弹图片


    std::vector<Bullet> bullets; // 使用vector来存储子弹实例

//    while (true) {
//
//
//        BeginBatchDraw();//在调用此函数之后，所有对图形设备的绘制操作（如 putimage()、line() 等）都会被缓存起来，而不会立即执行
//        cleardevice();//cleardevice() 被用于每次循环的开始，这有助于在更新图片位置或旋转之前清除之前的图像，确保每次显示的是最新的状态。
//        putimage(bgX+500, bgY+500, 100, 100, &bgImage,100, 100);
//        putimage(imgX_forback, imgY_forback, &img2); // 绘制图片
//
//        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // 左键按下时创建新子弹
//            bullets.emplace_back(imgX_forback, imgY_forback, totalRotationChange);
//        }
//
//        for (auto& bullet : bullets) { // 遍历并更新所有子弹
//            bullet.bullet_move();
//        }
//
//        BeginBatchDraw();
//        cleardevice();
//        putimage(bgX+500, bgY+500, 100, 100, &bgImage,100, 100);
//        putimage(imgX_forback, imgY_forback, &img2); // 绘制坦克
//        rotateimage(&img2, &img1, rotationAngle); // 旋转坦克
//
//        for (auto& bullet : bullets) { // 绘制所有子弹
//            bullet.bullet_draw(img_bullet);
//        }
//
//
//        Sleep(5);
//        FlushBatchDraw();//将之前在批次绘制模式下累积的所有图形操作一次性提交给图形硬件执行,因为所有的绘图操作都在一个批次中完成，而不是每次操作都发送一次
//
//        // 减少睡眠时间以加快移动速度
//    }


    closegraph();
    return 0;
}