#ifndef DEBUG
#include "ui.hpp"
#endif

#include <easyx.h>
#include <string>

RGB_color::RGB_color(){
    r = 0;
    g = 0;
    b = 0;
}

RGB_color::RGB_color(COLOR16 r, COLOR16 g, COLOR16 b){
    this->r = r;
    this->g = g;
    this->b = b;
}

RGB_color::RGB_color(std::string_view color_id){
    auto hex2int = [](std::string_view hex){
        return std::stoi(std::string(hex), nullptr, 16);
    };
    if(color_id[0] == '#'){
        r = hex2int(color_id.substr(1, 2));
        g = hex2int(color_id.substr(3, 2));
        b = hex2int(color_id.substr(5, 2));
    } else if(color_id.length() == 6){
        r = hex2int(color_id.substr(0, 2));
        g = hex2int(color_id.substr(2, 2));
        b = hex2int(color_id.substr(4, 2));
    } else {
        r = 0;
        g = 0;
        b = 0;
    }
}

COLOR16 RGB_color::get_red(){
    return r;
}

COLOR16 RGB_color::get_green(){
    return g;
}

COLOR16 RGB_color::get_blue(){
    return b;
}

COLORREF RGB_color::get_color(){
    return RGB(r, g, b);
}

position::position(){
    x = 0;
    y = 0;
}

position::position(int x, int y){
    this->x = x;
    this->y = y;
}

UI::UI(int width, int height){
    this->width = width;
    this->height = height;
    initgraph(width, height);
}

void UI::update(){
    FlushBatchDraw();
}

void UI::draw_text(RGB_color color, std::string text, position pos, int size){
    settextcolor(color.get_color());
    settextstyle(size, 0, "宋体");
    outtextxy(pos.x, pos.y, text.c_str());
}

void UI::draw_rect(RGB_color color, position start, position end, bool fill){
    setlinecolor(color.get_color());
    if(fill){
        setfillcolor(color.get_color());
        fillrectangle(start.x, start.y, end.x, end.y);
    } else {
        rectangle(start.x, start.y, end.x, end.y);
    }
}

void UI::draw_circle(RGB_color color, position center, int radius, int thickness, bool fill = true){
    setlinecolor(color.get_color());
    if(fill){
        setfillcolor(color.get_color());
        fillcircle(center.x, center.y, radius);
    } else {
        circle(center.x, center.y, radius);
    }
}

void UI::draw_line(RGB_color color, position start, position end, int thickness){
    setlinecolor(color.get_color());
    setlinestyle(PS_SOLID, thickness);
    line(start.x, start.y, end.x, end.y);
}

void UI::draw_image(IMAGE img, position start, double angle = 0.0){
    IMAGE output = img;
    if(angle != 0.0){
        rotateimage(&output, &img, angle);
    }
    putimage(start.x, start.y, &output);
}

void UI::draw_image(std::string_view path, position start, position size){
    IMAGE img;
    loadimage(&img, std::string(path).c_str(), size.x, size.y);
    putimage(start.x, start.y, &img);
}
