//
//  CppShader.cpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppShader.hpp"
#include "CppContext.hpp"
#include "CppLuaEngine.hpp"
#include "CppUtils.hpp"



namespace CppRender{
static int g_index = 0;
bool Shader::init(Context* ctx, const std::string& file)
{
    _ctx = ctx;
    LuaEngine* engine = _ctx->getLuaEngine();
    _env = std::string(CR_SHADER_ENV_PREFIX) + std::to_string(g_index++);
    engine->newEnv(_env);
    bool ok = engine->run(_env, file);

    return ok;
}

bool Shader::unpackTableToEnv(const std::string& name)
{
    bool ret = false;

    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_env);
    engine->getField(name);

    if(!engine->isNil())
    {
        ret = true;
        engine->unpack();
    }

    engine->pop(2);
    return ret;
}
void Shader::initVariables(const std::string& name, std::vector<std::string>& target)
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_env);
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

bool Shader::runOne()
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_env);
    engine->getField(CR_SHADER_MAINFUNC);
    if(engine->isNil())
    {
        CR_ASSERT(false, "main函数不存在");
        engine->pop(2);
        return false;
    }

    bool ret = engine->runFunc(_env, 0, 0);
    engine->pop(1);
    return ret;
}

Shader::~Shader(){
    if(!_env.empty())
    {
        LuaEngine* engine = _ctx->getLuaEngine();
        engine->deleteEnv(_env);
    }
}
}
