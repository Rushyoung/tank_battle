#include "ui.hpp"
#include <windows.h>

#define key(x) (GetAsyncKeyState(x)&0x8000)

int main(){
    UI_render ui(800, 600);
    FPS_controller fps(60);

    RGB_color white("#FFFFFF");
    RGB_color black(0, 0, 0);

    ui.set_background(white);

    position rect_pos(0, 0);
    position rect_size(200, 200);

    while(1){
        ui.update();
        ui.draw_rect(black, rect_pos, rect_pos+rect_size, true);
        if(key(VK_UP)){
            rect_pos.y -= 5;
        } else if(key(VK_DOWN)){
            rect_pos.y += 5;
        } else if(key(VK_LEFT)){
            rect_pos.x -= 5;
        } else if(key(VK_RIGHT)){
            rect_pos.x += 5;
        }
        fps.wait();
    }
}