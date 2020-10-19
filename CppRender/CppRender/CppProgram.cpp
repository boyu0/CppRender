//
//  CppProgram.cpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppProgram.hpp"
#include "CppShader.hpp"
#include "CppUtils.hpp"


namespace CppRender{
void Program::attach(Shader* shader)
{
    switch (shader->getType())
    {
    case CR_VERTEX_SHADER:
        _vertexShader = shader;
        break;
    case CR_FRAGMENT_SHADER:
        _fragmentShader = shader;
        break;
    default:
        break;
    }
}

bool Program::link()
{
    return true;
}

}