#include "render.hpp"
#include <windows.h>
#include <cmath>
#include <chrono>
#include <thread>
#include <iostream>

#define key GetAsyncKeyState

int main(){
    render::window window(720, 720);
    render::monitor inputs;
    window.retitle("Render Test");

    render::FPS<60> fps;
    
    render::picture back("../assets/image.jpg");
    window.bind(&back);

    render::picture alist("../assets/tank/churchil_body.png");
    alist.set_as_alpha( render::color("#000000") );

/*
    render::picture alist("../assets/tank/churchil_body.png");
    alist.set_as_alpha( render::color("#000000") );
    alist.rotate(90);
    alist.move(300, 300);;*/


    window.bind(&alist);
    

    
    double angle = 0;

	int count = 0;
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    

    while(true){
        if(key(VK_ESCAPE) or window.is_closed()){
            break;
        }

        if(key('A')){
            angle += 3;
            alist.rotate(angle);
        }
        if(key('D')){
            angle -= 3;
            alist.rotate(angle);
        }

        if(key('W')){
            //沿着角度移动, 初始方向为向右
            alist.move(
                  3 * cos( degree(angle) ),
                - 3 * sin( degree(angle) )
            );
        }

        if(window.is_closed()){
            break;
        }

        fps.wait();
        window.update();
        inputs.clear();
        count ++;
        if(count == 60){
            std::cout<< "a second passed\n";
            count = 0;
        }
    }
    

    // closegraph();
    // 关闭easyx窗口
    closegraph();

    return 0;
}