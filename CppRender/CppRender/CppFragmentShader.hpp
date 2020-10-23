//
//  CppFragmentShader.hpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppFragmentShader_hpp
#define CppFragmentShader_hpp

#include <stdio.h>
#include "CppShader.hpp"

namespace CppRender{
class FragmentShader : public Shader{
public:
    virtual ~FragmentShader() = default;

public:
    virtual bool init(Context* ctx, const std::string& file) override;
    void dealResult();
    void setVerying(const std::string& name, int count, float f[]);
    void getResult(float color[4]);
};
}

#endif /* CppFragmentShader_hpp */
