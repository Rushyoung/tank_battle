#ifndef DEBUG
#include "render.hpp"
#endif

#include <easyx.h>


#include <string>
#include <vector>

#include <chrono>
#include <cmath>

#include <iostream>

#include <thread>
#include <atomic>

namespace render{
    /**
     * @brief RBG颜色类
    */
    color::color(){
        r = 0;
        g = 0;
        b = 0;
    }

    color::color(COLOR16 r, COLOR16 g, COLOR16 b){
        this->r = r;
        this->g = g;
        this->b = b;
    }

    color::color(std::string_view color_id){
        auto hex2int = [](std::string_view hex){
            return std::stoi(std::string(hex), nullptr, 16);
        };
        std::string color_id_str = std::string(color_id);
        if(color_id[0] == '#'){
            color_id_str = color_id_str.substr(1);
        }
        if(color_id_str.length() == 6){
            r = hex2int(color_id_str.substr(0, 2));
            g = hex2int(color_id_str.substr(2, 2));
            b = hex2int(color_id_str.substr(4, 2));
        } else {
            r = 0;
            g = 0;
            b = 0;
        }
    }

    COLOR16 color::get_red(){
        return r;
    }

    COLOR16 color::get_green(){
        return g;
    }

    COLOR16 color::get_blue(){
        return b;
    }

    COLORREF color::get_color(){
        return RGB(r, g, b);
    }

    base_tuple::base_tuple(){
        x = 0;
        y = 0;
    }

    base_tuple::base_tuple(int x, int y){
        this->x = x;
        this->y = y;
    }

    base_tuple base_tuple::operator+(base_tuple pos){
        return base_tuple(x+pos.x, y+pos.y);
    }

    base_tuple base_tuple::operator-(base_tuple pos){
        return base_tuple(x-pos.x, y-pos.y);
    }

    void base_tuple::move(int x, int y){
        this->x += x;
        this->y += y;
    }


    void render_object::draw(position &pos){
        this->draw(pos.x, pos.y);
    }

    void render_object::draw(){
        this->draw(default_pos.x, default_pos.y);
    }

    void render_object::move(position &pos){
        this->move(pos.x, pos.y);
    }

    void render_object::move(int x, int y){
        default_pos.move(x, y);
    }


    render_text::render_text(color font_color, std::string_view content, int font_size){
        font = "宋体";
        text = content;
        text_color = font_color;
        size = font_size;
    }
    void render_text::set_font(std::string_view font){
        this->font = font;
    }
    void render_text::set_text(std::string_view text){
        this->text = text;
    }
    void render_text::set_color(color font_color){
        text_color = font_color;
    }
    void render_text::set_size(int font_size){
        size = font_size;
    }
    void render_text::draw(int x, int y){
        settextcolor(text_color.get_color());
        settextstyle(size, 0, font.c_str());
        outtextxy(x, y, text.c_str());
    }

    render_rect::render_rect(color rect_color, size rect_size, bool fill){
        this->rect_color = rect_color;
        this->rect_size = rect_size;
        this->is_filled = fill;
    }
    void render_rect::set_color(color rect_color){
        this->rect_color = rect_color;
    }
    void render_rect::set_size(size rect_size){
        this->rect_size = rect_size;
    }
    void render_rect::set_filled(bool fill){
        is_filled = fill;
    }
    void render_rect::draw(int x, int y){
        setlinecolor(rect_color.get_color());
        if(is_filled){
            setfillcolor(rect_color.get_color());
            fillrectangle(x, y, x+rect_size.x, y+rect_size.y);
        } else {
            rectangle(x, y, x+rect_size.x, y+rect_size.y);
        }
    }

    render_circle::render_circle(color circle_color, double radius, bool fill){
        this->circle_color = circle_color;
        this->radius = radius;
        this->is_filled = fill;
    }
    void render_circle::set_color(color circle_color){
        this->circle_color = circle_color;
    }
    void render_circle::set_radius(double radius){
        this->radius = radius;
    }
    void render_circle::set_filled(bool fill){
        is_filled = fill;
    }
    void render_circle::draw(int x, int y){
        setlinecolor(circle_color.get_color());
        if(is_filled){
            setfillcolor(circle_color.get_color());
            fillellipse(x, y, radius*2, radius*2);
        } else {
            ellipse(x, y, radius*2, radius*2);
        }
    }
    
