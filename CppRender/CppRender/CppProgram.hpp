//
//  CppProgram.hpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppProgram_hpp
#define CppProgram_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "CppDefine.h"

namespace CppRender{
class Shader;
class Context;
class VertexShader;
class FragmentShader;
class Primitive;
class LuaEngine;
class Program{
public:
    Program(Context* ctx):_ctx(ctx){}

public:
    void attach(Shader* shader);
    bool link();
    void run(int mode, int start, int count);
    void setAttribute(const std::string& name, int size, int type, bool normalized, void* data);
    void setUniform(const std::string& name, float x);
    void setUniform(const std::string& name, float x, float y);
    void setUniform(const std::string& name, float x, float y, float z);
    void setUniform(const std::string& name, float x, float y, float z, float w);
    void setUniform(const std::string& name, int x);
    void setUniform(const std::string& name, float f[], int count);
    void pushVertexAttrf(int count, float f[]);
    void createPrimitive(int mode);
    void newVertex(float pos[4]);
    void runFragment(int count, int index[], float portion[], float color[4]);
    void getTexture2DColor(int index, float u, float v, float color[4]);
    void clear();
    void beginEnv(int type);
    void endEnv(int type);
    LuaEngine* getLuaEngine();

private:
    bool runVertex(int start, int count);

    void initVariables(int type, const std::string& name, std::vector<std::string>& target);
    void dealVaryings();
    bool runShader(int type);
    void setVerying(const std::string& name, int count, float f[]);
    void getResultColor(float color[4]);

private:
    Context* _ctx{};
    Primitive* _primitive{};
    std::string _env;
    std::string _shaderEnvs[CR_SHAER_TYPE_COUNT];
    std::vector<std::string> _veryings;
};
}

#endif /* CppProgram_hpp */
