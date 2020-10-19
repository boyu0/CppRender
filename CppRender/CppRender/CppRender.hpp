//
//  CppRender.hpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CR_
#define CR_

#include "CppDefine.h"
#include <string>

namespace CppRender{
class Context;
class Render
{
public:
    static bool init(int width, int height);
    static void genFrameBuffers(int n, int* ids);
    static void bindFrameBuffer(int id);
    
    static void clearColor(float r, float g, float b, float a);
    static void clear(int bit);
    
    static void getRenderData(void** data);
    
    static void begin(int mode);
    static void end();
    static void vertex3f(float x, float y, float z);
    static void color3f(float r, float g, float b);

    static int createShader(int type, const std::string& file);
    static int createProgram();

    static Context* getContext();
};
}

#endif
