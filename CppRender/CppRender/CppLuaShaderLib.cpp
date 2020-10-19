//
//  CppLuaShaderLib.cpp
//  CppRender
//
//  Created by yubo on 2020/10/19.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppLuaShaderLib.hpp"

namespace CppRender{
int luaopen_shader (lua_State *L) {
  /* open lib into global table */
  lua_pushglobaltable(L);
  return 1;
}
}
