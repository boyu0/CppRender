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
    _engine = ctx->getLuaEngine();
    _identifier = std::string(CR_SHADER_LIB_NAME) + std::to_string(g_index++);
    
    _engine->pushEnv(CR_SHADER_LIB_NAME);
    _engine->newEnv(_identifier);
    _engine->pushEnv(_identifier);
    bool ok = _engine->run(file);
    _engine->popEnv();
    _engine->popEnv();

    return ok;
}

bool Shader::unpackTableToEnv(const std::string& name)
{
    bool ret = false;
    
    _engine->pushEnv(CR_SHADER_LIB_NAME);
    _engine->pushEnv(_identifier);
    _engine->getEnv();
    _engine->getGlobal(name);

    if(!_engine->isNil())
    {
        ret = true;
        _engine->unpack();
    }

    _engine->pop(2);
    _engine->popEnv();
    _engine->popEnv();
    return ret;
}

bool Shader::runOne()
{
    _engine->getGlobal(CR_SHADER_MAINFUNC);
    if(_engine->isNil())
    {
        CR_ASSERT(false, "main函数不存在");
        _engine->pop(1);
        return false;
    }

    bool ret = _engine->runFunc(0, 0);
    return ret;
}

Shader::~Shader(){
    if(!_identifier.empty())
    {
        _engine->deleteEnv(_identifier);
    }
}
}
