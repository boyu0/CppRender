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
    Context* ctx = Render::getContext();
    if(mask & CPPRENDER_COLOR_BUFFER_BIT)
    {
        CPPRENDER_ASSERT(_texture2DIndex != CPPRENDER_INVALID_VALUE, "");
        Texture* tex = ctx->getTexture(_texture2DIndex);
        tex->clearColor(ctx->getClearColor());
    }

}
}
