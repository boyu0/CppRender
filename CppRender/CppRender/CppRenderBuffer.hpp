//
//  CppRenderBuffer.hpp
//  CppRender
//
//  Created by yubo on 2020/10/15.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppRenderBuffer_hpp
#define CppRenderBuffer_hpp

#include <stdio.h>
#include "CppDefine.h"

namespace CppRender{
class Context;
class RenderBuffer{
public:
    RenderBuffer(Context* ctx):_ctx(ctx){}

public:
    void storage(int target, int internalformat, int width, int height, void* data = nullptr);
    void clearColor(float color[4]);
    inline void* getData() { return _data; }
    inline int getWidth() { return _width; }
    inline int getHeight() { return _height; }
    inline int getInternalFormat() { return _format; }

private:
    Context* _ctx{};
    int _target = CR_INVALID_VALUE;
    int _format = CR_INVALID_VALUE;
    int _width = CR_INVALID_VALUE;
    int _height =CR_INVALID_VALUE;
    void* _data{};
};
}

#endif /* CppRenderBuffer_hpp */
