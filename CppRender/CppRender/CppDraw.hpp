//
//  CppDraw.hpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppDraw_hpp
#define CppDraw_hpp

#include <stdio.h>
#include "CppDefine.h"
#include <vector>
#include "glm/glm.hpp"

namespace CppRender{
class Primitive;
class Context;
class Draw{
public:
    Draw(Context* ctx);

private:
    struct VertexInfo{
        float pos[4] = {0.0f};
        float color[4] = {0.0f};
        float uv[2] = {0.0f};
    };
public:
    void begin(int mode);
    void end();
    void vertexf(float x, float y, float z = 0.0f, float w = 1.0f);
    void colorf(float r, float g, float b, float a = 1.0f);
    void uvf(float u, float v);

private:
    float _currentColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float _currentUV[2] = {0.0f, 0.0f};
    int _currentMode = CR_INVALID_VALUE;
    std::vector<VertexInfo> _vertexes;
    Context* _ctx{};
};
}

#endif /* CppDraw_hpp */
