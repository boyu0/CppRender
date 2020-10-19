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

namespace CppRender{
class Context;
class Shader{
public:
    virtual ~Shader() = 0;

    bool init(Context* ctx, const std::string& file);
};
}

#endif /* CppShader_hpp */
