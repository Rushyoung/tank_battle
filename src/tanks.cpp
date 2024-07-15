#ifndef DEBUG
#include "tanks.hpp"
#endif

#include "render.hpp"
#include "channel.hpp"

#include <cmath>
#include <string>
#include <format>

const render::position offset_pos(75, 75);
    
tank_render::tank_render( std::string_view name):
    body( std::format("../assets/tank/{}_body.png", name) ),
    turret( std::format("../assets/tank/{}_turret.png", name) )
{
    body  .set_as_alpha( render::color("#000000") );
    turret.set_as_alpha( render::color("#000000") );
    body_rotate_angle = 0;
    turret_rotate_angle = 0;
    default_pos = default_pos + offset_pos;
}

void tank_render::draw(int x, int y){
    body  .draw( default_pos - offset_pos );
    turret.draw( default_pos - offset_pos );
}

render::picture& tank_render::get_body(){
    return body;
}

render::picture& tank_render::get_turret(){
    return turret;
}

int tank_render::get_turret_angle(){
    return turret_rotate_angle;
}

render::position tank_render::get_position(){
    return default_pos;
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
    move(
         distance * std::cos( degree(body_rotate_angle) ),
        -distance * std::sin( degree(body_rotate_angle) )
    );
}