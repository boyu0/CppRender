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
};
}

#endif /* CppFragmentShader_hpp */
