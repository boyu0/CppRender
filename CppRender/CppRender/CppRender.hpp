//
//  CppRender.hpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppRender_
#define CppRender_

#include "CppDefine.h"

namespace CppRender{
class Render
{
public:
    static bool init();
    static void genFrameBuffers(int n, int* ids);
    static void bindFrameBuffer(int id);
    
    static void clear(unsigned int bit);
};
}

#endif
