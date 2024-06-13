#ifndef __RENDER_HPP__
#define __RENDER_HPP__

#include <easyx.h>
#include <string>
#include <ctime>
#include <vector>

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
    class render_object{
    public:
        void draw(position&);
        virtual void draw(int, int) = 0;
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
     * @brief 图片渲染类，继承自渲染物体基类
    */
    class render_pic: public render_object{
    protected:
        IMAGE img;
        IMAGE img_alpha;
        double rotation;
        std::string path;
        bool is_rotated;
        bool is_loaded;
    public:
        render_pic(std::string_view);
        void resize(int, int);
        void rotate(double);
        void set_as_alpha();
        void draw(int, int) override;
    };
    using picture = render_pic;

    
    /**
     * @brief 窗口渲染类
    */
    class window{
    private:
        int width, height;
        
        std::vector<render_object*> background_objects;
        IMAGE background;
        bool has_background;
        void draw_background();
        void update_background();

        color background_color;
    public:
        window(int, int);
        ~window();
        void set_background(color);
        void add_background(render_object*);
        void update();
    };
}

#endif
