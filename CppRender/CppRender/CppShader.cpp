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
}
