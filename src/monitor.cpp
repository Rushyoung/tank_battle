#ifndef DEBUG
#include "monitor.hpp"
#endif

#include <easyx.h>

bool operator==(POINT a, POINT b){
    return a.x == b.x and a.y == b.y;
}

bool operator!(POINT a){
    return a.x != 0 or a.y != 0;
}


monitor::monitor():
    pos({0, 0}), mouse_state({})
{
    clear();
}

void monitor::clear(){
    for(int i=0; i<256; i++){
        key_state[i] = 0;
    }
}

bool monitor::key(int key){
    if(key < 0 || key > 255){
        return false;
    }
    if(key_state[key] & 0b0100 ){
        key_state[key] ^= 0b0100;
        return true;
    }
    if(key_state[key]){
        return true;
    }
    return false;
}

monitor::mouse_pos monitor::mouse(mouse_token token){
    if(token == mouse_token::position){
        return pos;
    }
    monitor::mouse_pos ret = mouse_state[static_cast<int>(token)];
    mouse_state[static_cast<int>(token)] = {0, 0};
    return ret;
}


void monitor::message_loop(){
    ExMessage msg;
    while( true ){
        msg = getmessage(EX_MOUSE | EX_KEY) ;
        switch(msg.message){
            // 键盘事件
            // 自上次检测以来，按下了某个键且未释放 0b0101
            // 自上次检测以来，释放了某个键 0b0100
            case WM_KEYDOWN:
                if(key_state[msg.vkcode] & 0b0001)
                    break;
                key_state[msg.vkcode] = 0b0101;
                break;
            case WM_KEYUP:
                if(key_state[msg.vkcode] & 0b0001)
                    key_state[msg.vkcode] = 0b0100;
                break;
            case WM_MOUSEMOVE ... WM_MOUSEHWHEEL:
                pos = {msg.x, msg.y};
                mouse_state[ msg.message - WM_MOUSEMOVE ] = pos;
        }
    }
}