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
#include <stack>
#include "glm/glm.hpp"
extern "C"{
    #include "lua.h"
}

namespace CppRender{
class LuaEngine{
public:
    bool init();
    bool run(const std::string& file);
    void newEnv(const std::string& name);
    void deleteEnv(const std::string& name);
    void pushEnv(const std::string& name);
    void getEnv();
    void popEnv();
    bool isNil();
    int getTop();

    void getGlobal(const std::string& name);
    void setGlobal(const std::string& name);
    void getField(int i);
    void getField(const std::string& name);
    int getLen();
    std::string getFieldString(const std::string& name, bool* bNil = nullptr);
    std::string getFieldString(int i, bool* bNil = nullptr);
    void setFieldvf(glm::vec4 v, int size);
    float getFieldFloat(const std::string& name, bool* bNil = nullptr);
    float getFieldFloat(int i, bool* bNil = nullptr);
    void pop(int n);
    void unpack();
    bool runFunc(int args, int rets);
    void newTable();

private:
    lua_State* L = nullptr;
    std::stack<std::string> _gs;
};
}

#endif /* CppShaderEngine_hpp */
