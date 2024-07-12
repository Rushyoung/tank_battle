#ifndef __TANKS_HPP__
#define __TANKS_HPP__

#include <render.hpp>
#include <string_view>


class tank_render: public render::drawable{
private:
    render::picture body;
    render::picture turret;
    int body_rotate_angle;
    int turret_rotate_angle;
public:
    tank_render(std::string_view = "churchil");

    render::picture& get_body();
    render::picture& get_turret();
    void rotate_body(int);
    void rotate_turret(int);
    void forward(int);

    using render::drawable::draw;
    void draw(int, int) override;
};


#endif
