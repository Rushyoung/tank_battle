#ifndef __UI_HPP__
#define __UI_HPP__

#include <easyx.h>
#include <string>
#include <ctime>

struct RGB_color{
    COLOR16 r, g, b;
    RGB_color();
    RGB_color(COLOR16, COLOR16, COLOR16);
    RGB_color(std::string_view);
    COLOR16 get_red();
    COLOR16 get_green();
    COLOR16 get_blue();
    COLORREF get_color();
};


struct position{
    int x, y;
    position();
    position(int x, int y);
    position operator+(position);
    position operator-(position);
};

class picture{
private:
    IMAGE img;
    IMAGE *img_ptr;
    int width, height;
    double radius;
    std::string path;
    bool is_rotated;
    bool is_loaded;
public:
    picture(std::string_view);
    const IMAGE* get_image();
    void resize(int, int);
    void rotate(double);
    void draw(position);
    void draw(int, int);
};

class picture_alpha: public picture{
private:
    IMAGE img_alpha;
public:
    picture_alpha(std::string_view, std::string_view);
    void draw(position);
};


class UI_render {
private:
    int width, height;
public:
    UI_render(int, int);
    void set_background(RGB_color);
    void update();
    void draw_text(RGB_color, std::string, position, int);
    void draw_rect(RGB_color, position, position, bool);
    void draw_circle(RGB_color, position, int, int, bool);
    void draw_line(RGB_color, position, position, int);
    void draw_image(IMAGE, position, double);
    void draw_image(std::string_view, position, position);
};

class FPS_controller {
private:
    int fps;
    int frame_time;
    time_t last_time;
    int frame_count;
public:
    FPS_controller(int);
    void wait();
};

#endif