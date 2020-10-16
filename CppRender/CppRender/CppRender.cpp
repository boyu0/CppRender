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

Context* Render::getContext()
{
    return ctx;
}

void Render::genFrameBuffers(int n, int* ids)
{
}

void Render::bindFrameBuffer(int id)
{
    
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

}
