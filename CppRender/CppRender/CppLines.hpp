//
//  CppLines.hpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppLines_hpp
#define CppLines_hpp

#include <stdio.h>
#include "CppPrimitive.hpp"

namespace CppRender{
class Lines : public Primitive{
public:
    Lines(Context* ctx);
    virtual ~Lines();
};
}

#endif /* CppLines_hpp */
