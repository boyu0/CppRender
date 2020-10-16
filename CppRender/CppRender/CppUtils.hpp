//
//  CppUtils.hpp
//  CppRender
//
//  Created by yubo on 2020/10/16.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppUtils_hpp
#define CppUtils_hpp

#include <stdio.h>

#define CPPRENDER_CHECK_RETURN(cond) if(!(cond)) { return; }
#define CPPRENDER_CHECK_RETURN_RET(cond, ret) if(!(cond)) { return ret; }
#define CPPRENDER_CHECK_RETURN_FALSE(cond) CPPRENDER_CHECK_RETURN_RET(cond, false)

#endif /* CppUtils_hpp */
