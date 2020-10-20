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
#include "CppContext.hpp"
#include "CppLuaEngine.hpp"
#include "CppVertexShader.hpp"
#include "CppFragmentShader.hpp"

namespace CppRender{
void Program::attach(Shader* shader)
{
    switch (shader->getType())
    {
    case CR_VERTEX_SHADER:
        _vertexShader = dynamic_cast<VertexShader*>(shader);
        break;
    case CR_FRAGMENT_SHADER:
        _fragmentShader = dynamic_cast<FragmentShader*>(shader);
        break;
    default:
        break;
    }
}

bool Program::link()
{
    return true;
}

void Program::setProgramAttribute(int n, int index, int size, int type, bool normalized, void* data)
{
    _vertexShader->setAttribute(n, index, size, type, normalized, data);
}

void Program::run()
{

}

}