//
//  CppFrameBuffer.hpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppFrameBuffer_hpp
#define CppFrameBuffer_hpp

#include <stdio.h>
#include "CppDefine.h"

namespace CppRender{
class Context;
class FrameBuffer{
public:
    FrameBuffer(Context* ctx):_ctx(ctx){}

public:
    void bindRenderBuffer(int idx);
    void bindTexture2D(int idx);
    void clear(int mask);
    inline int getTexture2D() { return _texture2DIndex; }
    inline int* getViewPort() { return _view; }
    void drawArrays(int mode, int start, int count);
    void doClear();
    void* getData();
    void getSize(int size[2]);
    int genDepthBuffer();
    inline int getDepthBuffer(){return _depthBufferIndex;}
    void deleteDepthBuffer();

private:
    Context* _ctx{};
    int _renderBufferIndex = CR_INVALID_VALUE;
    int _depthBufferIndex = CR_INVALID_VALUE;
    int _texture2DIndex = CR_INVALID_VALUE;
    int _view[4] = {0};
    float _clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    int _clearMask{};
};
}

#endif /* CppFrameBuffer_hpp */
