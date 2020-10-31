//
//  CppBuffer.cpp
//  CppRender
//
//  Created by yubo on 2020/10/15.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppBuffer.hpp"
#include <memory>

namespace CppRender{

void Buffer::data(int size, void* data, int useage)
{
    _data = malloc(size);
    _size = size;
    if(data != nullptr)
    {
        memcpy(_data, data, size);
    }
}

Buffer::~Buffer()
{
    if(_data != nullptr)
    {
        delete _data;
    }
}

}
