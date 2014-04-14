//
//  MyOpenGl.h
//  test
//
//  Created by XuHao on 14-4-11.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface MyOpenGl : NSOpenGLView
- (void)drawRect:(NSRect) dirtyRect;
- (void) moveCamera:(double) l;
- (void)mkBox;
- (void)drawAnObject;
- (void)eyeMove:(NSPoint) u;
-(void)addObj:(stlmodel*)model;
@end
