//
//  CppVertexShader.cpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppVertexShader.hpp"
#include "CppUtils.hpp"
#include "CppContext.hpp"
#include "CppLuaEngine.hpp"

namespace CppRender{
bool VertexShader::init(Context* ctx, const std::string& file)
{
    if(!Shader::init(ctx, file)){
        return false;
    }

    _type = CR_VERTEX_SHADER;

    unpackTableToEnv(CR_SHADER_ATTRIBUTE);
    unpackTableToEnv(CR_SHADER_VERYING);
    unpackTableToEnv(CR_SHADER_UNIFORM);
    initLayouts();

    return true;
}

void VertexShader::initLayouts()
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->pushEnv(_env);
    engine->getGlobal(CR_SHADER_LAYOUT);
    if(engine->isNil())
    {
        return;
    }

    engine->getf
}

void VertexShader::setAttribute(int n, int index, int size, int type, bool normalized, void* data)
{

}

}
