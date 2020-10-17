//
//  CppContext.cpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppContext.hpp"
#include "CppFrameBuffer.hpp"
#include "CppRenderBuffer.hpp"
#include "CppTexture.hpp"
#include "CppRender.hpp"
#include "CppUtils.hpp"
#include "CppDraw.hpp"

namespace CppRender{
Context::Context()
{
    
}

Context::~Context()
{
    
}


void Context::clear(int mask)
{
    CPPRENDER_ASSERT(_currentFrameBufferIndex != CPPRENDER_INVALID_VALUE && _frameBuffers.find(_currentFrameBufferIndex) != _frameBuffers.end(), "");

    FrameBuffer* frameBuffer = _frameBuffers[_currentFrameBufferIndex];
    frameBuffer->clear(mask);
}

void Context::clearColor(float r, float g, float b, float a)
{
    _color = glm::vec4(r, g, b, a);
}

void Context::genFrameBuffers(int n, int* ids)
{
    CPPRENDER_GEN_BUFFER(FrameBuffer, _frameBuffers, _frameBufferIndex, n, ids);
}

Texture* Context::getTexture(int id)
{
    CPPRENDER_MAP_FIND_RETURN(_textures, id);
}

void Context::bindFrameBuffer(int target, int id)
{
    _currentFrameBufferIndex = id;
}

void Context::genRenderbuffers(int n, int* ids)
{
    CPPRENDER_GEN_BUFFER(RenderBuffer, _renderBuffers, _renderBufferIndex, n, ids);
}

void Context::bindRenderBuffer(int target, int id)
{
    _currentRenderBufferIndex = id;
}

int Context::createShader(int type)
{
    return 0;
}

int Context::createProgram()
{
    return 0;
}

void Context::frameBufferTexture2D(int target, int attachment, int textarget, int texture, int level)
{
    CPPRENDER_ASSERT(_frameBuffers.find(attachment) != _frameBuffers.end(), "");
    CPPRENDER_ASSERT(_textures.find(texture) != _textures.end(), "");

    FrameBuffer* frameBuffer = _frameBuffers[attachment];
    frameBuffer->bindTexture2D(texture);
}

void Context::genTextures(int n, int* ids)
{
    CPPRENDER_GEN_BUFFER(Texture, _textures, _textureIndex, n, ids);
}

void Context::bindTexture(int target, int id)
{
    _currentTextureIndex = id;
}

void  Context::texImage2D(int target, int level, int internalformat, int width, int height, void* data)
{
    CPPRENDER_ASSERT(_currentTextureIndex != CPPRENDER_INVALID_VALUE && _textures.find(_currentTextureIndex) != _textures.end(), "");
    
    Texture* tex = _textures[_currentTextureIndex];
    tex->image2D(target, level, internalformat, width, height, data);
}

bool Context::init(int width, int height)
{
    _draw = new Draw();

    int defaultFrameBuffer = CPPRENDER_INVALID_VALUE;
    genFrameBuffers(1, &defaultFrameBuffer);
    CPPRENDER_CHECK_RETURN_FALSE(defaultFrameBuffer != CPPRENDER_INVALID_VALUE);
    CPPRENDER_ASSERT(defaultFrameBuffer == 0, "defaultFrameBuffer只能为0");
    bindFrameBuffer(0, defaultFrameBuffer);

//    int defaultRenderBuffer = CPPRENDER_INVALID_VALUE;
//    genRenderbuffers(1, &defaultRenderBuffer);
//    CPPRENDER_CHECK_RETURN_FALSE(defaultRenderBuffer != CPPRENDER_INVALID_VALUE);
//    CPPRENDER_ASSERT(defaultRenderBuffer == 0, "defaultRenderBuffer只能为0");
//    bindRenderBuffer(0, defaultRenderBuffer);

    int defaultTexture = CPPRENDER_INVALID_VALUE;
    genTextures(1, &defaultTexture);
    CPPRENDER_CHECK_RETURN_FALSE(defaultTexture != CPPRENDER_INVALID_VALUE);
    CPPRENDER_ASSERT(defaultTexture == 0, "defaultTexture只能为0");
    bindTexture(0, defaultTexture);
    texImage2D(CPPRENDER_TEXTURE_2D, 0, CPPRENDER_RGBA8, width, height, nullptr);
    frameBufferTexture2D(0, defaultFrameBuffer, 0, defaultTexture, 0);

    return true;
}

void Context::getRenderData(void** data)
{
    CPPRENDER_ASSERT(_frameBuffers.find(_currentFrameBufferIndex) != _frameBuffers.end(), "");

    FrameBuffer* frameBuffer = _frameBuffers[_currentFrameBufferIndex];
    int texture2dIndex = frameBuffer->getTexture2D();
    CPPRENDER_ASSERT(_textures.find(texture2dIndex) != _textures.end(), "");
    Texture* tex = _textures[texture2dIndex];
    *data = tex->getData();
}


void Context::begin(int mode)
{
    _draw->begin(mode);
}

void Context::end()
{
    _draw->end();
}

void Context::vertex3f(float x, float y, float z)
{
    _draw->vertex3f(x, y, z);
}

void Context::color3f(float r, float g, float b)
{
    _draw->color3f(r, g, b);
}
}
