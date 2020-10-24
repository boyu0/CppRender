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
#include "llex.h"
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
    lua_getglobal(L, LUA_ENV);
    lua_setglobal(L, CR_LUA_ENV);

    return true;
}

void LuaEngine::newEnv(const std::string& name)
{
    lua_pushglobaltable(L);
    lua_newtable(L);
    lua_newtable(L);
    lua_getglobal(L, LUA_GNAME);
    lua_setfield(L, -2, "__index");
    lua_setmetatable(L, -2);
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

void LuaEngine::setSuper()
{
    lua_newtable(L);
    lua_pushvalue(L, -2);
    lua_setfield(L, -2, "__index");
    lua_setmetatable(L, -3);
    pop(2);
}

void LuaEngine::getEnv(const std::string& env)
{
    lua_getglobal(L, env.c_str());
}

bool LuaEngine::isNil()
{
    return lua_isnil(L, -1);
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

void LuaEngine::getField(const std::string& name, int index)
{
    lua_getfield(L, index, name.c_str());
}

void LuaEngine::getFieldOrNewTable(const std::string& name, int index)
{
    getField(name, index);
    if(isNil())
    {
        pop(1);
        newTable();
        setField(name, index-1);
        getField(name, index);
    }
}

void LuaEngine::pop(int n)
{
    lua_pop(L, n);
}

void LuaEngine::setField(const std::string& name, int index)
{
    lua_setfield(L, index, name.c_str());
}

std::string LuaEngine::getFieldString(const std::string& name, int index, bool* b)
{
    getField(name, index);
    CR_LUA_CHECKNOTNIL(b, "");
    std::string ret = lua_tostring(L, index);
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

std::string LuaEngine::toString(int index)
{
    return lua_tostring(L, index);
}

float LuaEngine::toFloat(int index)
{
    return lua_tonumber(L, index);
}

int LuaEngine::type(int index)
{
    return lua_type(L, index);
}

void LuaEngine::setFieldUserData(const std::string& name, void* userdata, int index)
{
    lua_pushlightuserdata(L, userdata);
    lua_setfield(L, index-1, name.c_str());
}

void LuaEngine::setFieldv(float v[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        lua_pushnumber(L, v[i]);
        lua_seti(L, -2, i+1);
    }
}

void LuaEngine::setFieldv(int v[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        lua_pushinteger(L, v[i]);
        lua_seti(L, -2, i+1);
    }
}

void LuaEngine::setFieldFloat(const std::string& name, float f, int index)
{
    lua_pushnumber(L, f);
    lua_setfield(L, index-1, name.c_str());
}

void LuaEngine::setFieldInt(const std::string& name, int i, int index)
{
    lua_pushinteger(L, i);
    lua_setfield(L, index-1, name.c_str());
}

void LuaEngine::getFieldv(const std::string& name, int index, float v[], int* size)
{
    getField(name);
    int t = type();
    if(t == LUA_TNUMBER){
        v[0] = toFloat();
        if(size){ *size = 1; }
    }else if(t == LUA_TTABLE){
        int count = getLen();
        for(int i = 0; i < count; ++i){
            v[i] = getFieldFloat(i+1);
        }
        if(size){ *size = count; }
    }else{
        CR_ASSERT(false, "");
    }
    pop(1);
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

void LuaEngine::walk(std::function<void()> func)
{
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        func();
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

bool LuaEngine::runFunc(const std::string& env, int args, int rets)
{
    lua_getglobal(L, env.c_str());
    lua_setupvalue(L, -2, 1);

    if(lua_pcall(L, args, rets, 0) != 0){
        CR_LOGE("lua RUNTIME ERROR! msg:%s", lua_tostring(L, -1));
        pop(1);
        return false;
    }
    return true;
}

bool LuaEngine::run(const std::string& env, const std::string& file)
{
    int status = luaL_loadfile(L, file.c_str());
    if(status != LUA_OK){
        CR_LOGE("加载shader错误：%s\n", lua_tostring(L, -1));
        CR_ASSERT(false, "");
    }

    lua_getglobal(L, env.c_str());
    lua_setupvalue(L, -2, 1);

    status = lua_pcall(L, 0, 0, 0);

    if(status != LUA_OK){
        CR_LOGE("加载shader错误：%s\n", lua_tostring(L, -1));
        CR_ASSERT(false, "");
    }
    return status == LUA_OK;
}
}

