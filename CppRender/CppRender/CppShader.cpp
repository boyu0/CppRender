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

namespace CppRender{
bool Shader::init(Context* ctx, const std::string& file)
{
    LuaEngine* engine = ctx->getLuaEngine();
    return engine->run(file);
}

Shader::~Shader(){
    
}
}
