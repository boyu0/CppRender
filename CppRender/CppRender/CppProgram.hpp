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

namespace CppRender{
class Shader;
class Context;
class VertexShader;
class FragmentShader;
class Program{
public:
    Program(Context* ctx):_ctx(ctx){}

public:
    void attach(Shader* shader);
    bool link();
    void run();
    void setProgramAttribute(int n, int index, int size, int type, bool normalized, void* data);

private:
    Context* _ctx{};
    VertexShader* _vertexShader{};
    FragmentShader* _fragmentShader{};
};
}

#endif /* CppProgram_hpp */
