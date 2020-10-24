//
//  CppVertexArray.cpp
//  CppRender
//
//  Created by yubo on 2020/10/16.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppVertexArray.hpp"
#include "CppContext.hpp"

namespace CppRender {
void VertexArray::vertexAttributePointer(int index, int size, int type, bool normalized, int stride, int pointer)
{
    _vertexAttributePointerInfos[index] = VertexAttributePointerInfo{size, type, normalized, stride, pointer, _ctx->get(CR_ARRAY_BUFFER)};
}

void VertexArray::loadOne(int n)
{
    for(auto&& pair : _vertexAttributePointerInfos)
    {
        auto& info = pair.second;
        int size = 0;
        char* data = (char*)_ctx->mapBufferIndex(info.buffer, &size);
        int offset = n*info.stride + info.pointer;
        _ctx->setProgramAttribute(pair.first, info.size, info.type, info.normalized, data + offset);
    }
}
}
