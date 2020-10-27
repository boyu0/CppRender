//
//  CppDraw.cpp
//  CppRender
//
//  Created by yubo on 2020/10/17.
//  Copyright © 2020 test. All rights reserved.
//

#include "CppDraw.hpp"
#include "CppTriangles.hpp"
#include "CppUtils.hpp"
#include "CppContext.hpp"

namespace CppRender{

Draw::Draw(Context* ctx)
{
    _ctx = ctx;
}

void Draw::begin(int mode)
{
    _currentMode = mode;
}

void Draw::end()
{
    if(_vertexes.size() > 0)
    {
        int buf = CR_INVALID_VALUE;
        _ctx->genBuffers(1, &buf);
        _ctx->bindBuffer(CR_ARRAY_BUFFER, buf);
        _ctx->bufferData(CR_ARRAY_BUFFER, _vertexes.size()*sizeof(VertexInfo), &_vertexes[0], CR_DYNAMIC_DRAW);
        _ctx->vertexAttributePointer(0, 4, CR_FLOAT, false, sizeof(VertexInfo), 0);
        _ctx->vertexAttributePointer(1, 4, CR_FLOAT, false, sizeof(VertexInfo), 4*sizeof(float));
        _ctx->vertexAttributePointer(2, 2, CR_FLOAT, false, sizeof(VertexInfo), 8*sizeof(float));
        _ctx->bindBuffer(CR_ARRAY_BUFFER, 0);
        _ctx->setProgramUniform("texture", _ctx->get(CR_TEXTURE_2D));
        _ctx->drawArrays(_currentMode, 0, _vertexes.size());
        _ctx->deleteBuffers(1, &buf);

        _vertexes.clear();
    }
}

void Draw::vertexf(float x, float y, float z, float w)
{
    _vertexes.emplace_back(VertexInfo{
        {x, y, z, w},
        {_currentColor[0], _currentColor[1], _currentColor[2], _currentColor[3]},
        {_currentUV[0], _currentUV[1]},
    });
}

void Draw::uvf(float u, float v)
{
    _currentUV[0] = u;
    _currentUV[1] = v;
}

void Draw::colorf(float r, float g, float b, float a)
{
    _currentColor[0] = r;
    _currentColor[1] = g;
    _currentColor[2] = b;
    _currentColor[3] = a;
}

}
