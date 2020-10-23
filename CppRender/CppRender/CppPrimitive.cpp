//
//  CppPrimitive.cpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppPrimitive.hpp"
#include "glm/glm.hpp"
#include "glm/common.hpp"
#include "glm/matrix.hpp"
#include "glm/ext.hpp"
#include "CppContext.hpp"

namespace CppRender{
Primitive::~Primitive()
{
}

void Primitive::newVertex(float pos[4])
{
    _vetexValues.push_back({{pos[0], pos[1], pos[2], pos[3]}});
    _vertexAttrs.push_back({});
}

float* Primitive::getVertexAttrf(int index, int name, int* count)
{
    auto& v = _vertexAttrs[index][name];
    *count = v.count;
    return v.f;
}

void Primitive::pushVertexAttrf(int count, float f[])
{
    auto& v = _vertexAttrs.back();
    VertexAttr attr{count};
    for(int i = 0; i < count; ++i)
    {
        attr.f[i] = f[i];
    }
    v.emplace_back(attr);
}
}
