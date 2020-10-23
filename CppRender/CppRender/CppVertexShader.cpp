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
    float v[4];
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
    engine->getFieldOrNewTable(_attributes[index]);
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
        pos[i] = engine->getFieldFloat(i+1);
    }
    engine->pop(1);
    program->newVertex(pos);

    for(int index = 0; index < _veryings.size(); ++index)
    {
        float v[4] = {0};
        int count;
        engine->getFieldvf(_veryings[index], -1, v, &count);
        program->pushVertexAttrf(count, v);
    }
}

}
