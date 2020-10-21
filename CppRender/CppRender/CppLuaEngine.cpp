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


#define CR_LUA_CHECKNOTNIL(b, ret) \
    if(isNil()){ \
        if(b){ *b = false; } \
        pop(1); \
        return ret; \
    }else{ if(b){*b = true; }}


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

void LuaEngine::newEnv(const std::string& name)
{
    lua_pushglobaltable(L);
    lua_newtable(L);
    lua_setfield(L, -2, name.c_str());
    pop(1);
}

void LuaEngine::deleteEnv(const std::string& name)
{
    lua_pushglobaltable(L);
    lua_pushnil(L);
    lua_setfield(L, -2, name.c_str());
    pop(1);
}

void LuaEngine::pushEnv(const std::string& env)
{
    lua_pushglobaltable(L);
    lua_getfield(L, -1, env.c_str());
    lua_getglobal(L, LUA_GNAME);
    lua_setmetatable(L, -2);
    lua_setglobal(L, LUA_GNAME);
    pop(1);
    _gs.emplace(env);
}

bool LuaEngine::isNil()
{
    return lua_isnil(L, -1);
}

void LuaEngine::popEnv()
{
    _gs.pop();
    if(_gs.empty())
    {
        lua_getglobal(L, CR_LUA_G);
        lua_setglobal(L, LUA_GNAME);
    }else{
        std::string& env = _gs.top();
        lua_pushglobaltable(L);
        lua_getfield(L, -1, env.c_str());
        lua_setglobal(L, LUA_GNAME);
        pop(1);
    }
}

void LuaEngine::getEnv()
{
    getGlobal(LUA_GNAME);
}

void LuaEngine::getGlobal(const std::string& name)
{
    lua_getglobal(L, name.c_str());
}

void LuaEngine::setGlobal(const std::string& name)
{
    lua_setglobal(L, name.c_str());
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

std::string LuaEngine::getFieldString(const std::string& name, bool* b)
{
    getField(name);
    CR_LUA_CHECKNOTNIL(b, "");
    std::string ret = lua_tostring(L, -1);
    pop(1);
    return ret;
}

std::string LuaEngine::getFieldString(int i, bool* b)
{
    getField(i);
    CR_LUA_CHECKNOTNIL(b, "");
    std::string ret = lua_tostring(L, -1);
    pop(1);
    return ret;
}

void LuaEngine::setFieldvf(glm::vec4 v, int size)
{
    for(int i = 0; i < size; ++i)
    {
        lua_pushnumber(L, v[i]);
        lua_seti(L, -2, i+1);
    }
}

float LuaEngine::getFieldFloat(const std::string& name, bool* b)
{
    getField(name);
    CR_LUA_CHECKNOTNIL(b, 0);
    float ret = lua_tonumberx(L, -1, nullptr);
    pop(1);
    return ret;
}

float LuaEngine::getFieldFloat(int i, bool* b)
{
    getField(i);
    CR_LUA_CHECKNOTNIL(b, 0);
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
}

void LuaEngine::newTable()
{
    lua_newtable(L);
}

int LuaEngine::getTop()
{
    return lua_gettop(L);
}

int LuaEngine::getLen()
{
    return lua_rawlen(L, -1);
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

