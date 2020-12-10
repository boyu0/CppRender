//
//  CaseBoxView.m
//  CppApp
//
//  Created by yubo on 2020/12/9.
//  Copyright © 2020 test. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CaseBoxView.h"
#include "../../CppRender/CppRender/CppRender.hpp"
#include "../../CppRender/include/stb_image.h"
#include "../../CppRender/include/glm/glm.hpp"
#include "../../CppRender/include/glm/ext.hpp"

using namespace CppRender;
@implementation CaseBoxView{
}

static int buffers[2];
static int vao;
-(void) prepareRender{
    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
    };
    
    Render::enable(CR_DEPTH_BUFFER);

    Render::perspective(glm::radians(45.0f), self.winW, self.winH, 0.1f, 100.0f);

    Render::genVertexArrays(1, &vao);
    Render::bindVertexArray(vao);
    Render::genBuffers(2, buffers);
    Render::bindBuffer(CR_ARRAY_BUFFER, buffers[0]);
    Render::bufferData(CR_ARRAY_BUFFER, sizeof(vertices), vertices, CR_STATIC_DRAW);
    
    Render::vertexAttributePointer("aPos", 3, CR_FLOAT, false, 8 * sizeof(float), 0);
    Render::vertexAttributePointer("aNormal", 3, CR_FLOAT, false, 8 * sizeof(float), 3*sizeof(float));
    Render::vertexAttributePointer("aUV", 2, CR_FLOAT, false, 8 * sizeof(float), 6*sizeof(float));
    
    int texture;
    Render::genTextures(1, &texture);
    Render::bindTexture(texture);
    int width, height;
    unsigned char* data = stbi_load([self getPath:"res/png/container.jpg"].c_str(), &width, &height, nullptr, 4);
    Render::texImage2D(CR_TEXTURE_2D, 0, CR_RGBA8, width, height, data);
    
    
    int crvert = Render::createShader(CR_VERTEX_SHADER, [self getPath:"res/shader/testVert.lua"]);
    int crfrag = Render::createShader(CR_FRAGMENT_SHADER, [self getPath:"res/shader/testFrag.lua"]);
    int crprogram = Render::createProgram();
    Render::attachShader(crprogram, crvert);
    Render::attachShader(crprogram, crfrag);
    Render::linkProgram(crprogram);
    Render::useProgram(crprogram);
    Render::setProgramUniform("texture", texture);
    
    glm::mat4 view = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -3.0f));
    Render::setProgramUniform("view", glm::value_ptr(view), 16);
    glm::mat4 projection = glm::perspective(45.0f, (float)self.winW/(float)self.winH, 0.1f, 100.0f);
    Render::setProgramUniform("projection", glm::value_ptr(projection), 16);
    
    Render::bindVertexArray(0);
}

-(void) drawRender{
    Render::clear(CR_COLOR_BUFFER_BIT | CR_DEPTH_BUFFER_BIT);
    glm::mat4 model = glm::rotate(glm::mat4(1.0), 50.0f * self.time * 0.02f, glm::vec3(0.5f, 1.0f, 0.0f));
    Render::setProgramUniform("model", glm::value_ptr(model), 16);
    Render::bindVertexArray(vao);
    Render::drawArrays(CR_TRIANGLES, 0, 36);
}

@end
