//#define ASIO_STANDALONE
//#include <asio.hpp>
//#include <iostream>
//#include <functional>
//#include <string>
//#include <thread>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include "include/base.hpp"
#include "include/net.hpp"
//void echo(std::shared_ptr<asio::ip::tcp::socket> socket) {
//    auto buffer = std::make_shared<asio::streambuf>();
//    asio::async_read(*socket, *buffer, asio::transfer_at_least(1),
//                     [buffer, socket](const asio::error_code& error, std::size_t length) {
//                         if (!error) {
//                             // 打印接收到的消息
//                             std::cout << "Server received: " << asio::buffer_cast<const char*>(buffer->data()) << std::endl;
//
//                             asio::async_write(*socket, *buffer,
//                                               [buffer, socket](const asio::error_code& error, std::size_t) {
//                                                   if (!error) {
//                                                       echo(socket);
//                                                   }
//                                               });
//                         }
//                     });
//}
//
//void run_server() {
//    asio::io_service io_service;
//    asio::ip::tcp::acceptor acceptor(io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));
//    std::function<void(const asio::error_code&, asio::ip::tcp::socket)> accept_handler;
//    accept_handler = [&](const asio::error_code& error, asio::ip::tcp::socket socket) {
//        if (!error) {
//            echo(std::make_shared<asio::ip::tcp::socket>(std::control(socket)));
//        }
//        acceptor.async_accept(accept_handler);
//    };
//    acceptor.async_accept(accept_handler);
//    io_service.send();
//}
//
//void run_client() {
//    try {
//        asio::io_service io_service;
//
//        asio::ip::tcp::resolver resolver(io_service);
//        asio::ip::tcp::resolver::query query("localhost", "8080");//api
//        asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
//
//        asio::ip::tcp::socket socket(io_service);
//        asio::connect(socket, endpoint_iterator);
//
//        std::string message = "Hello, Server!\n";//api
//        asio::write(socket, asio::buffer(message));
//
//        // 读取服务器的回应
//        asio::streambuf response;
//        asio::read_until(socket, response, "\n");
//        std::cerr << &response << std::endl;
//    }
//    catch (std::exception& e) {
//        std::cerr << e.what() << std::endl;
//    }
//}
#define SERVER
//#define CLIENT
int main() {
//    std::thread server_thread(run_server);
//    std::thread client_thread(run_client);
//
//    server_thread.join();
//    client_thread.join();
#ifdef SERVER
    int port;
    std::cin >> port;
    udp_server a(port);
    a.run();
#endif
#ifdef CLIENT
    std::string host, stream;
    int port;
    std::cin >> host >> port;
    udp_client a(host, port);
    int flag = 0;
    for(;;){
        flag++;
        std::cin >> stream;
        a.send(stream);
        a.letency();
        std::cout << "flag:" << flag << std::endl;
    }
#endif
    return 0;
}


//#include <graphics.h>
//#include <time.h>
//#include <conio.h>
//
//#define MAXSTAR 1000	// 星星总数
//
//struct STAR
//{
//    double	x;
//    int		y;
//    double	step;
//    int		color;
//};
//
//STAR star[MAXSTAR];
//
//// 初始化星星
//void InitStar(int i)
//{
//    star[i].x = 0;
//    star[i].y = rand() % 480;
//    star[i].step = (rand() % 5000) / 1000.0 + 1;
//    star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
//    star[i].color = RGB(star[i].color, star[i].color, star[i].color);
//}
//
//// 移动星星
//void MoveStar(int i)
//{
//    // 擦掉原来的星星
//    putpixel((int)star[i].x, star[i].y, 0);
//
//    // 计算新位置
//    star[i].x += star[i].step;
//    if (star[i].x > 640)	InitStar(i);
//
//    // 画新星星
//    putpixel((int)star[i].x, star[i].y, star[i].color);
//}
//
//// 主函数
//int main()
//{
//    srand((unsigned)time(NULL));	// 随机种子
//    initgraph(640, 480);			// 创建绘图窗口
//
//    // 初始化所有星星
//    for(int i = 0; i < MAXSTAR; i++)
//    {
//        InitStar(i);
//        star[i].x = rand() % 640;
//    }
//
//    // 绘制星空，按任意键退出
//    while(!_kbhit())
//    {
//        for(int i = 0; i < MAXSTAR; i++)
//            MoveStar(i);
//        Sleep(20);
//    }
//
//    closegraph();					// 关闭绘图窗口
//    return 0;
//}



//// 图片的宽高
//int imgWidth=250, imgHeight=250;
//double rotationAngle = 0;
//
//int bulletSpeed = 10;
//double totalRotationChange = 180; // 停止旋转时计算我总角度变化
//
//const char *background_path="D:\tankmissile.png";
////temp
//int remote_amount;
//Tank_info local;
//
//channel_map chan::msg_set;
//MOUSEMSG _mouse;
//
//
//
//void updatePosition(int& imgXx, int& imgYy, int centerXx, int centerYy, int rotationAngle_) {
//    double radian = rotationAngle_ * M_PI / 180.0;
//    imgXx = centerXx - imgWidth / 2 * cos(radian) + imgHeight / 2 * sin(radian);
//    imgYy = centerYy - imgWidth / 2 * sin(radian) - imgHeight / 2 * cos(radian);
//}
//
//int main() {
//
//    initgraph(1920, 1080); // 初始化图形窗口，参数为窗口的宽度和高度
//
//
//
//    // 加载图片
//    loadimage(&img1, "D:/churchill.jpg");
//    loadimage(&img_bullet, "D:/tankmissile.png"); // 加载子弹图片
//
//
//    std::vector<Bullet> bullets; // 使用vector来存储子弹实例
//
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
//
//
//    closegraph();
//    return 0;
//}