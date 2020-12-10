//
//  CaseModelView.m
//  CppApp
//
//  Created by yubo on 2020/12/10.
//  Copyright © 2020 test. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CaseModelView.h"
#include "../../CppRender/CppRender/CppRender.hpp"
#include "../../CppRender/include/stb_image.h"
#include "../../CppRender/include/glm/glm.hpp"
#include "../../CppRender/include/glm/ext.hpp"
#include <iostream>
#include "Model.hpp"
#include "Camera.h"

using namespace CppRender;
@implementation CaseModelView{
    Model _model;
    Camera* _camera;

    int _diffuse;
    int _ao;
    int _specular;
    int _normal;
    int _roughness;
    int _shader;
}

static int buffers[2];
static int vao;

int loadTexture(const std::string& path)
{
    int width, height, nrComponents;
    int tid = 0;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 4);
    if (data)
    {
//        int format;
//        if (nrComponents == 1)
//            format = CR_RGBA8;
//        else if (nrComponents == 3)
//            format = CR_RGBA8;
//        else if (nrComponents == 4)
//            format = CR_RGBA8;
        
//        if(nrComponents != 4)
//        {
//            std::cout << "xxxx: " << path << std::endl;
//            stbi_image_free(data);
//            return tid;
//        }
        
        Render::genTextures(1, &tid);
        Render::bindTexture(tid);
        Render::texImage2D(CR_TEXTURE_2D, 0, CR_RGBA8, width, height, data);
        stbi_image_free(data);
    }else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    
    return tid;
}


-(void) initModel{
    for(auto& mesh : _model._meshes)
    {
        int vao;
        Render::genVertexArrays(1, &vao);
        Render::bindVertexArray(vao);
        mesh.VAO = vao;
        
        int vbo;
        Render::genBuffers(1, &vbo);
        Render::bindBuffer(CR_ARRAY_BUFFER, vbo);
        Render::bufferData(CR_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], CR_STATIC_DRAW);
        
        Render::vertexAttributePointer("aPos", 3, CR_FLOAT, false, sizeof(Vertex), 0);
        Render::vertexAttributePointer("aUV", 2, CR_FLOAT, false, sizeof(Vertex), 6*sizeof(float));
        
        int ebo;
        Render::genBuffers(1, &ebo);
        Render::bindBuffer(CR_ELEMENT_ARRAY_BUFFER, ebo);
        mesh.EBO = ebo;
        Render::bufferData(CR_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), &mesh.indices[0], CR_STATIC_DRAW);
    }
}


-(void) prepareRender{
    Render::enable(CR_DEPTH_BUFFER);
    _model.load([self getPath:"res/1001/backpack.obj"]);
    stbi_set_flip_vertically_on_load(true);
    _camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    _camera->ProcessKeyboard(BACKWARD, 1);
    
    _diffuse = loadTexture([self getPath:"res/1001/diffuse.jpg"]);
//    _ao = loadTexture([self getPath:"res/1001/ao.jpg"]);
//    _specular = loadTexture([self getPath:"res/1001/specular.jpg"]);
//    _normal = loadTexture([self getPath:"res/1001/normal.png"]);
//    _roughness = loadTexture([self getPath:"res/1001/roughness.jpg"]);
    
    
    int crvert = Render::createShader(CR_VERTEX_SHADER, [self getPath:"res/shader/ModelVert.lua"]);
    int crfrag = Render::createShader(CR_FRAGMENT_SHADER, [self getPath:"res/shader/ModelFrag.lua"]);
    int crprogram = Render::createProgram();
    Render::attachShader(crprogram, crvert);
    Render::attachShader(crprogram, crfrag);
    Render::linkProgram(crprogram);
    Render::useProgram(crprogram);
    _shader = crprogram;
    Render::setProgramUniform("texture", _diffuse);
    
    glm::mat4 projection = glm::perspective(glm::radians(_camera->Zoom), (float)self.winW / (float)self.winH, 0.1f, 100.0f);
    glm::mat4 view = _camera->GetViewMatrix();
    Render::useProgram(_shader);
    Render::setProgramUniform("projection", glm::value_ptr(projection), 16);
    Render::setProgramUniform("view", glm::value_ptr(view), 16);
    
    [self initModel];
    [self drawModel];
}


-(void) drawModel{
    
    glm::mat4 model = glm::rotate(glm::mat4(1.0), 50.0f * self.time * 0.02f, glm::vec3(0.5f, 1.0f, 0.0f));
    Render::setProgramUniform("model", glm::value_ptr(model), 16);

    Render::useProgram(_shader);
    Render::bindTexture(_diffuse);
    for(auto& mesh : _model._meshes)
    {
        Render::bindVertexArray(mesh.VAO);
        Render::bindBuffer(CR_ELEMENT_ARRAY_BUFFER, mesh.EBO);
        Render::drawArrays(CR_TRIANGLES, 0, mesh.indices.size());
    }
}

-(void) drawRender{
}

@end
