//
//  CppPrimitive.cpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppPrimitive.hpp"

namespace CppRender{
Primitive::~Primitive()
{
}

void Primitive::newVertex(float pos[4])
{
    _vetexValues.push_back({{pos[0], pos[1], pos[2], pos[3]}});
    _vertexAttrs.push_back({});
}

void Primitive::setVertexAttrf(int name, int count, float f[])
{
    auto& v = _vertexAttrs.back();
    VertexAttr attr{name, count};
    for(int i = 0; i < count; ++i)
    {
        attr.f[i] = f[i];
    }
    v.emplace_back(attr);
}
}
