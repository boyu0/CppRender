//
//  CppShader.hpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppShader_hpp
#define CppShader_hpp

#include <stdio.h>
#include <string>
#include "CppDefine.h"

namespace CppRender{
class Context;
class LuaEngine;
class Shader{
public:
    virtual ~Shader() = 0;

    inline int getType() { return _type; }
    virtual bool init(Context* ctx, const std::string& file);
    bool runOne();

protected:
    bool unpackTableToEnv(const std::string& name);

protected:
    LuaEngine* _engine = nullptr;
    int _type = CR_INVALID_VALUE;
    std::string _identifier;
};
}

#endif /* CppShader_hpp */
