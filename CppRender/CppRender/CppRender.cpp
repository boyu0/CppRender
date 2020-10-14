//
//  CppRender.cpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#include <iostream>
#include "CppRender.hpp"
#include "CppRenderPriv.hpp"

void CppRender::HelloWorld(const char * s)
{
    CppRenderPriv *theObj = new CppRenderPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void CppRenderPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

