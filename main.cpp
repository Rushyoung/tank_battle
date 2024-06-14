#include "render.hpp"
#include <windows.h>
#include <cmath>

#define key(x) (GetAsyncKeyState(x)&0x8000)

#define render_cast(type, value) \
({ \
    const_cast<type*>(\
        static_cast<const type*>(value) \
    ); \
})

int main(){
    render::window window(720, 720);
    window.retitle("Render Test");
    render::FPS fps(60);
    render::rect block(render::color(255, 0, 0), render::size(10, 10), true);
    render::picture back("../assets/image.jpg");
    int backid = window.add_render_object(&back);
    window.add_render_object(&block);
    render::picture alist("../assets/alist_ico.png");
    alist.set_as_alpha("../assets/alist_ico.mask.jpg");
    int id = window.add_render_object(&alist);
    render::picture backup = alist;
    window.add_render_object(&backup);
    
    double angle = 0;
    

    while(true){
        if(key(VK_UP)){
            alist.move(0, -5);
        }
        if(key(VK_DOWN)){
            alist.move(0, 5);
        }
        if(key(VK_LEFT)){
            alist.move(-5, 0);
        }
        if(key(VK_RIGHT)){
            alist.move(5, 0);
        }
        if(key('A')){
            angle += 0.5;
            render_cast(render::render_pic, window.get_render_object(id))->rotate(angle);
        }
        if(key('C')){
            window.remove_render_object(id);
        }
        if(key('D')){
            window.enable_render_object(id);
        }
        if(window.is_closed()){
            break;
        }

        fps.wait();
        window.update();
    }
    

    // closegraph();
    // 关闭easyx窗口
    closegraph();

    return 0;
}