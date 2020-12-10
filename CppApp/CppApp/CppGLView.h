//
//  CppGLView.h
//  CppApp
//
//  Created by yubo on 2020/10/14.
//  Copyright © 2020 test. All rights reserved.
//

#ifndef CppGLView_h
#define CppGLView_h

#import<AppKit/AppKit.h>
#include <string>

@interface CppGLView : NSOpenGLView

- (void) drawRect: (NSRect) bounds;
-(const std::string) getPath:(const std::string& )path;

@property float time;
@property int winW;
@property int winH;

@end


#endif /* CppGLView_h */
