#ifndef DEBUG
#include "tanks.hpp"
#endif

#include "render.hpp"
#include "channel.hpp"

#include <cmath>
#include <string>
#include <format>


    
tank_render::tank_render( std::string_view name):
    body( std::format("../assets/tank/{}_body.png", name) ),
    turret( std::format("../assets/tank/{}_turret.png", name) )
{
    body  .set_as_alpha( render::color("#000000") );
    turret.set_as_alpha( render::color("#000000") );
    body_rotate_angle = 0;
    turret_rotate_angle = 0;
}

void tank_render::draw(int x, int y){
    body  .draw();
    turret.draw();
}

render::picture& tank_render::get_body(){
    return body;
}

render::picture& tank_render::get_turret(){
    return turret;
}


void tank_render::rotate_body(int angle){
    body_rotate_angle += angle;
    body_rotate_angle %= 360;
    body.rotate( body_rotate_angle );
}

void tank_render::rotate_turret(int angle){
    turret_rotate_angle += angle;
    turret_rotate_angle %= 360;
    turret.rotate( turret_rotate_angle );
}

void tank_render::forward(int distance){
    body.move(
        // 角度轉弧度
         distance * std::cos( degree(body_rotate_angle) ),
        -distance * std::sin( degree(body_rotate_angle) )
    );
    turret.move(
         distance * std::cos( degree( body_rotate_angle ) ),
        -distance * std::sin( degree( body_rotate_angle ) )
    );
}