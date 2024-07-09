#ifndef DEBUG
#include "tanks.hpp"
#endif

#include "render.hpp"
#include "monitor.hpp"
#include <string>

monitor_used;

namespace tank{
    
tank_render::tank_render():
    body("../assets/tank/churchil_body.png"),
    turret("../assets/tank/churchil_turret.png")
{
    body  .set_as_alpha( render::color("#000000") );
    turret.set_as_alpha( render::color("#000000") );
    body_rotate_angle = 0;
    turret_rotate_angle = 0;
}

void tank_render::set(std::string_view name){
    /**
     * @todo
    */
}

void tank_render::draw(render::position pos){
    body  .draw(pos);
    turret.draw(pos);
}

void tank_render::draw(render::position pos, int body_angle, int turret_angle){
    if(body_angle != body_rotate_angle){
        body.rotate( degree(body_angle-body_rotate_angle) );
        body_rotate_angle = body_angle;
    }
    if(turret_angle != turret_rotate_angle){
        turret.rotate( degree(turret_angle-turret_rotate_angle) );
        turret_rotate_angle = turret_angle;
    }
    draw(pos);
}

render::picture& tank_render::get_body(){
    return body;
}

render::picture& tank_render::get_turret(){
    return turret;
}


/**
 * @brief tank_base
*/
tank_base::tank_base():
    __tank()
{
    is_rotating = false;
    is_end = false;
}

tank_base::~tank_base(){
    is_end = true;
}

void tank_base::draw(int, int){
    /*while(is_rotating){
        std::this_thread::sleep_until( std::chrono::steady_clock::now() + std::chrono::milliseconds(2) );
    }*/
    __tank.draw( default_pos );
}

void tank_base::end(){
    is_end = true;
}


/**
 * @brief tank_local
*/
tank_local::tank_local():
    tank_base()
{}

void tank_local::control(){
    /**
     * @todo
    */
    render::FPS<60> fps;
    monitor_used_as(inputs);
    double angle = 0;


    while(!is_end){
        while(angle>360){
            angle -= 360;
        }
        while(angle<0){
            angle += 360;
        }

        if(inputs->key('A')){
            printf("A\n");
            angle += 3;
            is_rotating = true;
            __tank.get_body().rotate( angle );
            is_rotating = false;
        }
        if(inputs->key('D')){
            printf("D\n");
            angle -= 3;
            is_rotating = true;
            __tank.get_body().rotate( angle );
            is_rotating = false;
        }
        fps.wait();
    }
}

}