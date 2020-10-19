//
//  CppPrimitive.hpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppPrimitive_hpp
#define CppPrimitive_hpp

#include <stdio.h>
#include "CppUtils.hpp"

namespace CppRender{
class Primitive{
public:
    Primitive()=default;
    virtual ~Primitive()=0;

public:
    inline void setImmediateMode(bool b) { _immediateMode = b; }

protected:
    int _type{CR_INVALID_VALUE};
    bool _immediateMode{false};
};
}


#endif /* CppPrimitive_hpp */
