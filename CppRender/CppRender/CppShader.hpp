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
    virtual ~Shader() = 0;

    inline int getType() { return _type; }
    virtual bool init(Context* ctx, const std::string& file);
    bool runOne();
    inline std::string& getEnv() { return _env; }

protected:
    bool unpackTableToEnv(const std::string& name);
    void initVariables(const std::string& name, std::vector<std::string>& target);

protected:
    Context* _ctx{};
    int _type = CR_INVALID_VALUE;
    std::string _env;
};
}

#endif /* CppShader_hpp */
