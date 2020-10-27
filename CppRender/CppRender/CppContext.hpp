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
#include <string>
#include "CppDefine.h"
#include "glm/matrix.hpp"

namespace CppRender{
class VertexArray;
class FrameBuffer;
class RenderBuffer;
class Buffer;
class Texture;
class Draw;
class Shader;
class Program;
class LuaEngine;
class Window;
class Context{
public:
    Context();
    ~Context();
    
    bool init(int width, int height);
    
    void genFrameBuffers(int n, int* ids);
    void bindFrameBuffer(int target, int id);
    void frameBufferTexture2D(int target, int attachment, int textarget, int texture, int level);
    void getFrameBufferSize(int target, int size[2]);
    int getFrameBufferTexture2D(int target);
    
    void genRenderbuffers(int n, int* ids);
    void bindRenderBuffer(int target, int id);
    void renderbufferStorage(int target, int id);

    void genBuffers(int n, int* ids);
    void bindBuffer(int target, int id);
    void bufferData(int target, int size, void* data, int useage);
    void* mapBuffer(int target);
    void* mapBufferIndex(int index, int* size = nullptr);
    void deleteBuffers(int n, int* ids);
    
    void genTextures(int n, int* ids);
    void bindTexture(int target, int id);
    void texImage2D(int target, int level, int internalformat, int width, int height, void* data);
    void getTextureSize(int target, int size[2]);

    void genVertexArrays(int n, int* ids);
    void bindVertexArray(int id);
    void vertexAttributePointer(int index, int size, int type, bool normalized, int stride, int pointer);
    void vertexArrayLoadOne(int n);
    
    int createShader(int type, const std::string& file);
    int createProgram();
    void attachShader(int program, int shader);
    bool linkProgram(int program);
    void useProgram(int program);
    void runProgram(int mode, int start, int count);
    void setProgramAttribute(int index, int size, int type, bool normalized, void* data);
    void setProgramUniform(const std::string& name, int i);

    void viewPort(int x, int y, int width, int height);
    void clearColor(float r, float g, float b, float a);
    void clear(int mask);
    void drawArrays(int mode, int start, int count);

    Texture* getTexture(int id);
    inline float* getClearColor() { return _clearColor; }
    
    void getRenderData(void** data);
    
    void begin(int mode);
    void end();
    void vertexf(float x, float y, float z, float w);
    void colorf(float r, float g, float b, float w);
    void uvf(float u, float v);
    int get(int target);
    void ortho(float left, float right, float bottom, float top, float near, float far);
    inline const glm::mat4& getProjection() { return _projection; }
    void getIntegerv(int target, int out[]);

    inline LuaEngine* getLuaEngine() { return _luaEngine; }

private:
    std::unordered_map<int, VertexArray*> _vertexArrays;
    std::unordered_map<int, FrameBuffer*> _frameBuffers;
    std::unordered_map<int, RenderBuffer*> _renderBuffers;
    std::unordered_map<int, Buffer*> _buffers;
    std::unordered_map<int, Texture*> _textures;
    std::unordered_map<int, Shader*> _shaders;
    std::unordered_map<int, Program*> _programs;

    int _currentFrameBufferIndex = CR_INVALID_VALUE;
    int _currentRenderBufferIndex = CR_INVALID_VALUE;
    int _currentTextureIndex = CR_INVALID_VALUE;
    int _currentVertexArrayIndex = CR_INVALID_VALUE;
    int _currentArrayBufferIndex = CR_INVALID_VALUE;
    int _currentElementArrayBufferIndex = CR_INVALID_VALUE;
    int _currentProgramIndex = CR_INVALID_VALUE;
    int _frameBufferIndex = 0;
    int _renderBufferIndex = 0;
    int _bufferIndex = 0;
    int _textureIndex = 0;
    int _vertexArrayIndex = 0;
    int _shaderIndex = 1;
    int _programIndex = 1;
    float _clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    Draw* _draw{};
    LuaEngine* _luaEngine{};
    glm::mat4 _projection;

    Window* _window{};
};
}

#endif /* CppContext_hpp */
