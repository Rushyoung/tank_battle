#ifndef __RENDER_HPP__
#define __RENDER_HPP__

#include <easyx.h>
#include <string>
#include <ctime>
#include <vector>

#define PI 3.14159265358979323846
#define degree(x) ((x)*PI/180.0)

namespace render{
    /**
     * @brief RBG颜色类
    */
    class color{
    private:
        COLOR16 r, g, b;
    public:
        color();
        color(COLOR16, COLOR16, COLOR16);
        color(std::string_view);
        COLOR16 get_red();
        COLOR16 get_green();
        COLOR16 get_blue();
        COLORREF get_color();
    };


    /**
     * @brief 位置类和尺寸类
    */
    struct base_tuple{
        int x, y;
        base_tuple();
        base_tuple(int, int);
        base_tuple operator+(base_tuple);
        base_tuple operator-(base_tuple);
        void move(int, int);
    };
    using position = base_tuple;
    using size = base_tuple;


    /**
     * @brief FPS 控制类
    */
    class FPS{
    private:
        int    fps;
        time_t last_render_time;
        double frame_interval;
        int    frame_count;
    public:
        FPS(int);
        void set_fps(int);
        void wait();
    };


    /**
     * @brief 渲染物体的基类
    */
    class base_render_object{
    protected:
        position default_pos;
    public:
        virtual void draw() = 0;
        virtual void draw(position&) = 0;
        virtual void draw(int, int) = 0;
        virtual void move(position&) = 0;
        virtual void move(int, int) = 0;
    };

    class render_object: protected base_render_object{
    public:
        virtual void draw(int, int) = 0;
        void draw() override;
        void draw(position&) override;
        void move(position&) override;
        void move(int, int) override;
    };

    /**
     * @brief 文本渲染类，继承自渲染物体基类
    */
    class render_text: public render_object{
    private:
        std::string font;
        std::string text;
        int size;
        color text_color;
    public:
        render_text(color, std::string_view, int);
        void set_font(std::string_view);
        void set_text(std::string_view);
        void set_color(color);
        void set_size(int);
        void draw(int, int) override;
    };
    using text = render_text;

    /**
     * @brief 矩形渲染类，继承自渲染物体基类
    */
    class render_rect: public render_object{
    private:
        color rect_color;
        size rect_size;
        bool is_filled;
    public:
        render_rect(color, size, bool);
        void set_color(color);
        void set_size(size);
        void set_filled(bool);
        void draw(int, int) override;
    };
    using rect = render_rect;

    /**
     * @brief 圆形渲染类，继承自渲染物体基类
    */
    class render_circle: public render_object{
    private:
        color circle_color;
        double radius;
        bool is_filled;
    public:
        render_circle(color, double, bool);
        void set_color(color);
        void set_radius(double);
        void set_filled(bool);
        void draw(int, int) override;
    };
    using circle = render_circle;

    /**
     * @brief 线段渲染类，继承自渲染物体基类
    */
    class render_line: public render_object{
    private:
        color line_color;
        int length;
        double angle;
        int thick;
    public:
        render_line(color, int, double=0, int=1);
        void set_color(color);
        void set_length(int);
        void set_angle(double);
        void draw(int, int) override;
    };
    using stripe = render_line;

    /**
     * @brief 基础图片渲染类
    */
    class base_image{
    private:
        IMAGE img;
        IMAGE img_output;
        std::string path;
    public:
        base_image(std::string_view);
        base_image();
        void resize(int, int);
        void rotate(double);
        void draw(int, int, DWORD=SRCCOPY);
    };

    /**
     * @brief 图片渲染类，继承自渲染物体基类
    */
    class render_pic: public render_object{
    protected:
        base_image img;
        base_image img_alpha;
        bool is_alpha;
        double rotation;
    public:
        render_pic(std::string_view);
        void resize(int, int);
        void rotate(double);
        void set_as_alpha(std::string_view);
        void draw(int, int) override;
    };
    using picture = render_pic;

    
    /**
     * @brief 窗口渲染类
    */
    class window{
    private:
        int width, height;
        
        std::vector<render_object*> default_render_list;
        std::vector<bool> enable_render_list;
        bool has_default;
        void draw_default();

        color background_color;
    public:
        window(int, int);
        ~window();
        void set_background(color);
    
        int  add_render_object(render_object*);
        const render_object* get_render_object(int);
        void remove_render_object(int);
        void enable_render_object(int);
        void clear_render_object();

        void update();

        bool is_closed();
        void retitle(std::string_view);
    };
}

#endif
