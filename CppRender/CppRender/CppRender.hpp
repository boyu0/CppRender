//
//  CppRender.hpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppRender_
#define CppRender_

/* The classes below are exported */
#pragma GCC visibility push(default)

class CppRender
{
    public:
    static bool init();
    static void genFrameBuffers(int n, int* ids);
};

#pragma GCC visibility pop
#endif
