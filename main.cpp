#include <windows.h>
#include <cmath>
#include <chrono>
#include <thread>
#include <iostream>

#include "render.hpp"
#include "tanks.hpp"
#include "monitor.hpp"

enable_monitor_shared;

int main(){
    monitor_init(inputs);
    monitor_share(inputs);

    render::window window(720, 720);
    window.retitle("Render Test");
    
    monitor_start(inputs);

    render::FPS<60> fps;
    
    render::picture back("../assets/image.jpg");
    window.bind(&back);

    render::picture alist("../assets/tank/churchil_body.png");
    alist.set_as_alpha( render::color("#000000") );
    window.bind(&alist);

    render::rect rects( render::color("#FF0000") , render::size(100, 100) , false);
    window.bind(&rects);


    double angle = 0;

	int count = 0;
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    

    while(true){
        if(inputs.key(VK_ESCAPE) or window.is_closed()){
            break;
        }


        while(angle>360){
            angle -= 360;
        }
        while(angle<0){
            angle += 360;
        }

        if(inputs.key('A')){
            angle += 3;
            alist.rotate(angle);
        }
        if(inputs.key('D')){
            angle -= 3;
            alist.rotate(angle);
        }

        if(inputs.key('W')){
            //沿着角度移动, 初始方向为向右
            alist.move(
                3 * cos( degree(angle) ),
                -3 * sin( degree(angle) )
            );
        }

        monitor::mouse_pos pos = inputs.mouse(mouse_token::left_down);
        if(pos ISNT ZERO){
            std::cout << "mouse position: " << pos.x << ", " << pos.y << std::endl;
        }

        if(window.is_closed()){
            break;
        }

        fps.wait();
        window.update();
        count ++;
        if(count == 60){
            //std::cout<< "a second passed\n";
            count = 0;
        }
    }
    

    // closegraph();
    // 关闭easyx窗口
    closegraph();

    return 0;
}