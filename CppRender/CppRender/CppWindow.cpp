//
//  CppWindow.cpp
//  CppRender
//
//  Created by yubo on 2020/10/22.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppWindow.hpp"
#include "CppContext.hpp"
#include "CppUtils.hpp"

namespace CppRender{
bool Window::init(int width, int height)
{

    int defaultFrameBuffer = CR_INVALID_VALUE;
    _ctx->genFrameBuffers(1, &defaultFrameBuffer);
    CR_CHECK_RETURN_FALSE(defaultFrameBuffer != CR_INVALID_VALUE);
    CR_ASSERT(defaultFrameBuffer == 0, "defaultFrameBuffer只能为0");
    _ctx->bindFrameBuffer(0, defaultFrameBuffer);

    int defaultTexture = CR_INVALID_VALUE;
    _ctx->genTextures(1, &defaultTexture);
    CR_CHECK_RETURN_FALSE(defaultTexture != CR_INVALID_VALUE);
    CR_ASSERT(defaultTexture == 0, "defaultTexture只能为0");
    _ctx->bindTexture(0, defaultTexture);
    _ctx->texImage2D(CR_TEXTURE_2D, 0, CR_RGBA8, width, height, nullptr);
    _ctx->frameBufferTexture2D(0, defaultFrameBuffer, 0, defaultTexture, 0);

    int defaultVertexArray = CR_INVALID_VALUE;
    _ctx->genVertexArrays(1, &defaultVertexArray);
    CR_CHECK_RETURN_FALSE(defaultVertexArray != CR_INVALID_VALUE);
    CR_ASSERT(defaultVertexArray == 0, "defaultVertexArray只能为0");
    _ctx->bindVertexArray(defaultVertexArray);
    
    return true;
}

void Window::doViewPort()
{
    // Texture* tex = _ctx->getTexture(_texture2DIndex);
    // if(tex)
    // {
    //     if(tex->getWidth() != _view[2] - _view[0] || tex->getHeight() != _view[3] - _view[1])
    //     {
    //         tex->image2D(tex->getTarget(), 0, tex->getInternalFormat(), tex->getWidth(), tex->getHeight(), nullptr);
    //     }
    // }
}
}
