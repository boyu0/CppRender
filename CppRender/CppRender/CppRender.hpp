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

    static void genTextures(int n, int* ids);
    static void bindTexture(int id);
    static void texCoord2f(float u, float v);
    static void texImage2D(int target, int level, int internalformat, int width, int height, void* data);
    
    static void clearColor(float r, float g, float b, float a);
    static void clear(int bit);
    
    static void getRenderData(void** data);
    
    static void begin(int mode);
    static void end();
    static void vertexf(float x, float y, float z, float w = 1.0f);
    static void colorf(float r, float g, float b, float a = 1.0f);
    static void uvf(float u, float v);

    static int createShader(int type, const std::string& file);
    static int createProgram();
    static void attachShader(int program, int shader);
    static bool linkProgram(int program);
    static void useProgram(int program);
};
}

#endif
