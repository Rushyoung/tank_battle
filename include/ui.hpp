#ifndef __UI_HPP__
#define __UI_HPP__

#include <easyx.h>
#include <string>

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
};


class UI {
private:
    int width, height;
public:
    UI(int, int);
    void update();
    void draw_text(std::string, RGB_color, position, int);
    void draw_rect(RGB_color, position, position, bool);
    void draw_circle(RGB_color, position, int, int, bool);
    void draw_line(RGB_color, position, position, int);
    void draw_image(IMAGE, position, position, double);
};

#endif