//
//  GLDraw.cpp
//  CppApp
//
//  Created by yubo on 2020/12/9.
//  Copyright © 2020 test. All rights reserved.
//

#include "GLDraw.hpp"
#include <OpenGL/gl.h>
#include <string>
#include <iostream>


std::string vShader =
"attribute vec3 aPos; \
attribute vec3 aColor; \
attribute vec2 aTexCoord; \
varying vec3 ourColor; \
varying vec2 TexCoord; \
void main() \
{ \
    gl_Position = vec4(aPos, 1.0); \
    ourColor = aColor; \
    TexCoord = aTexCoord; \
}";

std::string fShader =
"varying vec3 ourColor; \
varying vec2 TexCoord; \
uniform sampler2D ourTexture; \
void main() \
{ \
    gl_FragColor = texture2D(ourTexture, TexCoord); \
}";



int createProgram(GLuint vertex, GLuint fragment)
{
    int success;
    GLuint ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return -1;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    return ID;
}

GLuint compileShader(const std::string& code, GLenum type)
{
    GLuint vertex = glCreateShader(type);
    int success;
    
    const char* scode = code.c_str();
    glShaderSource(vertex, 1, &scode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    };
    
    return vertex;
}


void GLDraw::prepare()
{
    float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    glGenVertexArraysAPPLE(1, &VAO);
    glBindVertexArrayAPPLE(VAO);
    
    int vert = compileShader(vShader, GL_VERTEX_SHADER);
    int frag = compileShader(fShader, GL_FRAGMENT_SHADER);
    program = createProgram(vert, frag);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    int pos;
    
    
    pos = glGetAttribLocation(program, "aPos");
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
    glEnableVertexAttribArray(pos);
    pos = glGetAttribLocation(program, "aColor");
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(pos);
    pos = glGetAttribLocation(program, "aTexCoord");
    glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
    glEnableVertexAttribArray(pos);
    
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArrayAPPLE(0);
}

void GLDraw::draw(int width, int height, void* data)
{
    if(texture == 0)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glBindVertexArrayAPPLE(VAO);
    glUseProgram(program);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glSwapAPPLE();
}
