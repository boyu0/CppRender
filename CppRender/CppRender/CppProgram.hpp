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
    void setAttribute(int index, int size, int type, bool normalized, void* data);
    void setUniform(const std::string& name, float x);
    void setUniform(const std::string& name, float x, float y);
    void setUniform(const std::string& name, float x, float y, float z);
    void setUniform(const std::string& name, float x, float y, float z, float w);
    void setUniform(const std::string& name, int x);
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

private:
    Context* _ctx{};
    VertexShader* _vertexShader{};
    FragmentShader* _fragmentShader{};
    Primitive* _primitive{};
    std::string _env;
};
}

#endif /* CppProgram_hpp */
