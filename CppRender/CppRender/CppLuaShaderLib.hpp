//
//  CppLuaShaderLib.hpp
//  CppRender
//
//  Created by yubo on 2020/10/19.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppLuaShaderLib_hpp
#define CppLuaShaderLib_hpp

#include <stdio.h>
extern "C"{
#include "lua.h"
}

namespace CppRender{
extern int luaopen_shader (lua_State *L);
}

#endif /* CppLuaShaderLib_hpp */
