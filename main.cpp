#include <chrono>
#include <thread>

#include <iostream>

#include <string>
#include <vector>
#include <map>

#include "render.hpp"
#include "tanks.hpp"
#include "monitor.hpp"
#include "channel.hpp"

#include "functions.hpp"

#define var auto&
#define elif else if
#define in :
#define lambda []

#define time_point std::chrono::steady_clock::time_point
#define get_now std::chrono::steady_clock::now

enable_monitor_shared;


std::map<std::string, tank_render> tanks;


void local_control(){
    render::FPS<55> fps;
    monitor_used_as(inputs);
    std::string cmd;
    double turret_angle = 0;
    while(true){
        cmd.clear();
        if(inputs->key('W')){
            cmd.append("W");
        } elif (inputs->key('S')){
            cmd.append("S");
        }
        if(inputs->key('A')){
            cmd.append("A");
        } elif (inputs->key('D')){
            cmd.append("D");
        }

        render::position   pos_1 = tanks["local"].get_position();
        monitor::mouse_pos pos_2 = inputs->mouse();
        double now_angle = angle_between_points( pos_1.x, pos_1.y, pos_2.x, pos_2.y);
        auto   angle_diff = lambda(double a, double b) -> double{
            double a_deal = ((a + 360) > 360) ? a : a + 360;
            double b_deal = ((b + 360) > 360) ? b : b + 360;
            return a_deal - b_deal;
        };
        double diff = angle_diff(turret_angle, now_angle);
        int    sign = 1;
        if( ( -360 <= diff && diff < -180 ) ||
            (    0 <= diff && diff <  180 ) ){
            sign = -1;
        }
        int rotate_wanted = 0;
        if( std::abs(diff) > 8){
            rotate_wanted = 8;
        } else {
            rotate_wanted = static_cast<int>(std::round(std::abs(diff)));
        }
        turret_angle += rotate_wanted * sign;
        turret_angle = int(turret_angle + 1080) % 360;
        if(sign == 1){
            cmd.append(rotate_wanted, 'a');
        } elif (sign == -1){
            cmd.append(rotate_wanted, 'd');
        }

        if(cmd.empty()){
            cmd.append("V");
        }
        chan("local").send(cmd);
        fps.wait();
    }
}

int main(){
    // 注册消息轮询，并启用共享
    monitor_init(inputs);
    monitor_share(inputs);


    // 初始窗口，改名，设置背景色
    render::window window(720, 720);
    window.retitle("tank game");
    window.set_background(render::color("#FFFFFF"));
    
    // 启动消息轮询
    monitor_start(inputs);

    // 定义一个FPS计数器，一个计数器，一个开始时间
    render::FPS<60> fps;
	int count = 0;
	time_point start = get_now();
    
    // 初始化坦克
    std::vector<std::string> tank_running_list = {"local"};
    for(var name in tank_running_list){
        tanks[name] = tank_render("churchil");
        window.bind(&tanks[name]);
    }

    // 定义一个图片，设置为透明，并绑定到窗口
    render::picture alist("../assets/alist_ico.png");
    alist.set_as_alpha(render::color("#000000"));
    window.bind(&alist);
    
    // 启动一个线程，用于本地控制
    std::thread local_thread(local_control);

    // 主循环
    while(true){
        if(window.is_closed()){ // 如果窗口关闭，退出主循环
            break;
        }

        for(var name in tank_running_list){ // 遍历坦克列表：local, remote, ai
            std::string cmd_str = chan(name).recv(); // 从消息通道中接收消息
            int turret_angle = 0;
            for(var cmd in cmd_str){
                switch(cmd){                // 根据消息内容，执行相应的操作
                    case 'W':
                        tanks[name].forward( 5);
                        break;
                    case 'S':
                        tanks[name].forward(-3);
                        break;
                    case 'A':
                        tanks[name].rotate_body( 3);
                        break;
                    case 'D':
                        tanks[name].rotate_body(-3);
                        break;
                    case 'a':
                        turret_angle += 1;
                        break;
                    case 'd':
                        turret_angle -= 1;
                        break;
                    case 'V':
                        [[fallthrough]];
                    default:
                        break;
                }
            }
            if(turret_angle){
                tanks[name].rotate_turret(turret_angle);
            }
        }

        // FPS限制，更新窗口
        fps.wait();
        window.update();

        // 计算FPS，每秒输出一次
        count ++;
        if(count == 60){
            time_point end = get_now();
            std::chrono::duration<double> diff = end - start;
            std::cout << "[log] A second pass, and fps is " << count / diff.count() << "\n";
            count = 0;
            start = end;
        }
    }

    // 关闭easyx窗口
    closegraph();

    return 0;
}