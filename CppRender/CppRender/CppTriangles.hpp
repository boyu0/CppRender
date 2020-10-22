//
//  CppTriangles.hpp
//  CppRender
//
//  Created by yubo on 2020/10/19.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppTriangles_hpp
#define CppTriangles_hpp

#include <stdio.h>
#include "CppPrimitive.hpp"
namespace CppRender{
class Context;
class Triangles : public Primitive{
public:
    Triangles(Context* ctx);
    virtual ~Triangles()=default;
};
}
#endif /* CppTriangles_hpp */