    render_line::render_line(color line_color, int line_len, double rotate_angle, int thickness){
        this->line_color = line_color;
        length = line_len;
        angle = rotate_angle;
        thick = thickness;
    }
    void render_line::set_color(color line_color){
        this->line_color = line_color;
    }
    void render_line::set_length(int line_len){
        length = line_len;
    }
    void render_line::set_angle(double rotate_angle){
        angle = rotate_angle;
    }
    void render_line::draw(int x, int y){
        setlinecolor(line_color.get_color());
        setlinestyle(PS_SOLID , thick);
        int end_x = x + length * cos(angle);
        int end_y = y + length * sin(angle);
        line(x, y, end_x, end_y);
    }

    base_image::base_image(std::string_view path){
        loadimage(&img, path.data());
        img_output = img;
        this->path = std::string(path);
    }
    base_image::base_image(){
        path = "";
    }
    void base_image::resize(int width, int height){
        loadimage(&img, path.c_str(), width, height);
        img.Resize(width, height);
    }
    void base_image::rotate(double angle){
        rotateimage(&img_output, &img, degree(angle));
    }
    void base_image::draw(int x, int y, DWORD mode){
        putimage(x, y, &img_output, mode);
    }

    render_pic::render_pic(std::string_view path){
        img = base_image(path);
        is_alpha = false;
        img_alpha = base_image(path);
    }
    void render_pic::resize(int width, int height){
        img.resize(width, height);
        if(is_alpha){
            img_alpha.resize(width, height);
        }
    }
    void render_pic::rotate(double angle){
        rotation = angle;
        img.rotate(angle);
        if(is_alpha){
            img_alpha.rotate(angle);
        }
    }
    void render_pic::draw(int x, int y){
        if(is_alpha){
            img_alpha.draw(x, y, SRCAND);
            img.draw(x, y, SRCPAINT);
        } else {
            img.draw(x, y);
        }
    }
    void render_pic::set_as_alpha(std::string_view path){
        img_alpha = base_image(path);
        is_alpha = true;
    }

    monitor::monitor():
    stop_msg_loop(std::atomic<int>(false)){
        memset(key_state, 0, sizeof(key_state));
        // in new thread to call message loop
        std::thread(&monitor::message_loop, this, std::ref(*this)).detach();
    }

    monitor::~monitor(){
        std::cout<< "monitor destroyed\n";
        stop_msg_loop = true;
    }

    bool monitor::key(int vkey){
        // get the keyboard message
        ExMessage msg = {0};
        while(peekmessage(&msg, EX_KEY, true)){
            key_state[msg.vkcode] = true;
        }
        return key_state[vkey] > 0;
    }

    void monitor::clear(){
        for(int i = 0; i < 256; i++){
            key_state[i] = 0;
        }
    }

    void monitor::message_loop(monitor &self){
        ExMessage msg = {0};
        loop_start:
        while(peekmessage(&msg, EX_KEY, true)){
            key_state[msg.vkcode] = true;
        }
        if(stop_msg_loop){
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        goto loop_start;
    }

    window::window(int width, int height){
        has_default = false;
        this->width = width;
        this->height = height;
        initgraph(width, height);
    }
    window::~window(){
        closegraph();
    }

    void window::update(){
        FlushBatchDraw();
        BeginBatchDraw();
        cleardevice();
        if(has_default){
            draw_default();
        }
    }

    void window::set_background(color bg_color){
        setbkcolor(bg_color.get_color());
        cleardevice();
    }
    int window::add_render_object(render_object* obj){
        has_default = true;
        default_render_list.push_back(obj);
        enable_render_list .push_back(true);
        return default_render_list.size() - 1;
    }
    const render_object* window::get_render_object(int index){
        return default_render_list[index];
    }
    void window::remove_render_object(int index){
        enable_render_list[index] = false;
    }
    void window::enable_render_object(int index){
        enable_render_list[index] = true;
    }
    void window::draw_default(){
        if(!has_default){
            return;
        }
        for(int idx = 0; idx < default_render_list.size(); idx++){
            if(enable_render_list[idx]){
                default_render_list[idx]->draw();
            }
        }
    }
    void window::clear_render_object(){
        default_render_list.clear();
        enable_render_list.clear();
    }

    bool window::is_closed(){
        HWND hwnd = GetHWnd();
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        return (style & WS_VISIBLE) == 0;
    }
    void window::retitle(std::string_view title){
        HWND hwnd = GetHWnd();
        SetWindowText(hwnd, title.data());
    }
}

