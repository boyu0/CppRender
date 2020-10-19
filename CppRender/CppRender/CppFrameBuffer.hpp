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
class FrameBuffer{
public:

    void bindRenderBuffer(int idx);
    void bindTexture2D(int idx);
    void clear(int mask);
    inline int getTexture2D() { return _texture2DIndex; }
    
private:
    int _renderBufferIndex = CR_INVALID_VALUE;
    int _texture2DIndex = CR_INVALID_VALUE;
};
}

#endif /* CppFrameBuffer_hpp */
