//
//  CppShaderEngine.cpp
//  CppRender
//
//  Created by yu bo on 2020/10/18.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppLuaEngine.hpp"
#include "CppUtils.hpp"
#include "CppLuaShaderLib.hpp"
extern "C"{
#include "lauxlib.h"
#include "lualib.h"
}

namespace CppRender{
static const luaL_Reg loadedlibs[] = {
  {CR_SHADER_LIB_NAME, luaopen_shader},
  {NULL, NULL}
};

void luaEngine_openlibs (lua_State *L) {
  const luaL_Reg *lib;
  /* "require" functions from 'loadedlibs' and set results to global table */
  for (lib = loadedlibs; lib->func; lib++) {
      luaL_requiref(L, lib->name, lib->func, 1);
      lua_pop(L, 1);  /* remove lib */
  }
}

bool LuaEngine::init()
{
    L = luaL_newstate();
    if(L == nullptr){
        return false;
    }
    luaL_openlibs(L);
    luaEngine_openlibs(L);
    
    lua_getglobal(L, LUA_GNAME);
    lua_setglobal(L, CR_LUA_G);

    return true;
}

void LuaEngine::pushG(const std::string& env)
{
    lua_getglobal(L, env.c_str());
    lua_getglobal(L, LUA_GNAME);
    lua_setmetatable(L, -2);
    lua_setglobal(L, LUA_GNAME);
    _gs.emplace(env);
}

bool LuaEngine::isNil()
{
    return lua_isnil(L, -1);
}

void LuaEngine::popG()
{
    if(_gs.empty())
    {
        lua_getglobal(L, CR_LUA_G);
    }else{
        std::string& env = _gs.top();
        lua_pushstring(L, env.c_str());
        _gs.pop();
    }
    lua_setglobal(L, LUA_GNAME);
}

void LuaEngine::getG()
{
    getGlobal(LUA_GNAME);
}

void LuaEngine::getGlobal(const std::string& name)
{
    lua_getglobal(L, name.c_str());
}

void LuaEngine::getField(int i)
{
    lua_geti(L, -1, i);
}

void LuaEngine::getField(const std::string& name)
{
    lua_getfield(L, -1, name.c_str());
}

void LuaEngine::pop(int n)
{
    lua_pop(L, n);
}

std::string LuaEngine::getFieldString(const std::string& name)
{
    getField(name);
    std::string ret = lua_tostring(L, -1);
    pop(1);
    return ret;
}

float LuaEngine::getFieldFloat(const std::string& name)
{
    getField(name);
    float ret = lua_tonumberx(L, -1, nullptr);
    pop(1);
    return ret;
}

float LuaEngine::getFieldFloat(int i)
{
    getField(i);
    float ret = lua_tonumberx(L, -1, nullptr);
    pop(1);
    return ret;
}

void LuaEngine::unpack()
{
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        lua_pushvalue(L, -2);
        lua_pushvalue(L, -2);
        lua_settable(L, -6);
        pop(1);
    }
    pop(1);
}

int LuaEngine::getTop()
{
    return lua_gettop(L);
}

bool LuaEngine::runFunc(int args, int rets)
{
    if(lua_pcall(L, args, rets, 0) != 0){
        CR_LOGE("lua RUNTIME ERROR! msg:%s", lua_tostring(L, -1));
        pop(1);
        return false;
    }
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

