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
#include "glm/glm.hpp"

namespace CppRender{
bool VertexShader::init(Context* ctx, const std::string& file)
{
    if(!Shader::init(ctx, file)){
        return false;
    }

    _type = CR_VERTEX_SHADER;
    
    LuaEngine* engine = _ctx->getLuaEngine();
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
        engine->pop(1);
        engine->popEnv();
        return;
    }
    int len = engine->getLen();
    for(int i = 1; i <= len; ++i)
    {
        _layouts.emplace_back(engine->getFieldString(i));
    }
    engine->pop(1);
    engine->popEnv();
}

void VertexShader::setAttribute(int n, int index, int size, int type, bool normalized, void* data)
{
    glm::vec4 v;
    for(int i = 0; i < size; ++i)
    {
        switch (type)
        {
        case CR_FLOAT:
                v[i] = *((float*)data + i);
            break;
        default:
            break;
        }
    }
    LuaEngine* engine = _ctx->getLuaEngine();
    printf("%d", engine->getTop());
//    engine->pushEnv(_env);
    runOne();
    engine->getGlobal(_layouts[index]);
    if(engine->isNil())
    {
        printf("xxxxx");
    }
    engine->setFieldvf(v, size);
    engine->pop(1);
//    engine->popEnv();
    printf("%d", engine->getTop());
}

}
