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

position position::operator+(position pos){
    return position(x+pos.x, y+pos.y);
}

position position::operator-(position pos){
    return position(x-pos.x, y-pos.y);
}


UI_render::UI_render(int width, int height){
    this->width = width;
    this->height = height;
    initgraph(width, height);
}


void UI_render::set_background(RGB_color color){
    setbkcolor(color.get_color());
    cleardevice();
}


void UI_render::update(){
    FlushBatchDraw();
    BeginBatchDraw();
    cleardevice();
}

void UI_render::draw_text(RGB_color color, std::string text, position pos, int size){
    settextcolor(color.get_color());
    settextstyle(size, 0, "宋体");
    outtextxy(pos.x, pos.y, text.c_str());
}

void UI_render::draw_rect(RGB_color color, position start, position end, bool fill){
    setlinecolor(color.get_color());
    if(fill){
        setfillcolor(color.get_color());
        fillrectangle(start.x, start.y, end.x, end.y);
    } else {
        rectangle(start.x, start.y, end.x, end.y);
    }
}

void UI_render::draw_circle(RGB_color color, position center, int radius, int thickness, bool fill = true){
    setlinecolor(color.get_color());
    if(fill){
        setfillcolor(color.get_color());
        fillcircle(center.x, center.y, radius);
    } else {
        circle(center.x, center.y, radius);
    }
}

void UI_render::draw_line(RGB_color color, position start, position end, int thickness){
    setlinecolor(color.get_color());
    setlinestyle(PS_SOLID, thickness);
    line(start.x, start.y, end.x, end.y);
}

void UI_render::draw_image(IMAGE img, position start, double angle = 0.0){
    IMAGE output = img;
    if(angle != 0.0){
        rotateimage(&output, &img, angle);
    }
    putimage(start.x, start.y, &output);
}

void UI_render::draw_image(std::string_view path, position start, position size){
    IMAGE img;
    loadimage(&img, std::string(path).c_str(), size.x, size.y);
    putimage(start.x, start.y, &img);
}

picture::picture(std::string_view path){
    loadimage(&img, path.data());
    width  = img.getheight();
    height = img.getwidth();
    radius = 0;
    this->path = std::string(path);
    is_loaded = true;
    is_rotated = false;
    img_ptr = &img;
}

const IMAGE* picture::get_image(){
    if(!is_loaded){
        loadimage(&img, path.c_str(), width, height);
        is_loaded = true;
    }
    if(is_rotated){
        if(img_ptr != nullptr){
            delete img_ptr;
        }
        img_ptr = new IMAGE;
        rotateimage(img_ptr, &img, radius);
    }
    return img_ptr;
}

void picture::resize(int width, int height){
    this->width = width;
    this->height = height;
    is_loaded = false;
}

void picture::rotate(double angle){
    radius = angle;
    is_rotated = true;
}

void picture::draw(int x, int y){
    putimage(x, y, get_image());
}

void picture::draw(position pos){
    putimage(pos.x, pos.y, get_image());
}

picture_alpha::picture_alpha(std::string_view path, std::string_view alpha_path)
    : picture(path){
    loadimage(&img_alpha, alpha_path.data());
}

void picture_alpha::draw(position pos){
    putimage(pos.x, pos.y, get_image(), SRCINVERT);
}


FPS_controller::FPS_controller(int fps){
    this->fps = fps;
    frame_time = 1000 / fps;
    last_time = time(nullptr);
}

void FPS_controller::wait(){
    frame_count++;
    time_t current_time = time(nullptr);
    if(current_time - last_time < frame_time){
        Sleep(frame_time - current_time + last_time);
    }
    last_time = time(nullptr);
}