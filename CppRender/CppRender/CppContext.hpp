//
//  CppContext.hpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppContext_hpp
#define CppContext_hpp

#include <stdio.h>
#include <unordered_map>
#include "CppDefine.h"

namespace CppRender{
class VertexArray;
class FrameBuffer;
class Buffer;
class Context{
public:
    Context();
    ~Context();
    
    bool init();
    
    void genFrameBuffers(int n, int* ids);
    void bindFrameBuffer(int id);
    
private:
    std::unordered_map<int, VertexArray*> _vetexArrays;
    std::unordered_map<int, FrameBuffer*> _frameBuffers;
    std::unordered_map<int, Buffer*> _buffers;
    
    int _defaultFrameBuffer = CPPRENDER_INVALID_VALUE;
    int _frameBufferIndex = 0;
};
}

#endif /* CppContext_hpp */
