//
//  GLDraw.hpp
//  CppApp
//
//  Created by yubo on 2020/12/9.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef GLDraw_hpp
#define GLDraw_hpp

#include <stdio.h>

class GLDraw
{
public:
    void prepare();
    void draw(int width, int height, void* data);
    
private:
    unsigned int VAO{};
    int program{};
    unsigned int texture{};
};

#endif /* GLDraw_hpp */
