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
#include "CppRenderBuffer.hpp"

namespace CppRender{
class Context;
class Texture{
public:
    Texture(Context* ctx):_ctx(ctx){}
public:
    void image2D(int target, int level, int internalformat, int width, int height, void* data);
    void clearColor(float color[4]);
    void* getData(int level = 0) { return _buffers[level]->getData(); }
    inline int getWidth() { return _buffers[0]->getWidth(); }
    inline int getHeight() { return _buffers[0]->getHeight(); }
    inline int getInternalFormat() { return _buffers[0]->getInternalFormat(); }
    inline int getTarget() { return _target; }
    void readPixel(int level, int x, int y, float color[4]);
    void readPixel(int level, float x, float y, float color[4]);
private:
    Context* _ctx{};
    RenderBuffer* _buffers[CR_TEXUTRE_MAX_LEVEL] = {};
    int _target{};
};
}

#endif /* CppTexture_hpp */
