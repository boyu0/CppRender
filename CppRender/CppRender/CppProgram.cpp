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
#include "CppTriangles.hpp"
#include "CppTexture.hpp"

namespace CppRender{
static int g_index = 0;

void Program::attach(Shader* shader)
{
    _shaderEnvs[shader->getType()] = shader->getEnv();
}

bool Program::link()
{
    _env = std::string(CR_PROGRAM_ENV_PREFIX) + std::to_string(g_index++);
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->newEnv(_env);
    engine->getEnv(_env);
    engine->setFieldUserData(CR_PROGRAM_LUA_NAME, this);
    engine->pop(1);

    initVariables(CR_VERTEX_SHADER, CR_SHADER_VERYING, _veryings);
    return true;
}

void Program::pushVertexAttrf(int count, float f[])
{
    _primitive->pushVertexAttrf(count, f);
}

void Program::setAttribute(const std::string& name, int size, int type, bool normalized, void* data)
{
    Utils::setValue(_ctx, _env, name, size, type, normalized, data);
}

void Program::beginEnv(int type)
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_shaderEnvs[type]);
    engine->getEnv(_env);
    engine->setSuper();
}

void Program::endEnv(int type)
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_shaderEnvs[type]);
    engine->getEnv(CR_LUA_G);
    engine->setSuper();
}

bool Program::runVertex(int start, int count)
{
    beginEnv(CR_VERTEX_SHADER);
    for(int i = start; i < start + count; ++i)
    {
        _ctx->vertexArrayLoadOne(i);
        runShader(CR_VERTEX_SHADER);
        dealVaryings();
    }
    endEnv(CR_VERTEX_SHADER);

    return true;
}


void Program::initVariables(int type, const std::string& name, std::vector<std::string>& target)
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_shaderEnvs[type]);
    engine->getField(name);
    if(engine->isNil())
    {
        engine->pop(2);
        return;
    }
    int len = engine->getLen();
    for(int i = 1; i <= len; ++i)
    {
        target.emplace_back(engine->getFieldString(i));
    }
    engine->pop(2);
}

void Program::dealVaryings()
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_shaderEnvs[CR_VERTEX_SHADER]);
    // TODO: error
    engine->getField(CR_SHADER_VERT_POSITION);
    int count = engine->getLen();
    CR_ASSERT(count == 4, "");
    float pos[4];
    for(int i = 0; i < 4; ++i)
    {
        pos[i] = engine->getFieldFloat(i+1);
    }
    engine->pop(1);
    newVertex(pos);

    for(int index = 0; index < _veryings.size(); ++index)
    {
        float v[4] = {0};
        int count;
        engine->getFieldv(_veryings[index], -1, v, &count);
        pushVertexAttrf(count, v);
    }
}

bool Program::runShader(int type)
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_shaderEnvs[type]);
    engine->getField(CR_SHADER_MAINFUNC);
    if(engine->isNil())
    {
        CR_ASSERT(false, "main函数不存在");
        engine->pop(2);
        return false;
    }

    bool ret = engine->runFunc(_shaderEnvs[type], 0, 0);
    engine->pop(1);
    return ret;
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

void Program::setUniform(const std::string& name, float f[], int count)
{
    Utils::setValue(_ctx, _env, name, count, CR_FLOAT, false, f);
}

void Program::setUniform(const std::string& name, int x)
{
    Utils::setValue(_ctx, _env, name, 1, CR_INT, false, &x);
}

void Program::setVerying(const std::string& name, int count, float f[])
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_shaderEnvs[CR_FRAGMENT_SHADER]);
    engine->getFieldOrNewTable(name);
    engine->setFieldv(f, count);
    engine->pop(2);
}

void Program::getResultColor(float color[4])
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_shaderEnvs[CR_FRAGMENT_SHADER]);
    engine->getFieldv(CR_SHADER_VERT_COLOR, -1, color);
    engine->pop(1);
}

void Program::runFragment(int count, int index[], float portion[], float color[4])
{
    for(int i = 0; i < _veryings.size(); ++i)
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
        setVerying(_veryings[i], pcount, result);
    }
    runShader(CR_FRAGMENT_SHADER);
    getResultColor(color);
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
