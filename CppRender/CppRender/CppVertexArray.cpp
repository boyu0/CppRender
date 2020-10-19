//
//  CppVertexArray.cpp
//  CppRender
//
//  Created by yubo on 2020/10/16.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppVertexArray.hpp"

namespace CppRender {
    void VertexArray::vertexAttributePointer(int index, int size, int type, bool normalized, int stride, int pointer)
    {
        _vertexAttributePointerInfos.emplace(std::make_pair(index, VertexAttributePointerInfo{size, type, normalized, stride, pointer}));
    }
}
