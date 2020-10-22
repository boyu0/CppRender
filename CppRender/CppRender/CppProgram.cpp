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
#include "CppTriangles.hpp"

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

void Program::setVertexAttrf(int name, int count, float f[])
{
    _primitive->setVertexAttrf(name, count, f);
}

void Program::setProgramAttribute(int n, int index, int size, int type, bool normalized, void* data)
{
    _vertexShader->setAttribute(n, index, size, type, normalized, data);
}

bool Program::runVertex(int start, int count)
{
    for(int i = start; i < start + count; ++i)
    {
        _ctx->vertexArrayLoadOne(i);
        _vertexShader->runOne();
        _vertexShader->dealResult(this);
    }

    return true;
}

void Program::runFragment(float x, float y, float color[4])
{
    color[0] = 1.0f;
    color[1] = 0.0f;
    color[2] = 0.0f;
    color[3] = 1.0f;
}

void Program::newVertex(float pos[4])
{
    _primitive->newVertex(pos);
}

void Program::createPrimitive(int mode)
{
    switch (mode)
    {
    case CR_TRIANGLES:
        _primitive = new Triangles(_ctx);
        break;
    default:
        break;
    }
}

void Program::run(int mode, int start, int count)
{
    createPrimitive(mode);
    runVertex(start, count);
    _primitive->raster(this);
}

}
