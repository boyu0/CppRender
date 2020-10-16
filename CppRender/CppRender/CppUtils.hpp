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
#include <assert.h>
#include "CppDefine.h"

#define CPPRENDER_CHECK_RETURN(cond) if(!(cond)) { return; }
#define CPPRENDER_CHECK_RETURN_RET(cond, ret) if(!(cond)) { return ret; }
#define CPPRENDER_CHECK_RETURN_FALSE(cond) CPPRENDER_CHECK_RETURN_RET(cond, false)
#define CPPRENDER_ASSERT(cond, msg) assert(cond)

#define CPPRENDER_GEN_BUFFER(TBuffer, Map, Index, N, Ids) \
    for (int i = 0; i < N; ++i) { \
        TBuffer* buffer = new TBuffer(); \
        Map.emplace(std::make_pair(Index, buffer)); \
        Ids[i] = Index++; \
    }

#define CPPRENDER_MAP_FIND_RETURN(Map, Id) if(Map.find(Id) != Map.end()){return Map[Id];}else{return nullptr;}

namespace CppRender{
class Utils
{
public:
    static int getFormatPerSize(int format);
};
}

#endif /* CppUtils_hpp */
