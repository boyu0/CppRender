//
//  CppUtils.cpp
//  CppRender
//
//  Created by yubo on 2020/10/16.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppUtils.hpp"
#include "CppContext.hpp"
#include "CppLuaEngine.hpp"
extern "C"{
#include "lua.h"
}
#include "glm/gtc/type_ptr.hpp"

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

int Utils::getTypeSize(int type)
{
    switch (type)
    {
    case CR_FLOAT:
        return sizeof(float);
        break;
    default:
        return 0;
        break;
    }
}

bool Utils::isRight(const glm::vec2& a, const glm::vec2& b, const glm::vec2& p)
{
    glm::vec2 ab = b - a;
    glm::vec2 ap = p - a;
    return glm::cross(glm::vec3(ab.x, ab.y, 0), glm::vec3(ap.x, ap.y, 0)).z >= 0;
}

glm::vec3 Utils::getTrianglePos(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c, const glm::vec2& p)
{
    glm::vec3 s[2];
    for(int i = 2; i--;){
        s[i][0] = c[i] - a[i];
        s[i][1] = b[i] - a[i];
        s[i][2] = a[i] - p[i];
    }
    glm::vec3 u = glm::cross(s[0], s[1]);
    if(std::abs(u[2])>1e-2)
    {
        return glm::vec3(1-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
    }

    return glm::vec3(-1, 1, 1);
}
void Utils::setValue(Context* ctx, const std::string& env, const std::string& name, int size, int type, bool normalized, void* data)
{
    LuaEngine* engine = ctx->getLuaEngine();
    engine->getEnv(env);
    switch (type)
    {
    case CR_FLOAT:
    {
        if(size == 1)
        {
            engine->setFieldFloat(name.c_str(), ((float*)data)[0]);
        }else
        {
            engine->getFieldOrNewTable(name);
            float v[16];
            for(int i = 0; i < size; ++i)
            {
                v[i] = *((float*)data + i);
            }
            engine->setFieldv(v, size);
            engine->pop(1);
        }
        break;
    }
    case CR_INT:
    {
        if(size == 1)
        {
            engine->setFieldInt(name.c_str(), ((int*)data)[0]);
        }else
        {
            engine->getFieldOrNewTable(name);
            int v[16];
            for(int i = 0; i < size; ++i)
            {
                v[i] = *((int*)data + i);
                engine->setFieldv(v, size);
            }
            engine->pop(1);
        }
        break;
    }
    default:
        break;
    }
    engine->pop(1);
}

void Utils::getFieldv(lua_State* L, int index, float v[], int* size)
{
    int t = lua_type(L, index);
    if(t == LUA_TNUMBER){
        v[0] = lua_tonumber(L, index);
        if(size){ *size = 1; }
    }else if(t == LUA_TTABLE){
        int count = (int)lua_rawlen(L, index);
        for(int i = 0; i < count; ++i){
            lua_geti(L, index, i+1);
            v[i] = lua_tonumber(L, -1);
            lua_pop(L, 1);
        }
        if(size){ *size = count; }
    }else{
        CR_ASSERT(false, "");
    }
}

void Utils::pushArray(lua_State* L, float v[], int size)
{
    lua_newtable(L);
    for(int i = 0; i < size; ++i)
    {
        lua_pushnumber(L, v[i]);
        lua_seti(L, -2, i+1);
    }
}

void Utils::normalize(lua_State* L, int index)
{
    float v[3];
    getFieldv(L, index, v, nullptr);
    
    glm::vec3 m = glm::normalize(glm::make_vec3(v));
    pushArray(L, glm::value_ptr(m), 3);
}

void Utils::add(lua_State* L, int aIndex, int bIndex)
{
    float va[4] = {};
    int counta;
    float vb[4] = {};
    int countb;
    getFieldv(L, aIndex, va, &counta);
    getFieldv(L, bIndex, vb, &countb);
    
    glm::vec4 m = glm::make_vec4(va) + glm::make_vec4(vb);
    pushArray(L, glm::value_ptr(m), counta < countb ? counta : countb);
}

void Utils::sub(lua_State* L, int aIndex, int bIndex)
{
    float va[4] = {};
    int counta;
    float vb[4] = {};
    int countb;
    getFieldv(L, aIndex, va, &counta);
    getFieldv(L, bIndex, vb, &countb);
    
    glm::vec4 m = glm::make_vec4(va) - glm::make_vec4(vb);
    pushArray(L, glm::value_ptr(m), counta < countb ? counta : countb);
}

void Utils::dot(lua_State* L, int aIndex, int bIndex)
{
    float va[3] = {};
    int counta;
    float vb[3] = {};
    int countb;
    getFieldv(L, aIndex, va, &counta);
    getFieldv(L, bIndex, vb, &countb);
    
    float m = glm::dot(glm::make_vec3(va), glm::make_vec3(vb));
    lua_pushnumber(L, m);
}

void Utils::reflect(lua_State* L, int aIndex, int bIndex)
{
    float va[3] = {};
    int counta;
    float vb[3] = {};
    int countb;
    getFieldv(L, aIndex, va, &counta);
    getFieldv(L, bIndex, vb, &countb);
    
    glm::vec3 m = glm::reflect(glm::make_vec3(va), glm::make_vec3(vb));
    pushArray(L, glm::value_ptr(m), 3);
}

void Utils::matmul(lua_State *L, int aIndex, int bIndex) {
    float va[16];
    float vb[16];
    int counta;
    int countb;
    getFieldv(L, aIndex, va, &counta);
    getFieldv(L, bIndex, vb, &countb);
    
    if(counta == 16 && countb == 16)
    {
        glm::mat4 ma = glm::make_mat4(va);
        glm::mat4 mb = glm::make_mat4(vb);
        glm::mat4 mc = ma * mb;
        pushArray(L, glm::value_ptr(mc), 16);
    }else if(counta == 16 && countb == 4)
    {
        glm::mat4 ma = glm::make_mat4(va);
        glm::vec4 mb = glm::make_vec4(vb);
        glm::vec4 mc = ma * mb;
        pushArray(L, glm::value_ptr(mc), 4);
    }else if(counta == 1 && countb == 3)
    {
        glm::vec3 mc = glm::make_vec3(vb) * va[0];
        pushArray(L, glm::value_ptr(mc), 3);
    }else if(counta == 3 && countb == 1)
    {
        glm::vec3 mc = glm::make_vec3(va) * vb[0];
        pushArray(L, glm::value_ptr(mc), 3);
    }else if(counta == 1 && countb == 4)
    {
        glm::vec4 mc = glm::make_vec4(vb) * va[0];
        pushArray(L, glm::value_ptr(mc), 4);
    }else if(counta == 4 && countb == 1)
    {
        glm::vec4 mc = glm::make_vec4(va) * vb[0];
        pushArray(L, glm::value_ptr(mc), 4);
    }else if(counta == 3 && countb == 3)
    {
        glm::vec3 mc = glm::make_vec3(va) * glm::make_vec3(vb);
        pushArray(L, glm::value_ptr(mc), 3);
    }else{
        CR_ASSERT(false, "");
    }
}


}
