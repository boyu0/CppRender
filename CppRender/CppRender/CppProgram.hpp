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
class Program{
public:
    Program(Context* ctx):_ctx(ctx){}

public:
    void attach(Shader* shader);
    bool link();
    void run(int mode, int start, int count);
    void setProgramAttribute(int n, int index, int size, int type, bool normalized, void* data);
    void pushVertexAttrf(int count, float f[]);
    void createPrimitive(int mode);
    void newVertex(float pos[4]);
    void runFragment(int count, int index[], float portion[], float color[4]);

private:
    bool runVertex(int start, int count);

private:
    Context* _ctx{};
    VertexShader* _vertexShader{};
    FragmentShader* _fragmentShader{};
    Primitive* _primitive{};
};
}

#endif /* CppProgram_hpp */
