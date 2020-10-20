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
#include <vector>

namespace CppRender{
class VertexShader : public Shader{
public:
    virtual ~VertexShader() = default;

public:
    virtual bool init(Context* ctx, const std::string& file);
    void setAttribute(int n, int index, int size, int type, bool normalized, void* data);

private:
    void initLayouts();

private:
    std::vector<std::string> _layouts;
};
}

#endif /* CppVertexShader_hpp */
