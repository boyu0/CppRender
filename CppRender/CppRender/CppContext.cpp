//
//  CppContext.cpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppContext.hpp"
#include "CppFrameBuffer.hpp"
#include "CppRender.hpp"
#include "CppUtils.hpp"

namespace CppRender{
Context::Context()
{
    
}

Context::~Context()
{
    
}

void Context::genFrameBuffers(int n, int* ids)
{
    for (int i = 0; i < n; ++i) {
        FrameBuffer* buffer = new FrameBuffer();
        _frameBuffers.emplace(std::pair<_frameBufferIndex++, buffer>);
    }
}

void Context::bindFrameBuffer(int id)
{
    
}

bool Context::init()
{
    genFrameBuffers(1, &_defaultFrameBuffer);
    CPPRENDER_CHECK_RETURN_FALSE(_defaultFrameBuffer != CPPRENDER_INVALID_VALUE);
    
    return true;
}
}
