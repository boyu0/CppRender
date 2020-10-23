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

void Program::pushVertexAttrf(int count, float f[])
{
    _primitive->pushVertexAttrf(count, f);
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

void Program::runFragment(int count, int index[], float portion[], float color[4])
{
    auto& veryings = _vertexShader->getVeryings();
    for(int i = 0; i < veryings.size(); ++i)
    {
        float result[4] = {0};
        int pcount = 0;
        for(int j = 0; j < count; ++j)
        {
            float* p = _primitive->getVertexAttrf(index[j], i, &pcount);
            for(int k = 0; k < pcount; ++k)
            {
                result[k] += portion[j] * p[k];
            }
        }
        _fragmentShader->setVerying(veryings[i], pcount, result);
    }
    _fragmentShader->runOne();
    _fragmentShader->getResult(color);
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
