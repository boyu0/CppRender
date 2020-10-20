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
#include "CppLuaEngine.hpp"
#include "CppShader.hpp"
#include "CppVertexShader.hpp"
#include "CppFragmentShader.hpp"
#include "CppProgram.hpp"
#include "CppVertexArray.hpp"
#include "CppBuffer.hpp"

namespace CppRender{
Context::Context()
{
    
}

Context::~Context()
{
    
}


void Context::clear(int mask)
{
    CR_ASSERT(_currentFrameBufferIndex != CR_INVALID_VALUE && _frameBuffers.find(_currentFrameBufferIndex) != _frameBuffers.end(), "");

    FrameBuffer* frameBuffer = _frameBuffers[_currentFrameBufferIndex];
    frameBuffer->clear(mask);
}

void Context::clearColor(float r, float g, float b, float a)
{
    _clearColor = glm::vec4(r, g, b, a);
}

void Context::genFrameBuffers(int n, int* ids)
{
    CR_GEN_BUFFER(FrameBuffer, _frameBuffers, _frameBufferIndex, n, ids);
}

Texture* Context::getTexture(int id)
{
    CR_MAP_FIND_RETURN(_textures, id);
}

void Context::bindFrameBuffer(int target, int id)
{
    _currentFrameBufferIndex = id;
}

void Context::genRenderbuffers(int n, int* ids)
{
    CR_GEN_BUFFER(RenderBuffer, _renderBuffers, _renderBufferIndex, n, ids);
}

void Context::bindRenderBuffer(int target, int id)
{
    _currentRenderBufferIndex = id;
}

int Context::createShader(int type, const std::string& file)
{
    Shader* shader = nullptr;
    switch (type)
    {
    case CR_VERTEX_SHADER:
        shader = new VertexShader();
        break;
    case CR_FRAGMENT_SHADER:
        shader = new FragmentShader();
        break;
    default:
        CR_ASSERT(false, "");
        return false;
    }

    if(shader == nullptr || !shader->init(this, file))
    {
        CR_ASSERT(false, "");
        return CR_INVALID_VALUE;
    }

    _shaders.emplace(std::make_pair(_shaderIndex, shader));
    return _shaderIndex++;
}

int Context::createProgram()
{
    return 0;
}

void Context::frameBufferTexture2D(int target, int attachment, int textarget, int texture, int level)
{
    CR_ASSERT(_frameBuffers.find(attachment) != _frameBuffers.end(), "");
    CR_ASSERT(_textures.find(texture) != _textures.end(), "");

    FrameBuffer* frameBuffer = _frameBuffers[attachment];
    frameBuffer->bindTexture2D(texture);
}

void Context::genTextures(int n, int* ids)
{
    CR_GEN_BUFFER(Texture, _textures, _textureIndex, n, ids);
}

void Context::bindTexture(int target, int id)
{
    _currentTextureIndex = id;
}

void Context::genVertexArrays(int n, int* ids)
{
    CR_GEN_BUFFER(VertexArray, _vertexArrays, _vertexArrayIndex, n ,ids);
}

void Context::bindVertexArray(int id)
{
    _currentVertexArrayIndex = id;
}

void Context::genBuffers(int n, int* ids)
{
    CR_GEN_BUFFER(Buffer, _buffers, _bufferIndex, n, ids);
}
void Context::bindBuffer(int target, int id)
{
    if(target == CR_ARRAY_BUFFER)
    {
        _currentArrayBufferIndex = id;
    }else if(target == CR_ELEMENT_ARRAY_BUFFER){
        _currentElementArrayBufferIndex = id;
    }else{
        CR_ASSERT(false, "");
        return;
    }
}

void  Context::texImage2D(int target, int level, int internalformat, int width, int height, void* data)
{
    CR_ASSERT(_currentTextureIndex != CR_INVALID_VALUE && _textures.find(_currentTextureIndex) != _textures.end(), "");

    Texture* tex = _textures[_currentTextureIndex];
    tex->image2D(target, level, internalformat, width, height, data);
}

bool Context::init(int width, int height)
{
    _draw = new Draw();
    _luaEngine = new LuaEngine();
    if(_luaEngine == nullptr || !_luaEngine->init())
    {
        return false;
    }

    int defaultFrameBuffer = CR_INVALID_VALUE;
    genFrameBuffers(1, &defaultFrameBuffer);
    CR_CHECK_RETURN_FALSE(defaultFrameBuffer != CR_INVALID_VALUE);
    CR_ASSERT(defaultFrameBuffer == 0, "defaultFrameBuffer只能为0");
    bindFrameBuffer(0, defaultFrameBuffer);

//    int defaultRenderBuffer = CR_INVALID_VALUE;
//    genRenderbuffers(1, &defaultRenderBuffer);
//    CR_CHECK_RETURN_FALSE(defaultRenderBuffer != CR_INVALID_VALUE);
//    CR_ASSERT(defaultRenderBuffer == 0, "defaultRenderBuffer只能为0");
//    bindRenderBuffer(0, defaultRenderBuffer);

    int defaultTexture = CR_INVALID_VALUE;
    genTextures(1, &defaultTexture);
    CR_CHECK_RETURN_FALSE(defaultTexture != CR_INVALID_VALUE);
    CR_ASSERT(defaultTexture == 0, "defaultTexture只能为0");
    bindTexture(0, defaultTexture);
    texImage2D(CR_TEXTURE_2D, 0, CR_RGBA8, width, height, nullptr);
    frameBufferTexture2D(0, defaultFrameBuffer, 0, defaultTexture, 0);

    int defaultVertexArray = CR_INVALID_VALUE;
    genVertexArrays(1, &defaultVertexArray);
    CR_CHECK_RETURN_FALSE(defaultVertexArray != CR_INVALID_VALUE);
    CR_ASSERT(defaultVertexArray == 0, "defaultVertexArray只能为0");
    bindVertexArray(defaultVertexArray);

    return true;
}

void Context::getRenderData(void** data)
{
    CR_ASSERT(_frameBuffers.find(_currentFrameBufferIndex) != _frameBuffers.end(), "");

    FrameBuffer* frameBuffer = _frameBuffers[_currentFrameBufferIndex];
    int texture2dIndex = frameBuffer->getTexture2D();
    CR_ASSERT(_textures.find(texture2dIndex) != _textures.end(), "");
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

void Context::attachShader(int program, int shader)
{
    CR_ASSERT(_programs.find(program) != _programs.end(), "");
    CR_ASSERT(_shaders.find(shader) != _shaders.end(), "");
    _programs[program]->attach(_shaders[shader]);
}

bool Context::linkProgram(int program)
{
    CR_ASSERT(_programs.find(program) != _programs.end(), "");
    return _programs[program]->link();
}
}
