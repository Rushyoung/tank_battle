#ifndef __RENDER_HPP__
#define __RENDER_HPP__

#include <easyx.h>
#include <string>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>
#include <set>
#include <memory>

#define PI 3.14159265358979323846
#define degree(x) ((x)*PI/180.0)

/**
 * @brief 画图函数, 用于绘制图片, 改善了原函数不能设置透明度、绘制透明图片的问题
*/
void placeimage(IMAGE* pSrcImage, int x, int y, double opacity=1.0, DWORD ingoreColor=0x000000);


/**
 * @brief 旋转图片函数, 用于优雅地旋转图片, 适用带有透明度的图片
 * @warning 该函数会使图片变大，请不要在循环中使用
*/
void whirlimage(IMAGE *dstimg, IMAGE *srcimg, double radian, bool autosize = true);


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
        double x, y;
        base_tuple();
        base_tuple(double, double);
        base_tuple operator+(base_tuple);
        base_tuple operator-(base_tuple);
        void move(double, double);
    };
    using position = base_tuple;
    using size = base_tuple;


    /**
     * @brief FPS 控制类
    */
    template<int FPS_count>
    class FPS{
    private:
        std::chrono::duration<double, std::ratio<1, FPS_count>> time_between_frames;
        std::chrono::time_point<std::chrono::steady_clock, decltype(time_between_frames)> wake_time_point;
    public:
        FPS(){
            time_between_frames = std::chrono::duration<double, std::ratio<1, FPS_count>>(1);
            wake_time_point = std::chrono::steady_clock::now();
        }
        void wait(){
            wake_time_point += time_between_frames;
            std::this_thread::sleep_until(wake_time_point);
        }
    };


    /**
     * @brief 渲染物体的基类
    */
    class base_render_object{
    protected:
        position default_pos;
    public:
        virtual void draw() = 0;
        virtual void draw(position) = 0;
        virtual void draw(int, int) = 0;
        virtual void move(position) = 0;
        virtual void move(double, double) = 0;
    };

    class render_object: protected base_render_object{
    public:
        virtual void draw(int, int) = 0;
        void draw() override;
        void draw(position) override;
        void move(position) override;
        void move(double, double) override;
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
        using render_object::draw;
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
        using render_object::draw;
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
        using render_object::draw;
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
        using render_object::draw;
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
        void place(int, int, DWORD=0x000000);
    };

    /**
     * @brief 图片渲染类，继承自渲染物体基类
    */
    class render_pic: public render_object{
    protected:
        base_image img;
        base_image img_alpha;
        bool is_alpha;
        enum class alpha_mode{
            mask_off,
            ingore_color,
        } alpha_scheme;
        color ingore_color;
        double rotation;
    public:
        using render_object::draw;
        render_pic(std::string_view);
        void resize(int, int);
        void rotate(double);
        void set_as_alpha(std::string_view);
        void set_as_alpha(color);
        void draw(int, int) override;
    };
    using picture = render_pic;


    /**
     * @brief 消息检测类，继承自智能指针
    */
    class monitor: public std::shared_ptr<monitor>{
    private:
        bool key_state[256];
    public:
        monitor();
        ~monitor();
        void clear();
        bool key(int);
        void message_loop(monitor&);
    };

    
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
    
        int  bind(render_object*);
        render_object* get_bound(int);
        void disable(int);
        void enable(int);
        void clear_all();

        void update();

        bool is_closed();
        void retitle(std::string_view);
    };


}





#define render_cast(type, value) \
({ \
    const_cast<type*>(\
        static_cast<const type*>(value) \
    ); \
})


#endif
