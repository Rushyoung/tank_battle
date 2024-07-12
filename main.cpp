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

#define var auto&
#define elif else if
#define in :

#define time_point std::chrono::steady_clock::time_point
#define get_now std::chrono::steady_clock::now

enable_monitor_shared;

void local_control(){
    render::FPS<55> fps;
    monitor_used_as(inputs);
    std::string cmd;
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

        if(cmd.empty()){
            cmd.append("V");
        }
        chan("local").send(cmd);
        fps.wait();
    }
}

int main(){
    monitor_init(inputs);
    monitor_share(inputs);

    render::window window(720, 720);
    window.retitle("tank game");
    window.set_background(render::color("#FFFFFF"));
    
    monitor_start(inputs);

    render::FPS<60> fps;

	int count = 0;
	time_point start = get_now();
    
    std::vector<std::string> tank_running_list = {"local"};
    std::map<std::string, tank_render> tanks;
    for(auto& name: tank_running_list){
        tanks[name] = tank_render("churchil");
        window.bind(&tanks[name]);
    }

    render::picture alist("../assets/alist_ico.png");
    alist.set_as_alpha(render::color("#000000"));
    window.bind(&alist);
    
    std::thread local_thread(local_control);

    while(true){
        if(inputs->key(VK_ESCAPE) or window.is_closed()){
            break;
        }

        for(var name in tank_running_list){
            std::string cmd_str = chan(name).recv();
            for(var cmd in cmd_str){
                switch(cmd){
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
                    case 'V':
                        [[fallthrough]];
                    default:
                        break;
                }
            }
        }

        fps.wait();
        window.update();
        count ++;
        if(count == 60){
            time_point end = get_now();
            std::chrono::duration<double> diff = end - start;
            std::cout << "[log] A second pass, and fps is " << count / diff.count() << "\n";
            count = 0;
            start = end;
        }
    }
    

    // closegraph();
    // 关闭easyx窗口
    closegraph();

    return 0;
}