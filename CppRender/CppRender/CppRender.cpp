//
//  CppRender.cpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#include <iostream>
#include "CppRender.hpp"
#include "CppContext.hpp"
#include "CppFrameBuffer.hpp"
#include "CppBuffer.hpp"
#include "CppVertexArray.hpp"
#include <unordered_map>

namespace CppRender{

Context* ctx = nullptr;

bool Render::init(int width, int height)
{
    ctx = new Context();
    if(ctx == nullptr ||  !ctx->init(width, height)){
        return false;
    }
    
    return true;
}

void Render::genFrameBuffers(int n, int* ids)
{
}

void Render::bindFrameBuffer(int id)
{
    
}


void Render::genTextures(int n, int* ids)
{
    ctx->genTextures(n ,ids);
}

void Render::bindTexture(int id)
{
    ctx->bindTexture(0, id);
}

void Render::texCoord2f(float u, float v)
{
    ctx->uvf(u, v);
}

void Render::clearColor(float r, float g, float b, float a)
{
    ctx->clearColor(r, g, b, a);
}

void Render::clear(int bit)
{
    ctx->clear(bit);
}

void Render::getRenderData(void** data)
{
    return ctx->getRenderData(data);
}

void Render::begin(int mode)
{
    ctx->begin(mode);
}

void Render::end()
{
    ctx->end();
}

void Render::vertexf(float x, float y, float z, float w)
{
    ctx->vertexf(x, y, z, w);
}

void Render::colorf(float r, float g, float b, float a)
{
    ctx->colorf(r, g, b, a);
}

void Render::uvf(float u, float v)
{
    ctx->uvf(u, v);
}

int Render::createShader(int type, const std::string& file)
{
    return ctx->createShader(type, file);
}
int Render::createProgram()
{
    return ctx->createProgram();
}

void Render::attachShader(int program, int shader)
{
    ctx->attachShader(program, shader);
}

bool Render::linkProgram(int program)
{
    return ctx->linkProgram(program);
}

void Render::useProgram(int program)
{
    ctx->useProgram(program);
}

void Render::texImage2D(int target, int level, int internalformat, int width, int height, void* data)
{
    ctx->texImage2D(target, level, internalformat, width, height, data);
}
}
