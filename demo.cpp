#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>

const double FPS = 60.0;
const double FRAME_TIME = 1000.0 / FPS;

struct tank{
    virtual void control() = 0; // pure
};

struct tank_local: tank{
    tank_local(){
        std::cout << "tank_local\n";
    }
    void control() override{
        while(true){
            std::cout << "tank_local control\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_TIME));
        }
    }
};

struct tank_remote: tank{
    tank_remote(){
        std::cout << "tank_remote\n";
    }
    void control() override{
        while(true){
            std::cout << "tank_remote control\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_TIME));
        }
    }
};

struct tank_ai: tank{
    tank_ai(){
        std::cout << "tank_ai\n";
    }
    void control() override{
        while(true){
            std::cout << "tank_ai control\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(FRAME_TIME * 1.5));
        }
    }
};

void thread_stop(std::thread& t){
    std::thread::native_handle_type native_handle = t.native_handle();
#ifdef _WIN32
    HANDLE handle = OpenThread(THREAD_TERMINATE, FALSE, native_handle);
    TerminateThread(handle, 0);
#elif __linux__
    pthread_cancel(handle);
#endif
    t.join();
}

int main(){
    // game start
    tank_local local;
    tank_remote remote;
    tank_ai ai;
    // all of the control functions are running in its own thread
    std::thread t1(&tank_local::control, &local);
    std::thread t2(&tank_remote::control, &remote);
    std::thread t3(&tank_ai::control, &ai);
    // main loop
    while(true){
        chan("local").receive();
        // game logic
        if(is_ai_used){
            chan("ai").receive();
        }
        if(is_remote_used){
            chan("remote").receive();
        }
        for(auto bull: bullets){
            // 子弹碰撞逻辑
            if(tank_local.is_hit(bull)){
                // 中断线程
                thread_stop(t1);
            }
            // ....
        }

        UI_update();

        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_TIME));
    }
}