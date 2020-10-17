//
//  CppVertexShader.hpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppVertexShader_hpp
#define CppVertexShader_hpp

#include <stdio.h>
#include "CppShader.hpp"

namespace CppRender{
class VertexShader : public Shader{
public:
    virtual ~VertexShader() = default;
};
}

#endif /* CppVertexShader_hpp */
