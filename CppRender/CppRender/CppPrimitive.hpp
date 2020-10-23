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
#include <vector>
#include <string>

namespace CppRender{
class Context;
class Program;
class Primitive{
protected:
    struct VertexValue{
        float pos[4];
    };
    struct VertexAttr{
        int count;
        float f[4];
    };
public:
    Primitive(Context* ctx, int type, int count):_ctx(ctx), _type(type), _count(count){}
    virtual ~Primitive() = 0;

    void newVertex(float pos[4]);
    void pushVertexAttrf(int count, float f[]);
    float* getVertexAttrf(int index, int name, int* count);
    virtual void raster(Program* program) = 0;

public:
    inline void setImmediateMode(bool b) { _immediateMode = b; }

protected:
    int _type{CR_INVALID_VALUE};
    int _count{};
    bool _immediateMode{false};
    std::vector<VertexValue> _vetexValues;
    std::vector<std::vector<VertexAttr>> _vertexAttrs;
    Context* _ctx{};
};
}


#endif /* CppPrimitive_hpp */
