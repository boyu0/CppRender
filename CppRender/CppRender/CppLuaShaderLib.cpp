//
//  CppLuaShaderLib.cpp
//  CppRender
//
//  Created by yubo on 2020/10/19.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppLuaShaderLib.hpp"
extern "C"{
#include "lauxlib.h"
#include "lualib.h"
#include "llex.h"
}
#include "CppUtils.hpp"
#include "CppProgram.hpp"
#include "CppLuaEngine.hpp"
#include "glm/glm.hpp"

namespace CppRender{
static int shader_texture2D (lua_State *L) {
  lua_getupvalue(L, -4, 1);
  lua_getfield(L, -1, CR_PROGRAM_LUA_NAME);
  Program* program = (Program*)lua_touserdata(L, -1);
  lua_pop(L, 2);
  float texture = lua_tonumber(L, 2);

  lua_geti(L, 1, 1);
  float u = lua_tonumber(L, -1);
  lua_pop(L, 1);
  lua_geti(L, 1, 2);
  float v = lua_tonumber(L, -1);
  lua_pop(L, 1);

  float color[4];
  program->getTexture2DColor(texture, u, v, color);
  lua_newtable(L);
  for(int i = 0; i < 4; ++i)
  {
    lua_pushnumber(L, color[i]);
    lua_seti(L, -2, i+1);
  }

  return 1;
}

static int shader_matmul(lua_State* L){

    Utils::matmul(L, 1, 2);
    return 1;
}

static const luaL_Reg shaderlib[] = {
    {"texture2D",   shader_texture2D},
    {"mul",   shader_matmul},
  {NULL, NULL},
};

int luaopen_shader (lua_State *L) {
  luaL_newlib(L, shaderlib);
  return 1;
}
}
