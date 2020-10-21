//
//  CppFrameBuffer.cpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppFrameBuffer.hpp"
#include "CppUtils.hpp"
#include "CppRender.hpp"
#include "CppContext.hpp"
#include "CppTexture.hpp"
#include "CppProgram.hpp"

namespace CppRender{
void FrameBuffer::bindRenderBuffer(int idx)
{
    _renderBufferIndex = idx;
}

void FrameBuffer::bindTexture2D(int idx)
{
    _texture2DIndex = idx;
}

void FrameBuffer::clear(int mask)
{
    if(mask & CR_COLOR_BUFFER_BIT)
    {
        _clearMask |= CR_COLOR_BUFFER_BIT;
        memcpy(_clearColor, _ctx->getClearColor(), sizeof(_clearColor));
    }
}

void FrameBuffer::doViewPort()
{
    Texture* tex = _ctx->getTexture(_texture2DIndex);
    if(tex)
    {
        if(tex->getWidth() != _view[2] - _view[0] || tex->getHeight() != _view[3] - _view[1])
        {
            tex->image2D(tex->getTarget(), 0, tex->getInternalFormat(), tex->getWidth(), tex->getHeight(), nullptr);
        }
    }
}

void FrameBuffer::doClear()
{
    if(_clearMask & CR_COLOR_BUFFER_BIT)
    {
        Texture* tex = _ctx->getTexture(_texture2DIndex);
        if(tex)
        {
            tex->clearColor(_clearColor);
        }
    }

    _clearMask = 0;
}

void* FrameBuffer::getData()
{
    doViewPort();
    doClear();

    Texture* tex = _ctx->getTexture(_texture2DIndex);
    if(tex)
    {
        return tex->getData();
    }

    return nullptr;
}

void FrameBuffer::drawArrays(int mode, int start, int count)
{
    doViewPort();
    doClear();
    _ctx->runProgram(mode, start, count);
}

void FrameBuffer::viewPort(int x, int y, int width, int height)
{
    _view[0] = x;
    _view[1] = y;
    _view[2] = width;
    _view[3] = height;
}
}
