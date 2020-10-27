//
//  CppRenderBuffer.cpp
//  CppRender
//
//  Created by yubo on 2020/10/15.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppRenderBuffer.hpp"
#include "CppDefine.h"
#include "CppUtils.hpp"
#include <memory>

namespace CppRender{
void RenderBuffer::storage(int target, int internalformat, int width, int height, void* data)
{
    _target = target;
    _format = internalformat;
    _width = width;
    _height = height;
    _perSize = Utils::getFormatPerSize(_format);
    _data = malloc(width*height*_perSize);
    if(data != nullptr){
        memcpy(_data, data, width*height*_perSize);
    }else{
        memset(_data, 0, width*height*_perSize);
    }

}

void RenderBuffer::readPixel(int x, int y, float color[4])
{
    unsigned char* levelData = (unsigned char*)_data;
    unsigned char* c = levelData + (y * _width + x) * _perSize;
    color[0] = c[0] / 255.0f;
    color[1] = c[1] / 255.0f;
    color[2] = c[2] / 255.0f;
    color[3] = _perSize == 4 ? c[3]/255.0f : 1.0f;
}

void RenderBuffer::readPixel(float x, float y, float color[4])
{
    readPixel(int(x*_width), int(y*_height), color);
}

void RenderBuffer::clearColor(float color[4])
{
    unsigned char* levelData = (unsigned char*)_data;
    for(int i = 0; i < _height; ++i)
    {
        unsigned char* lineStart = levelData + i * _width * _perSize;
        for(int j = 0; j < _width; ++j)
        {
            unsigned char* pixelStart = lineStart + j * _perSize;
            for(int k = 0; k < _perSize; ++k)
            {
                *(pixelStart + k) = (unsigned char)(color[k] * 255);
            }
        }
    }
}

}
