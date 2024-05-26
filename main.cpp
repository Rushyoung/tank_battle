//#include <windows.h>

//int main() {
//    PlaySoundA(TEXT("C:/Users/Administrator/Desktop/素材/music/start.wav"), NULL, SND_FILENAME);
//    return 0;
//}
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
hiex::Scene main_scene;
hiex::Layer map_layer;
hiex::Layer body_layer;
hiex::Layer turret_layer;
hiex::Canvas Map_canvas(MAP_X, MAP_Y);
hiex::ImageBlock map_block(&Map_canvas);
hiex::Canvas Screen;

//channel_map<Tank_info> chan<Tank_info>::msg_set;
MOUSEMSG _mouse;
tank_data churchill_data(churchill);
tank_data tiger_data(tiger);
tank_data is2_data(is2);
tank_data t34_85_data(t34_85);
tank_data sherman_data(sherman);




struct Tank_collection {
    tank_data* data;
    baseTank* tank_class;
    tank_draw_data drawData;
    std::thread tank_thread;
    Tank_collection(tank_data* data, baseTank* tank_class)
        : data(data), tank_class(tank_class), 
          drawData(&data->body, &data->turret, &body_layer, &turret_layer, data->offset),
          tank_thread(&baseTank::control, this->tank_class)
          {tank_class->update_draw(&drawData);cerr << "update" << endl;}
};

Tank_collection* create_tank(tank_type t, int id, Ai_Type ai){
    baseTank* tank_class = nullptr;
    tank_data* data;
    switch (t) {
        case churchill:
            data = &churchill_data;
            break;
        case sherman:
            data = &sherman_data;
            break;
        case tiger:
            data = &tiger_data;
            break;
        case is2:
            data = &is2_data;
            break;
        case t34_85:
            data = &t34_85_data;
            break;
    }
    switch (ai) {
        case Local:
            tank_class = new Tank_local(random(0, MAP_X), random(0, MAP_Y), data->body_width/2,id, 2, t);
            return new Tank_collection(data, tank_class);
    }
}





int main() {
    // 初始化图形窗口

    std::vector<Tank_collection*> tanks;
    tanks.push_back(create_tank(sherman, 1, Local));

    std::thread r(&render);
    r.join();





//    hiex::Canvas c;
//    hiex::Canvas d;
//    hiex::Canvas e;
//    hiex::BindWindowCanvas(&c);
//    hiex::Scene sc;
//    hiex::Layer la, la2;
//    hiex::ImageBlock bl,bl2;
//    bl.SetCanvas(&d);
//    bl2.SetCanvas(&e);
//
//    bl.SetPos(600, 200);
//    e.Load_Image_Alpha(_T("../source/tiger_turret.png"), 0, 0, true, 0,0,255, false);
//
//
//
//    d.Load_Image_Alpha(_T("../source/tiger_body.png"), 0, 0, true, 0,0,255, false);
////    d.RotateImage_Alpha(PI/2);
//
//    la.push_back(&bl);
//    la2.push_back(&bl2);
//    sc.push_back(&la);
//    sc.push_back(&la2);
//    BEGIN_TASK();
//            { sc.Render(c.GetImagePointer()); }
//    END_TASK();
//    REDRAW_WINDOW();
//    la.remove_if([](hiex::ImageBlock* a){return a->bVisible;});
//    BEGIN_TASK();
//            { sc.Render(c.GetImagePointer()); }
//    END_TASK();
//    REDRAW_WINDOW();


//    BEGIN_TASK();

//            c.BindToImage(&a);
//            c.RotateImage_Alpha(5.0);
//            c.RenderTo(20, 20, hiex::GetWindowImage());
//            hiex::TransparentImage(hiex::GetWindowImage(), 10, 10, &a);
//
////        c.PutImageIn_Alpha(0, 0, &a);
//    END_TASK();
//    REDRAW_WINDOW();

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
//    draw_tank(&a.body, &a.body_mask, &a.turret, &a.turret_mask, 90.0, 0.0, 500, 500, a.offset);
//    FlushBatchDraw();

//    loadimage(&img, _T("D:/temp/tank/churchill.png"));
//    loadimage(&mask, _T("D:/temp/tank/churchill_mask.png"));
//
//    // 使用 SRCAND ROP 代码将掩码图像绘制到屏幕上
//    putimage(100, 100, &mask, SRCAND);
//
//    // 使用 SRCPAINT ROP 代码将图像绘制到屏幕上
//    putimage(100, 100, &img, SRCPAINT);
//    rotate_draw(&img, &mask, PI/2, 100+img.getwidth()/2, 100+img.getheight()/2);
    // 暂停
//    system("pause");

    // 关闭图形窗口

    for (Tank_collection* tank : tanks) {
        delete tank;
    }
}


