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

bool Render::init()
{
    ctx = new Context();
    if(ctx != nullptr ||  !ctx->init()){
        return false;
    }
    
    return true;
}

void Render::genFrameBuffers(int n, int* ids)
{
}

static void bindFrameBuffer(int id)
{
    
}

void Render::clear(unsigned int bit)
{
    
}

}
