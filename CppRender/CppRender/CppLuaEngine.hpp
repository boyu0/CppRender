//
//  CppShaderEngine.hpp
//  CppRender
//
//  Created by yu bo on 2020/10/18.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppShaderEngine_hpp
#define CppShaderEngine_hpp

#include <stdio.h>
#include <string>
extern "C"{
    #include "lua.h"
}

namespace CppRender{
class LuaEngine{
public:
    bool init();
    bool run(const std::string& file);
    
private:
    lua_State* L = nullptr;
};
}

#endif /* CppShaderEngine_hpp */
