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
class Program{
private:

public:
    void attach(Shader* shader);
    bool link();

private:
    Shader* _vertexShader{};
    Shader* _fragmentShader{};
};
}

#endif /* CppProgram_hpp */
