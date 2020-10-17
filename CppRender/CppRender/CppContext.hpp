//
//  CppContext.hpp
//  CppRender
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppContext_hpp
#define CppContext_hpp

#include <stdio.h>
#include <unordered_map>
#include "CppDefine.h"
#include "glm/vec4.hpp"

namespace CppRender{
class VertexArray;
class FrameBuffer;
class RenderBuffer;
class Buffer;
class Texture;
class Draw;
class Shader;
class Program;
class Context{
public:
    Context();
    ~Context();
    
    bool init(int width, int height);
    
    void genFrameBuffers(int n, int* ids);
    void bindFrameBuffer(int target, int id);
    void frameBufferTexture2D(int target, int attachment, int textarget, int texture, int level);
    
    void genRenderbuffers(int n, int* ids);
    void bindRenderBuffer(int target, int id);
    void renderbufferStorage(int target, int id);
    
    void genTextures(int n, int* ids);
    void bindTexture(int target, int id);
    void texImage2D(int target, int level, int internalformat, int width, int height, void* data);
    
    int createShader(int type);
    int createProgram();
    
    void clearColor(float r, float g, float b, float a);
    void clear(int mask);

    Texture* getTexture(int id);
    inline glm::vec4 getClearColor() { return _color; }
    
    void getRenderData(void** data);
    
    void begin(int mode);
    void end();
    void vertex3f(float x, float y, float z);
    void color3f(float r, float g, float b);

private:
    std::unordered_map<int, VertexArray*> _vetexArrays;
    std::unordered_map<int, FrameBuffer*> _frameBuffers;
    std::unordered_map<int, RenderBuffer*> _renderBuffers;
    std::unordered_map<int, Buffer*> _buffers;
    std::unordered_map<int, Texture*> _textures;
    std::unordered_map<int, Shader*> _shaders;
    std::unordered_map<int, Program*> _programs;
    
    int _currentFrameBufferIndex = CPPRENDER_INVALID_VALUE;
    int _currentRenderBufferIndex = CPPRENDER_INVALID_VALUE;
    int _currentTextureIndex = CPPRENDER_INVALID_VALUE;
    int _frameBufferIndex = 0;
    int _renderBufferIndex = 0;
    int _textureIndex = 0;
    int _shaderIndex = 0;
    int programIndex = 0;
    glm::vec4 _color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    Draw* _draw{};
};
}

#endif /* CppContext_hpp */
