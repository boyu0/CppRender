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
#include <string>
#include "CppDefine.h"
#include "glm/glm.hpp"

#define CR_CHECK_RETURN(cond) if(!(cond)) { return; }
#define CR_CHECK_RETURN_RET(cond, ret) if(!(cond)) { return ret; }
#define CR_CHECK_RETURN_FALSE(cond) CR_CHECK_RETURN_RET(cond, false)
#define CR_ASSERT(cond, msg) assert(cond)
#define CR_LOG(...) printf(__VA_ARGS__)
#define CR_LOGE(format, ...) CR_LOG("CPPRENDER ERROR:"#format, __VA_ARGS__)

#define CR_GEN_ARRAYS(ctx, TType, Map, Index, N, Ids) \
    for (int i = 0; i < N; ++i) { \
        TType* type = new TType(ctx); \
        Map.emplace(std::make_pair(Index, type)); \
        Ids[i] = Index++; \
    }

#define CR_DELETE_ARRAYS(ctx, Map, N, Ids) \
    for(int i = 0; i < N; ++i){ \
        if(Map.find(Ids[i]) != Map.end()){ \
            delete Map[Ids[i]]; \
            Map.erase(Ids[i]); \
        }\
    }

#define CR_FLOAT_FIX(f) std::floor((f) + 0.00001)

#define CR_MAP_FIND_RETURN(Map, Id) if(Map.find(Id) != Map.end()){return Map[Id];}else{return nullptr;}

struct lua_State;
namespace CppRender{
class Context;
class Utils
{
public:
    static int getFormatPerSize(int format);
    static int getTypeSize(int type);
    static bool isRight(const glm::vec2& a, const glm::vec2& b, const glm::vec2& p);
    static glm::vec3 getTrianglePos(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c, const glm::vec2& p);
    static void setValue(Context* ctx, const std::string& env, const std::string& name, int size, int type, bool normalized, void* data);
    static void getFieldv(lua_State* L, int index, float v[], int* size);
    static void pushArray(lua_State* L, float v[], int size);
    static void matmul(lua_State* L, int aIndex, int bIndex);
    static void normalize(lua_State* L, int index);
    static void add(lua_State* L, int aIndex, int bIndex);
    static void sub(lua_State* L, int aIndex, int bIndex);
    static void dot(lua_State* L, int aIndex, int bIndex);
    static void reflect(lua_State* L, int aIndex, int bIndex);
};
}

#endif /* CppUtils_hpp */
