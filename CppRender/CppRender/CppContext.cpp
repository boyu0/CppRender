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
#include "CppProgram.hpp"
#include "CppWindow.hpp"
#include "glm/ext.hpp"

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
    _clearColor[0] = r;
    _clearColor[1] = g;
    _clearColor[2] = b;
    _clearColor[3] = a;
}

void Context::genFrameBuffers(int n, int* ids)
{
    CR_GEN_ARRAYS(this, FrameBuffer, _frameBuffers, _frameBufferIndex, n, ids);
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
    CR_GEN_ARRAYS(this, RenderBuffer, _renderBuffers, _renderBufferIndex, n, ids);
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
    Program* program = new Program(this);
    _programs.emplace(std::make_pair(_programIndex, program));
    return _programIndex++;
}

void Context::vertexArrayLoadOne(int n)
{
    CR_ASSERT(_vertexArrays.find(_currentVertexArrayIndex) != _vertexArrays.end(), "");

    _vertexArrays[_currentVertexArrayIndex]->loadOne(n);
}

void Context::deleteBuffers(int n, int* ids)
{
    CR_DELETE_ARRAYS(this, _buffers, n, ids);
}

void Context::vertexAttributePointer(int index, int size, int type, bool normalized, int stride, int pointer)
{
    CR_ASSERT(_vertexArrays.find(_currentVertexArrayIndex) != _vertexArrays.end(), "");

    _vertexArrays[_currentVertexArrayIndex]->vertexAttributePointer(index, size, type, normalized, stride, pointer);
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
    CR_GEN_ARRAYS(this, Texture, _textures, _textureIndex, n, ids);
}

void Context::bindTexture(int target, int id)
{
    _currentTextureIndex = id;
}

void Context::getTextureSize(int target, int size[2])
{
    CR_ASSERT(_textures.find(target) != _textures.end(), "");
    size[0] = _textures[target]->getWidth();
    size[1] = _textures[target]->getHeight();
}

void Context::genVertexArrays(int n, int* ids)
{
    CR_GEN_ARRAYS(this, VertexArray, _vertexArrays, _vertexArrayIndex, n ,ids);
}

void Context::bindVertexArray(int id)
{
    _currentVertexArrayIndex = id;
}

void Context::genBuffers(int n, int* ids)
{
    CR_GEN_ARRAYS(this, Buffer, _buffers, _bufferIndex, n, ids);
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

void Context::runProgram(int mode, int start, int count)
{
    _programs[_currentProgramIndex]->run(mode, start, count);
}


void Context::useProgram(int program)
{
    _currentProgramIndex = program;
}

void Context::ortho(float left, float right, float bottom, float top, float near, float far)
{
    _projection = glm::ortho(left, right, bottom, top, near, far);
}

void Context::drawArrays(int mode, int start, int count)
{
    CR_ASSERT(_frameBuffers.find(_currentFrameBufferIndex) != _frameBuffers.end(), "");
    _frameBuffers[_currentArrayBufferIndex]->drawArrays(mode, start, count);
}

void Context::bufferData(int target, int size, void* data, int useage)
{
    Buffer* buffer = nullptr;
    if(target == CR_ARRAY_BUFFER)
    {
        CR_ASSERT(_buffers.find(_currentArrayBufferIndex) != _buffers.end(), "");
        buffer = _buffers[_currentArrayBufferIndex];
    }else if(target == CR_ELEMENT_ARRAY_BUFFER)
    {
        CR_ASSERT(_buffers.find(_currentElementArrayBufferIndex) != _buffers.end(), "");
        buffer = _buffers[_currentElementArrayBufferIndex];
    }else{
        CR_ASSERT(false, "");
        return;
    }
    buffer->data(target, size, data, useage);
}

void Context::texImage2D(int target, int level, int internalformat, int width, int height, void* data)
{
    CR_ASSERT(_currentTextureIndex != CR_INVALID_VALUE && _textures.find(_currentTextureIndex) != _textures.end(), "");

    Texture* tex = _textures[_currentTextureIndex];
    tex->image2D(target, level, internalformat, width, height, data);
}

void Context::viewPort(int x, int y, int width, int height)
{
    CR_ASSERT(_frameBuffers.find(_currentFrameBufferIndex) != _frameBuffers.end(), "");
    // _frameBuffers[_currentArrayBufferIndex]->viewPort(x, y, width, height);
}


void Context::getFrameBufferSize(int target, int size[2])
{
    _frameBuffers[target]->getSize(size);
}

void Context::getIntegerv(int target, int out[])
{
    switch (target)
    {
    case CR_VIEW_PORT:
    {
        int* p = _frameBuffers[_currentArrayBufferIndex]->getViewPort();
        out[0] = p[0];
        out[1] = p[1];
        out[2] = p[2];
        out[3] = p[3];
        return;
    }
    break;
    case CR_WIN_SIZE:
    {
        out[0] = 800;
        out[1] = 600;
        return;
    }
    break;
    default:
        break;
    }

    return;
}

bool Context::init(int width, int height)
{
    _draw = new Draw(this);
    _luaEngine = new LuaEngine();
    if(_luaEngine == nullptr || !_luaEngine->init())
    {
        return false;
    }

    ortho(-1, 1, -1, 1, -1, 1);

    _window = new Window(this);
    if(_window == nullptr || !_window->init(width, height))
    {
        return false;
    }

    return true;
}

void Context::getRenderData(void** data)
{
    CR_ASSERT(_frameBuffers.find(_currentFrameBufferIndex) != _frameBuffers.end(), "");

    FrameBuffer* frameBuffer = _frameBuffers[_currentFrameBufferIndex];
    *data = frameBuffer->getData();
}


void Context::begin(int mode)
{
    _draw->begin(mode);
}

void Context::end()
{
    _draw->end();
}

void Context::vertexf(float x, float y, float z, float w)
{
    _draw->vertexf(x, y, z);
}

void Context::colorf(float r, float g, float b, float a)
{
    _draw->colorf(r, g, b);
}

void Context::uvf(float u, float v)
{
    _draw->uvf(u, v);
}

void* Context::mapBuffer(int target)
{
    switch (target)
    {
    case CR_ARRAY_BUFFER:
        return _buffers[_currentArrayBufferIndex]->get();
    case CR_RENDER_BUFFER:
        return _frameBuffers[_currentFrameBufferIndex]->getData();
    default:
        return nullptr;
    }
}

void* Context::mapBufferIndex(int index, int* size)
{
    Buffer* buffer = _buffers[index];
    if(size)
    {
        *size = buffer->size();
    }
    return buffer->get();
}


void Context::setProgramAttribute(int index, int size, int type, bool normalized, void* data)
{
    Program* program = _programs[_currentProgramIndex];
    program->setAttribute(index, size, type, normalized, data);
}

int Context::get(int target)
{
    switch (target)
    {
    case CR_ARRAY_BUFFER:
        return _currentArrayBufferIndex;
    case CR_ELEMENT_ARRAY_BUFFER:
        return _currentElementArrayBufferIndex;
    case CR_PROGRAM:
        return _currentProgramIndex;
    case CR_FRAME_BUFFER:
        return _currentFrameBufferIndex;
    default:
        return CR_INVALID_VALUE;
    }
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
