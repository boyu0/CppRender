//
//  CppTexture.cpp
//  CppRender
//
//  Created by yu bo on 2020/10/16.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppTexture.hpp"
#include "CppUtils.hpp"
#include<memory>

namespace CppRender{
void Texture::image2D(int target, int level, int internalformat, int width, int height, void* data)
{
    CPPRENDER_ASSERT(level==0, "");
    _target = target;
    _format = internalformat;
    _width = width;
    _height = height;
    int perSize = Utils::getFormatPerSize(_format);
    _data[level] = malloc(width*height*perSize);
    if(data != nullptr){
        memcpy(_data[level], data, width*height*perSize);
    }else{
        memset(_data[level], 0, width*height*perSize);
    }
}

void Texture::clearColor(glm::vec4 color)
{
    char* levelData = (char*)_data[0];
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
