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

void Primitive::raster()
{
    glm::mat4x4 projection = _ctx->getProjection();
    std::vector<VertexValue> v(_vetexValues.size());
    for(int i = 0; i < _vetexValues.size(); ++i)
    {
        VertexValue& value = _vetexValues[i];
        glm::vec4 pos = glm::vec4(value.pos[0], value.pos[1], value.pos[2], value.pos[3]);
        glm::vec4 screenpos = projection * pos;
        printf("pos x:%f y:%f z:%f w:%f\n", screenpos.x, screenpos.y, screenpos.z, screenpos.w);
    }
}
}
