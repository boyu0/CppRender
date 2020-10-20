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
    int perSize = Utils::getFormatPerSize(_format);
    _data = malloc(width*height*perSize);
    if(data != nullptr){
        memcpy(_data, data, width*height*perSize);
    }else{
        memset(_data, 0, width*height*perSize);
    }

}

void RenderBuffer::clearColor(float color[4])
{
    char* levelData = (char*)_data;
    int perSize = Utils::getFormatPerSize(_format);
    for(int i = 0; i < _height; ++i)
    {
        char* lineStart = levelData + i * _width * perSize;
        for(int j = 0; j < _width; ++j)
        {
            char* pixelStart = lineStart + j * perSize;
            for(int k = 0; k < perSize; ++k)
            {
                *(pixelStart + k) = (char)(color[k] * 255);
            }
        }
    }
}

}