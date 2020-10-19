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
    case CR_RGB8:
        return 3;
    case CR_RGBA8:
        return 4;
    default:
        CR_ASSERT(false, "");
        return 0;
        break;
    }
}
}
