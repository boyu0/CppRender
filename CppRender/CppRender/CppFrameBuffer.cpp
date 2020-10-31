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
    
    if(_clearMask & CR_DEPTH_BUFFER_BIT)
    {
        if(_depthBufferIndex != CR_INVALID_VALUE)
        {
            void* data = _ctx->mapBufferIndex(_depthBufferIndex);
            Texture* tex = _ctx->getTexture(_texture2DIndex);
            int size = tex->getWidth() * tex->getHeight();
            memset(data, 0x7f, size);
        }
    }

    _clearMask = 0;
}

void* FrameBuffer::getData()
{
    doClear();

    Texture* tex = _ctx->getTexture(_texture2DIndex);
    if(tex)
    {
        return tex->getData();
    }

    return nullptr;
}

int FrameBuffer::genDepthBuffer()
{
    if(_depthBufferIndex != CR_INVALID_VALUE) { return _depthBufferIndex; }
    Texture* tex = _ctx->getTexture(_texture2DIndex);
    _ctx->genBuffers(1, &_depthBufferIndex);
    int size = tex->getWidth() * tex->getHeight();
    _ctx->bufferDataIndex(_depthBufferIndex, size, nullptr, CR_STATIC_DRAW);
    void* data = _ctx->mapBufferIndex(_depthBufferIndex);
    memset(data, 0x7f, size);
    return _depthBufferIndex;
}

void FrameBuffer::deleteDepthBuffer()
{
    if(_depthBufferIndex == CR_INVALID_VALUE) { return; }
    _ctx->deleteBuffers(1, &_depthBufferIndex);
    _depthBufferIndex = CR_INVALID_VALUE;
}

void FrameBuffer::getSize(int size[2])
{

    Texture* tex = _ctx->getTexture(_texture2DIndex);
    if(tex)
    {
        size[0] = tex->getWidth();
        size[1] = tex->getHeight();
    }

}

void FrameBuffer::drawArrays(int mode, int start, int count)
{
    doClear();
    _ctx->runProgram(mode, start, count);
}
}
