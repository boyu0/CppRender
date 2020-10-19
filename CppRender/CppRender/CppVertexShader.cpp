//
//  CppVertexShader.cpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppVertexShader.hpp"
#include "CppUtils.hpp"

namespace CppRender{
bool VertexShader::init(Context* ctx, const std::string& file)
{
    if(!Shader::init(ctx, file)){
        return false;
    }

    _type = CR_VERTEX_SHADER;
    unpackTableToGlobal(CR_SHADER_ATTRIBUTE);
    unpackTableToGlobal(CR_SHADER_VERYING);
    unpackTableToGlobal(CR_SHADER_UNIFORM);
    
    return true;
}


}
