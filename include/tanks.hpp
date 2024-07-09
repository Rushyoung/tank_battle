#ifndef __TANKS_HPP__
#define __TANKS_HPP__

#include <render.hpp>
#include <string_view>

namespace tank{
    class tank_render{
    private:
        render::picture body;
        render::picture turret;
        int body_rotate_angle;
        int turret_rotate_angle;
    public:
        tank_render();
        void set(std::string_view);
        void draw(render::position);
        void draw(render::position, int, int);
        render::picture& get_body();
        render::picture& get_turret();
    };

    class tank_base: public render::drawable{
    private:
        tank_render __tank;
    public:
        tank_base();
        virtual void control() = 0;
        void draw(int, int) override;
    };

    class tank_local: public tank_base{
    public:
        tank_local();
        void control();
    };

    class tank_remote: public tank_base{
    public:
        tank_remote();
        void control();
    };

    class tank_ai: public tank_base{
    public:
        tank_ai();
        void control();
    };
}



#endif
