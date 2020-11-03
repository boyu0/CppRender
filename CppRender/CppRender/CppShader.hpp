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
#include <vector>
#include "CppDefine.h"

namespace CppRender{
class Context;
class Shader{
public:
    Shader(int type):_type(type){}
public:
    inline int getType() { return _type; }
    virtual bool init(Context* ctx, const std::string& file);
    inline std::string& getEnv() { return _env; }

protected:
    Context* _ctx{};
    int _type = CR_INVALID_VALUE;
    std::string _env;
};
}

#endif /* CppShader_hpp */
