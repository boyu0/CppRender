//
//  CppVertexArray.hpp
//  CppRender
//
//  Created by yubo on 2020/10/16.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppVertexArray_hpp
#define CppVertexArray_hpp

#include <stdio.h>
#include <unordered_map>

namespace CppRender {
class Context;
class VertexArray{
public:
    VertexArray(Context* ctx):_ctx(ctx){}
private:
    struct VertexAttributePointerInfo{
        int size{};
        int type{};
        bool normalized{};
        int stride{};
        int pointer{};
        int buffer{};
    };

public:
    void vertexAttributePointer(int index, int size, int type, bool normalized, int stride, int pointer);
    void loadOne(int n);

private:
    std::unordered_map<int, VertexAttributePointerInfo> _vertexAttributePointerInfos;
    Context* _ctx{};
};
}

#endif /* CppVertexArray_hpp */
