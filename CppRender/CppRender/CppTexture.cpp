//
//  CppTexture.cpp
//  CppRender
//
//  Created by yu bo on 2020/10/16.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppTexture.hpp"
#include "CppUtils.hpp"
#include "CppRenderBuffer.hpp"

namespace CppRender{
void Texture::image2D(int target, int level, int internalformat, int width, int height, void* data)
{
    CR_ASSERT(level==0, "");

    _target = target;
    // TODO: 通用生成和销毁
    if(_buffers[level])
    {
        delete _buffers[level];
    }
    _buffers[level] = new RenderBuffer(_ctx);
    _buffers[level]->storage(CR_RENDER_BUFFER, internalformat, width, height, data);
}

void Texture::readPixel(int level, int x, int y, float color[4])
{
    _buffers[level]->readPixel(x, y, color);
}

void Texture::readPixel(int level, float x, float y, float color[4])
{
    _buffers[level]->readPixel(x, 1.0f-y, color);
}

void Texture::clearColor(float color[4])
{
    _buffers[0]->clearColor(color);
}
}
