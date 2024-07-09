#ifndef __INPUT_MONITOR_HPP__
#define __INPUT_MONITOR_HPP__

#include <thread>
#include <iostream>
#include <windows.h>

enum class mouse_token{
    left_down   = 1,
    left_dbclk  = 3,
    right_down  = 4,
    right_dbclk = 6,
    position
}; 


/**
 * @brief 消息检测类，继承自智能指针
*/
class monitor{
private:
    uint8_t key_state[256];
    POINT pos, mouse_state[16];
public:
    monitor();
    ~monitor(){
        std::cout << "monitor exit" << std::endl;
    }
    void clear();
    bool key(int);
    using mouse_pos = POINT;
    mouse_pos mouse(mouse_token = mouse_token::position);

    void message_loop();
};


#define IS   ==
#define ISNT !=
#define ZERO POINT({0, 0})
bool operator==(POINT, POINT);


/**
 * @brief 宏定义，允许分享一个monitor对象
*/
#define enable_monitor_shared monitor *monitor_shared = nullptr


/**
 * @brief 宏定义，分享一个monitor对象
*/
#define monitor_share(x) monitor_shared = x


/**
 * @brief 宏定义，在该文件中使用分享的monitor对象
*/
#define monitor_used extern monitor *monitor_shared


/**
 * @brief 宏定义，使用分享的monitor对象
*/
#define monitor_used_as(x) monitor *x = monitor_shared


/**
 * @brief 宏定义，定义一个monitor对象
*/
#define monitor_init(x) static monitor *x = new monitor()

/**
 * @brief 宏定义，启动新的线程以运行消息循环
*/
#define monitor_start(x) std::thread( &monitor::message_loop, x ).detach()


#endif