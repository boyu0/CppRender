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
#include "glm/vec4.hpp"
#include "CppDefine.h"

namespace CppRender{
class Primitive;
class Draw{
public:
    void begin(int mode);
    void end();
    void vertex3f(float x, float y, float z);
    void color3f(float r, float g, float b);

private:
    glm::vec4 _currentColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    int _currentMode = CPPRENDER_INVALID_VALUE;
    Primitive* _primitive;
};
}

#endif /* CppDraw_hpp */
