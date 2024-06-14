#include "render.hpp"
#include <windows.h>
#include <cmath>

#define key(x) (GetAsyncKeyState(x)&0x8000)
#define degree(x) ((x) * 3.14159265358979323846 / 180)

int main(){
    render::window window(720, 720);
    setorigin(0, 0);
    render::FPS fps(60);
    render::rect block(render::color(255, 0, 0), render::size(10, 10), true);
    render::picture back("../assets/image.jpg");
    window.add_background(&back);
    window.add_background(&block);
    
    double angle = 0;
    

    while(true){
        if(key(VK_UP)){
            block.move(0, -5);
        } else if(key(VK_DOWN)){
            block.move(0, 5);
        } else if(key(VK_LEFT)){
            block.move(-5, 0);
        } else if(key(VK_RIGHT)){
            block.move(5, 0);
        } else if(key(VK_ESCAPE) || key(VK_SPACE) || key('Q')){
            break;
        } else if(key('A')){
            angle += 0.5;
            back.rotate(angle);
        }

        window.update();
        fps.wait();
    }
    

    // closegraph();
    return 0;
}