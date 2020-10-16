//
//  CppTexture.hpp
//  CppRender
//
//  Created by yu bo on 2020/10/16.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppTexture_hpp
#define CppTexture_hpp

#include <stdio.h>
#include "CppDefine.h"
#include "glm/vec4.hpp"

namespace CppRender{
class Texture{
public:
    void image2D(int target, int level, int internalformat, int width, int height, void* data);
    void clearColor(glm::vec4 color);
    void* getData(int level = 0) { return _data[level]; }
private:
    int _target = CPPRENDER_INVALID_VALUE;
    int _format = CPPRENDER_INVALID_VALUE;
    int _width = CPPRENDER_INVALID_VALUE;
    int _height =CPPRENDER_INVALID_VALUE;
    void* _data[CPPRENDER_TEXUTRE_MAX_LEVEL] = {nullptr};
};
}

#endif /* CppTexture_hpp */
