//
//  CppShaderEngine.cpp
//  CppRender
//
//  Created by yu bo on 2020/10/18.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppLuaEngine.hpp"
#include "CppUtils.hpp"
extern "C"{
#include "lauxlib.h"
#include "lualib.h"
}

namespace CppRender{
bool LuaEngine::init()
{
    L = luaL_newstate();
    if(L == nullptr){
        return false;
    }
    luaL_openlibs(L);

    return true;
}

bool LuaEngine::run(const std::string& file)
{
    int status = luaL_dofile(L, file.c_str());
    if(status != LUA_OK){
        CR_LOGE("加载shader错误：%s\n", lua_tostring(L, -1));
        CR_ASSERT(false, "");
    }
    return status == LUA_OK;
}
}

