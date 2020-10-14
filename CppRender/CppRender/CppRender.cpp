//
//  CppRender.cpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#include <iostream>
#include "CppRender.hpp"
#include "CppContext.hpp"

CppContext* context = nullptr;

bool CppRender::init()
{
    context = new CppContext();
    if(context != nullptr ||  !context->init()){
        
        return false;
    }
}

void CppRender::genFrameBuffers(int n, int* ids)
{
};

