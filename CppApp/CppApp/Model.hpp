//
//  Model.hpp
//  AssimpTest
//
//  Created by yubo on 2020/12/9.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <vector>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.hpp"

class Model
{
public:
    std::vector<Mesh> _meshes;
    
    bool load(const std::string& path);
    
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
    
private:
    std::string _dir;
    std::vector<Texture> textures_loaded;
};

#endif /* Model_hpp */
