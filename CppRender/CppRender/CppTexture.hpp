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
    int _target = CR_INVALID_VALUE;
    int _format = CR_INVALID_VALUE;
    int _width = CR_INVALID_VALUE;
    int _height =CR_INVALID_VALUE;
    void* _data[CR_TEXUTRE_MAX_LEVEL] = {nullptr};
};
}

#endif /* CppTexture_hpp */
