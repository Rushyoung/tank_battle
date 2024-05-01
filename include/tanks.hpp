#ifndef __TANKS_HPP__
#define __TANKS_HPP__

namespace tank{
    class tank_base{
    private:
        double x, y;
    public:
        tank_base(double, double);
        virtual void move(double, double);
        virtual void control();
    };

    class tank_local: public tank_base{
    public:
        tank_local(double, double);
        void move(double, double);
        void control();
    };

    class tank_remote: public tank_base{
    public:
        tank_remote(double, double);
        void move(double, double);
        void control();
    };

    class tank_ai: public tank_base{
    public:
        tank_ai(double, double);
        void move(double, double);
        void control();
    };
}



#endif
