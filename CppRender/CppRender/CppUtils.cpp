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
        return glm::vec3(1-(u.x+u.y)/u.z, u.x/u.z, u.y/u.z);
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
            float v[4];
            for(int i = 0; i < size; ++i)
            {
                v[i] = *((float*)data + i);
                engine->setFieldv(v, size);
            }
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
            int v[4];
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

}
