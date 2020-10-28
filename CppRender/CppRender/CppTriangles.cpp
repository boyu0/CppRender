//
//  CppTriangles.cpp
//  CppRender
//
//  Created by yubo on 2020/10/19.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppTriangles.hpp"
#include "CppContext.hpp"
#include "glm/glm.hpp"
#include "CppProgram.hpp"
#include <cmath>

namespace CppRender{
Triangles::Triangles(Context* ctx)
:Primitive(ctx, CR_TRIANGLES, 3)
{
}

glm::vec4 projectionVec4(const glm::mat4x4& projection, float pos[4])
{
    auto vpos = glm::vec4(pos[0], pos[1], pos[2], pos[3]);
    vpos = projection * vpos;
    vpos[0] /= vpos[3];
    vpos[1] /= vpos[3];
    vpos[2] /= vpos[3];
    vpos[3] = 1;
    return vpos;
}

void Triangles::rasterOne(Program* program, int index[3])
{
    auto& proj = _ctx->getProjection();
    int frameBufferIndex = _ctx->get(CR_FRAME_BUFFER);
    int size[2];
    _ctx->getFrameBufferSize(frameBufferIndex, size);
    glm::vec4 p[3] = {
        projectionVec4(proj, _vetexValues[index[0]].pos),
        projectionVec4(proj, _vetexValues[index[1]].pos),
        projectionVec4(proj, _vetexValues[index[2]].pos),
    };

    // 包围盒
    float left = std::min(std::min(p[0].x, p[1].x), p[2].x);
    float right = std::max(std::max(p[0].x, p[1].x), p[2].x);
    float bottom = std::min(std::min(p[0].y , p[1].y), p[2].y);
    float top = std::max(std::max(p[0].y, p[1].y), p[2].y);
    float near = std::min(std::min(p[0].z, p[1].z), p[2].z);
    float far = std::max(std::max(p[0].z, p[1].z), p[2].z);

    float perx = 2.0f/size[0];
    float perxh = perx/2.0f;
    float pery = 2.0f/size[1];
    float peryh = pery/2.0f;

    float startx = left - std::fmod(left, perx) + perxh;
    startx = std::max(startx, -1.0f+perxh);
    int istartx = (int)CR_FLOAT_FIX(((1.0f + startx) / 2.0f)*size[0]);

    float endx = right - std::fmod(right, perx) + perxh + perx;
    endx = std::min(endx, 1.0f-perxh);
    int iendx = (int)CR_FLOAT_FIX(((1.0f + endx) / 2.0f)*size[0]);

    float starty = bottom - std::fmod(bottom, pery) + peryh;
    starty = std::max(starty, -1.0f+peryh);
    int istarty = (int)CR_FLOAT_FIX(((1.0f + starty) / 2.0f)*size[1]);

    float endy = top - std::fmod(top, pery) + peryh + pery;
    endy = std::min(endy, 1.0f-peryh);
    int iendy = (int)CR_FLOAT_FIX(((1.0f + endy) / 2.0f)*size[1]);

    int iy = istarty;
    float y = starty;
    float color[4];
    unsigned char* buffer = (unsigned char*)_ctx->mapBuffer(CR_RENDER_BUFFER);
    for(; iy <= iendy; y+=pery, ++iy)
    {
        int ix = istartx;
        float x = startx;
        for(; ix <= iendx; x+=perx, ++ix)
        {
            glm::vec2 pp(x, y);
            if(Utils::isRight(p[0], p[1], pp) && Utils::isRight(p[1], p[2], pp) && Utils::isRight(p[2], p[0], pp))
            {
                glm::vec3 tpos = Utils::getTrianglePos(p[0], p[1], p[2], pp);
                float ftpos[3] = {tpos[0], tpos[1], tpos[2]};
                program->runFragment(3, index, ftpos, color);
                buffer[(iy * size[0] + ix) * 4] = (unsigned char)(color[0] * 255);
                buffer[(iy * size[0] + ix) * 4 + 1] = (unsigned char)(color[1] * 255);
                buffer[(iy * size[0] + ix) * 4 + 2] = (unsigned char)(color[2] * 255);
                buffer[(iy * size[0] + ix) * 4 + 3] = (unsigned char)(color[3] * 255);
            }
        }
    }
}

void Triangles::raster(Program* program, int start, int count)
{
    int ea = _ctx->get(CR_INVALID_VALUE);
    if(ea <= 0)
    {
        for(int i = 0; i < _vetexValues.size() - 2; i += 3)
        {
            int index[3] = {i, i+1, i+2};
            rasterOne(program, index);
        }
    }else{
        int size;
        int* ebuffer = (int*)_ctx->mapBufferIndex(ea, &size);
        size = size / sizeof(int);
        for(int i = 0; i < size - 2; i += 3)
        {
            int index[3] = {ebuffer[i], ebuffer[i+1], ebuffer[i+2]};
            rasterOne(program, index);
        }
    }
}

}
