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
#include "CppTexture.hpp"

namespace CppRender{
static int g_index = 0;

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
    _env = std::string(CR_PROGRAM_ENV_PREFIX) + std::to_string(g_index++);
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->newEnv(_env);
    engine->getEnv(_env);
    engine->setFieldUserData(CR_PROGRAM_LUA_NAME, this);
    engine->pop(1);
    return true;
}

void Program::pushVertexAttrf(int count, float f[])
{
    _primitive->pushVertexAttrf(count, f);
}

void Program::setAttribute(int index, int size, int type, bool normalized, void* data)
{
    _vertexShader->setAttribute(index, size, type, normalized, data);
}

void Program::beginEnv(int type)
{
    Shader* shader = nullptr;
    switch (type) {
        case CR_VERTEX_SHADER:
            shader = _vertexShader;
            break;
        case CR_FRAGMENT_SHADER:
            shader = _fragmentShader;
            break;
        default:
            break;
    }
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(shader->getEnv());
    engine->getEnv(_env);
    engine->setSuper();
}

void Program::endEnv(int type)
{
    Shader* shader = nullptr;
    switch (type) {
        case CR_VERTEX_SHADER:
            shader = _vertexShader;
            break;
        case CR_FRAGMENT_SHADER:
            shader = _fragmentShader;
            break;
        default:
            break;
    }
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(shader->getEnv());
    engine->getEnv(CR_LUA_G);
    engine->setSuper();
}

bool Program::runVertex(int start, int count)
{
    beginEnv(CR_VERTEX_SHADER);
    for(int i = start; i < start + count; ++i)
    {
        _ctx->vertexArrayLoadOne(i);
        _vertexShader->runOne();
        _vertexShader->dealResult(this);
    }
    endEnv(CR_VERTEX_SHADER);

    return true;
}


void Program::setUniform(const std::string& name, float x)
{
    Utils::setValue(_ctx, _env, name, 1, CR_FLOAT, false, &x);
}
void Program::setUniform(const std::string& name, float x, float y)
{
    float f[2] = {x, y};
    Utils::setValue(_ctx, _env, name, 2, CR_FLOAT, false, f);
}
void Program::setUniform(const std::string& name, float x, float y, float z)
{
    float f[3] = {x, y, z};
    Utils::setValue(_ctx, _env, name, 3, CR_FLOAT, false, f);
}
void Program::setUniform(const std::string& name, float x, float y, float z, float w)
{
    float f[4] = {x, y, z, w};
    Utils::setValue(_ctx, _env, name, 4, CR_FLOAT, false, f);
}

void Program::setUniform(const std::string& name, int x)
{
    Utils::setValue(_ctx, _env, name, 1, CR_INT, false, &x);
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

LuaEngine* Program::getLuaEngine()
{
    return _ctx->getLuaEngine();
}

void Program::getTexture2DColor(int index, float u, float v, float color[4])
{
    Texture* tex = _ctx->getTexture(index);
    tex->readPixel(0, u, v, color);
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
    beginEnv(CR_FRAGMENT_SHADER);
    _primitive->raster(this, start, count);
    endEnv(CR_FRAGMENT_SHADER);
    clear();
}
void Program::clear()
{
    delete _primitive;
    _primitive = nullptr;
}

}
