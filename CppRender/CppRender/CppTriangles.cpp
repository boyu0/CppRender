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

    float perx = 1.0f/size[0];
    float perxh = perx/2.0f;
    float pery = 1.0f/size[1];
    float peryh = pery/2.0f;

    float startx = left - std::fmod(left, perx) + perxh;
    startx = std::max(startx, perxh);
    int istartx = (int)CR_FLOAT_FIX(startx);

    float endx = right - std::fmod(right, perx) + perxh + 1;
    endx = std::min(endx, 1.0f-perxh);
    int iendx = (int)CR_FLOAT_FIX(endx);

    float starty = bottom - std::fmod(bottom, pery) + peryh;
    starty = std::max(starty, peryh);
    int istarty = (int)CR_FLOAT_FIX(starty);

    float endy = top - std::fmod(top, pery) + peryh + 1;
    endy = std::min(endy, 1.0f-peryh);
    int iendy = (int)CR_FLOAT_FIX(endy);

    int iy = istarty;
    float color[4];
    char* buffer = (char*)_ctx->mapBuffer(CR_FRAME_BUFFER);
    for(float y = starty; y <= endy; y+=pery, ++iy)
    {
        int ix = istartx;
        for(float x = startx; x <= endx; x+=perx, ++ix)
        {
            program->runFragment(x, y, color);
            buffer[(iy * size[0] + ix) * 4] = (char)(color[0] * 255);
            buffer[(iy * size[0] + ix) * 4 + 1] = (char)(color[1] * 255);
            buffer[(iy * size[0] + ix) * 4 + 2] = (char)(color[2] * 255);
            buffer[(iy * size[0] + ix) * 4 + 3] = (char)(color[3] * 255);
        }
    }
}

void Triangles::raster(Program* program)
{
    for(int i = 0; i < _vetexValues.size() - 2; i += 3)
    {
        int index[3] = {i, i+1, i+2};
        rasterOne(program, index);
    }
}

}
