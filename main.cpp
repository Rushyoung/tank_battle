#include "render.hpp"
#include <windows.h>

#define key(x) (GetAsyncKeyState(x)&0x8000)

int main(){
    render::window window(600, 480);
    render::FPS fps(60);
    render::rect block(render::color(255, 0, 0), render::size(50, 50), true);
    render::position pos(0, 0);

    while(true){
        if(key(VK_UP)){
            pos.move(0, -5);
        } else if(key(VK_DOWN)){
            pos.move(0, 5);
        } else if(key(VK_LEFT)){
            pos.move(-5, 0);
        } else if(key(VK_RIGHT)){
            pos.move(5, 0);
        } else if(key(VK_ESCAPE)){
            break;
        }
        block.draw(pos.x, pos.y);
        window.update();
        fps.wait();
    }
    

    // closegraph();
    closegraph();
    return 0;
}