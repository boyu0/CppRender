//
//  CppDraw.cpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppDraw.hpp"
#include "CppTriangles.hpp"
#include "CppUtils.hpp"

namespace CppRender{
void Draw::begin(int mode)
{
    _currentMode = mode;
    if(_primitive)
    {
        delete _primitive;
        _primitive = nullptr;
    }

    switch (mode)
    {
    case CR_TRIANGLES:
        _primitive = new Triangles();
        break;
    default:
        CR_ASSERT(false, "");
        break;
    }
}

void Draw::end()
{
}

void Draw::vertex3f(float x, float y, float z)
{
    
}

void Draw::color3f(float r, float g, float b)
{
    _currentColor = glm::vec4(r, g, b, 1.0f);
}

}
