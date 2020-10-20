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
    _env = std::string(CR_SHADER_LIB_NAME) + std::to_string(g_index++);
    
    engine->pushEnv(CR_SHADER_LIB_NAME);
    engine->newEnv(_env);
    engine->pushEnv(_env);
    bool ok = engine->run(file);
    engine->popEnv();
    engine->popEnv();

    return ok;
}

bool Shader::unpackTableToEnv(const std::string& name)
{
    bool ret = false;

    LuaEngine* engine = _ctx->getLuaEngine();
    engine->pushEnv(CR_SHADER_LIB_NAME);
    engine->pushEnv(_env);
    engine->getEnv();
    engine->getGlobal(name);

    if(!engine->isNil())
    {
        ret = true;
        engine->unpack();
    }

    engine->pop(2);
    engine->popEnv();
    engine->popEnv();
    return ret;
}

bool Shader::runOne()
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getGlobal(CR_SHADER_MAINFUNC);
    if(engine->isNil())
    {
        CR_ASSERT(false, "main函数不存在");
        engine->pop(1);
        return false;
    }

    bool ret = engine->runFunc(0, 0);
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
