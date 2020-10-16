//
//  CppUtils.cpp
//  CppRender
//
//  Created by yubo on 2020/10/16.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppUtils.hpp"

namespace CppRender{
int Utils::getFormatPerSize(int format)
{
    switch (format)
    {
    case CPPRENDER_RGB8:
        return 3;
    case CPPRENDER_RGBA8:
        return 4;
    default:
        CPPRENDER_ASSERT(false, "");
        return 0;
        break;
    }
}
}