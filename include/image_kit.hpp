#pragma once

#ifndef __image_kit_hpp__
#define __image_kit_hpp__

#include <easyx.h>
#include <string_view>

namespace kit{
    using buffer_unit   = DWORD;
    using buffer_stream = DWORD*;

    struct image_buffer{
        int width, height;
        buffer_stream buffer;
        image_buffer(int, int, buffer_stream);
        ~image_buffer();
    };

    image_buffer get_buffer(std::string_view);
    image_buffer get_buffer(IMAGE*);

    // 旋转
    image_buffer rotate(image_buffer, double);
    // 缩放
    image_buffer resize(image_buffer, int, int);
    // 裁剪
    image_buffer reshape(image_buffer, int, int, int, int);
    // 透明度
    image_buffer opacity(image_buffer, double);

    void draw(image_buffer, int, int);
}

#endif