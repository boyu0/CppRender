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
#include <string>

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
    void vertexAttributePointer(const std::string& name, int size, int type, bool normalized, int stride, int pointer);
    void loadOne(int n);

private:
    std::unordered_map<std::string, VertexAttributePointerInfo> _vertexAttributePointerInfos;
    Context* _ctx{};
};
}

#endif /* CppVertexArray_hpp */
