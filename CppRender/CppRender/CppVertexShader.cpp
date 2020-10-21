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
#include "CppProgram.hpp"
#include "glm/glm.hpp"
extern "C"{
    #include "lua.h"
}

namespace CppRender{
bool VertexShader::init(Context* ctx, const std::string& file)
{
    if(!Shader::init(ctx, file)){
        return false;
    }

    _type = CR_VERTEX_SHADER;
    initVariables(CR_SHADER_ATTRIBUTE, _attributes);
    initVariables(CR_SHADER_VERYING, _veryings);
    initVariables(CR_SHADER_UNIFORM, _uniforms);

    return true;
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
    engine->getEnv(_env);
    engine->getField(_attributes[index]);
    if(engine->isNil())
    {
        engine->pop(1);
        engine->newTable();
        engine->setField(_attributes[index]);
        engine->getField(_attributes[index]);
    }
    engine->setFieldvf(v, size);
    engine->pop(2);
}

void VertexShader::dealResult(Program* program)
{
    LuaEngine* engine = _ctx->getLuaEngine();
    engine->getEnv(_env);
    // TODO: error
    engine->getField("cr_Position");
    int count = engine->getLen();
    CR_ASSERT(count == 4, "");
    float pos[4];
    for(int i = 0; i < 4; ++i)
    {
        pos[i] = engine->getFieldFloat(i);
    }
    engine->pop(1);
    program->newVertex(pos);

    for(int index = 0; index < _veryings.size(); ++index)
    {
        const std::string& name = _veryings[index];
        engine->getField(name);

        int type = engine->type();
        if(type == LUA_TNUMBER){
            float v = engine->toFloat();
            program->setVertexAttrf(index, 1, &v);
        }else if(type == LUA_TTABLE){
            int count = engine->getLen();
            float v[4] = {0};
            for(int i = 0; i < count; ++i){
                v[i] = engine->getFieldFloat(i);
            }
            program->setVertexAttrf(index, count, v);
        }else{
            CR_ASSERT(false, "");
        }
        engine->pop(1);
    }
}

}
