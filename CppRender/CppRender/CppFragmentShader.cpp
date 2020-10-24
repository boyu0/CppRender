//
//  CppFragmentShader.cpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppFragmentShader.hpp"
#include "CppLuaEngine.hpp"
#include "CppContext.hpp"

namespace CppRender{

bool FragmentShader::init(Context* ctx, const std::string& file)
{
    if(!Shader::init(ctx, file)){
        return false;
    }

    _type = CR_FRAGMENT_SHADER;
    return true;
}

void FragmentShader::dealResult()
{

}

void FragmentShader::setVerying(const std::string& name, int count, float f[])
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_env);
    engine->getFieldOrNewTable(name);
    engine->setFieldv(f, count);
    engine->pop(2);
}

void FragmentShader::getResult(float color[4])
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_env);
    engine->getFieldv(CR_SHADER_VERT_COLOR, -1, color);
    engine->pop(1);
}
}
