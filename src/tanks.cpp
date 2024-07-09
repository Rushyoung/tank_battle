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

tank_base::tank_base():
    __tank()
{}

void tank_base::draw(int, int){
    __tank.draw( default_pos );
}


tank_local::tank_local():
    tank_base()
{}

void tank_local::control(){
    /**
     * @todo
    */
    
}

}