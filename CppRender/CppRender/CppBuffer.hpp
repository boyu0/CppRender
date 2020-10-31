//
//  CppBuffer.hpp
//  CppRender
//
//  Created by yubo on 2020/10/15.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppBuffer_hpp
#define CppBuffer_hpp

#include <stdio.h>

namespace CppRender{
class Context;
class Buffer{
public:
    Buffer(Context* ctx):_ctx(ctx){}
    ~Buffer();

public:
    void data(int size, void* data, int useage);
    void* get() { return _data; }
    int size() { return _size; }

private:
    Context* _ctx{};
    void* _data{};
    int _size{};
};
}
#endif /* CppBuffer_hpp */
