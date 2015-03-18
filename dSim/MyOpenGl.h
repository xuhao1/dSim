//
//  MyOpenGl.h
//  test
//
//  Created by XuHao on 14-4-11.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "stlmodel.h"
#include "PhysEngine.h"
#include "cam.h"
@interface MyOpenGl : NSOpenGLView
- (void)drawRect:(NSRect) dirtyRect;
- (void)drawObjects;
//- (void)eyeMove:(NSPoint) u;
- (void)eyeOri:(unichar) c;
- (void)addObj:(stlmodel*)model;
@end