//// 小球数量
//#define BALL_NUM 14
//
//// 小球半径
//#define RADIUS 70
//
//// 球体
//struct Ball
//{
//    hiex::ImageBlock img;
//    float x, y;
//    float vx, vy;
//};
//
//hiex::SysButton btn;			// 按钮
//bool show_outline = false;		// 是否显示轮廓
//
//int main()
//{
//    hiex::Window wnd(640, 480);			// 创建窗口
//    hiex::Canvas canvas;				// 创建画布对象
//    wnd.BindCanvas(&canvas);			// 将窗口和画布绑定
//
//    // 手动刷新双缓冲
//    //hiex::EnableAutoFlush(false);
//
//    canvas.Clear(true, BLACK);			// 设置背景色为黑色，清空画布
//
//    // 创建按钮，用于点击设置是否显示轮廓
////    btn.Create(wnd.GetHandle(), 50, 50, 120, 30, L"Hide outline");
////    btn.RegisterMessage([]() {
////        show_outline = !show_outline;
////        btn.SetText(show_outline ? L"Show outline" : L"Hide outline");
////    });
//
//    // 初始化随机数
//    srand((UINT)time(nullptr));
//
//    hiex::Scene scene;		// 场景
//    hiex::Layer layer;		// 图层
//
//    Ball balls[BALL_NUM];	// 小球
//
//    // 初始化小球
//    for (auto& i : balls)
//    {
//        // 位置和速度的初始化
//        i.x = (float)(rand() % canvas.GetWidth());
//        i.y = (float)(rand() % canvas.GetHeight());
//        i.vx = rand() % 5 * (rand() % 2 ? 2.0f : -2.0f);
//        i.vy = rand() % 5 * (rand() % 2 ? 2.0f : -2.0f);
//        if (i.vx == 0)
//            i.vx = 3;
//        if (i.vy == 0)
//            i.vy = 3;
//
//        // 小球的图像块设置
//        i.img.CreateCanvas(RADIUS * 2, RADIUS * 2);
//        i.img.GetCanvas()->Clear();
//        i.img.GetCanvas()->SolidCircle(RADIUS, RADIUS, RADIUS, true, rand() % 0xffffff);
//        ReverseAlpha(i.img.GetCanvas()->GetBuffer(), i.img.GetCanvas()->GetBufferSize());
//
//        // 设置图像块透明度
//        i.img.alpha = 200;
//        i.img.bUseSrcAlpha = true;
//
//        // 加入图像块到图层
//        layer.push_back(&i.img);
//    }
//
//    // 加入图层到场景
//    scene.push_back(&layer);
//
//    // 主循环（窗口关闭或按下按键时退出）
//    while (wnd.IsAlive() && !peekmessage(nullptr, EM_CHAR))
//    {
//        for (auto& i : balls)
//        {
//            i.x += i.vx;
//            i.y += i.vy;
//
//            // 碰撞判定
//            if (i.x - RADIUS < 0)
//            {
//                i.x = RADIUS;
//                i.vx = -i.vx;
//            }
//            if (i.x + RADIUS > canvas.GetWidth())
//            {
//                i.x = (float)canvas.GetWidth() - RADIUS;
//                i.vx = -i.vx;
//            }
//            if (i.y - RADIUS < 0)
//            {
//                i.y = RADIUS;
//                i.vy = -i.vy;
//            }
//            if (i.y + RADIUS > canvas.GetHeight())
//            {
//                i.y = (float)canvas.GetHeight() - RADIUS;
//                i.vy = -i.vy;
//            }
//
//            // 更新位置
//            i.img.SetPos((int)i.x - RADIUS, (int)i.y - RADIUS);
//        }
//
//        if (wnd.BeginTask())
//        {
//            // 渲染场景
//            scene.Render(canvas.GetImagePointer(), show_outline);
//
//            // 手动刷新双缓冲
//            //wnd.FlushDrawing();
//
//            wnd.EndTask();
//            wnd.Redraw();
//        }
//
//        // 平衡帧率
//        hiex::DelayFPS(24);
//    }
//    return 0;
//}
