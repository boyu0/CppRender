//
//  CppWindow.hpp
//  CppRender
//
//  Created by yubo on 2020/10/22.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppWindow_hpp
#define CppWindow_hpp

#include <stdio.h>
namespace CppRender{
class Context;
class Window{
public:
    Window(Context* ctx):_ctx(ctx){}
    void doViewPort();

public:
    bool init(int width, int height);

private:
    Context* _ctx{};
    int _frameBuffer{};
    bool _autoChangeSize{true};
    void* data{};
};
}

#endif /* CppWindow_hpp */
