//
//  CppDraw.cpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppDraw.hpp"

namespace CppRender{
void Draw::begin(int mode)
{
    _currentMode = mode;
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
