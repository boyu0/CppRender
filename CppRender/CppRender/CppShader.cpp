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
bool Shader::init(Context* ctx, const std::string& file)
{
    _engine = ctx->getLuaEngine();

    _engine->pushG(CR_SHADER_LIB_NAME);
    bool ok = _engine->run(file);
    unpackTableToGlobal(CR_SHADER_ATTRIBUTE);
    _engine->popG();
    return ok;
}


bool Shader::unpackTableToGlobal(const std::string& name)
{
    int top = _engine->getTop();
    bool ret = false;
    _engine->getG();
    _engine->getGlobal(name);

    if(!_engine->isNil())
    {
        ret = true;
        _engine->unpack();
    }

    _engine->pop(2);
    printf("%d", _engine->getTop());
    CR_ASSERT(top == _engine->getTop(), "");
    return ret;
}

bool Shader::runOne()
{
    _engine->getGlobal("main");
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
}
}
