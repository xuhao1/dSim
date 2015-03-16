//
//  myWin.h
//  test
//
//  Created by XuHao on 14-4-14.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "MyOpenGl.h"

@interface myWin : NSWindow
-(void ) initall;
@property (weak) IBOutlet MyOpenGl *opengl;

@end
