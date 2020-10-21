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
    bool run(const std::string& env, const std::string& file);
    void newEnv(const std::string& name);
    void deleteEnv(const std::string& name);
    void getEnv(const std::string& name);
    bool isNil();
    int getTop();

    void getGlobal(const std::string& name);
    void setGlobal(const std::string& name);
    void getField(int i);
    void getField(const std::string& name, int index = -1);
    void setField(const std::string& name, int index = -2);
    int getLen();
    std::string getFieldString(const std::string& name, int index = -1, bool* bNil = nullptr);
    std::string getFieldString(int i, bool* bNil = nullptr);
    void setFieldvf(glm::vec4 v, int size);
    float getFieldFloat(const std::string& name, bool* bNil = nullptr);
    float getFieldFloat(int i, bool* bNil = nullptr);
    void pop(int n);
    void unpack();
    void walk(std::function<void()> func);
    bool runFunc(const std::string& env, int args, int rets);
    void newTable();
    std::string toString(int index = -1);
    float toFloat(int index = -1);
    int type(int index = -1);

private:
    lua_State* L = nullptr;
};
}

#endif /* CppShaderEngine_hpp */
