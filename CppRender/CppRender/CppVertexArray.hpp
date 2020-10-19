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
class VertexArray{
private:
    struct VertexAttributePointerInfo{
        int size{};
        int type{};
        bool normalized{};
        int stride{};
        int pointer{};
    };

public:
    void vertexAttributePointer(int index, int size, int type, bool normalized, int stride, int pointer);

private:
    std::unordered_map<int, VertexAttributePointerInfo> _vertexAttributePointerInfos;
};
}

#endif /* CppVertexArray_hpp */
