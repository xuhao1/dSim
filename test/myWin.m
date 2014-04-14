//
//  myWin.m
//  test
//
//  Created by XuHao on 14-4-14.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#import "myWin.h"
@implementation myWin
{
    NSPoint first;
}
-(void)initall
{
    first=[NSEvent mouseLocation];
    self.acceptsMouseMovedEvents=true;
}
-(void)mouseDown:(NSEvent *)theEvent
{
    NSPoint po;
    po.x=0;
    po.y=0;
    [_opengl eyeMove:po];
}
-(void)mouseMoved:(NSEvent *)theEvent
{
    NSPoint mousepos=[NSEvent mouseLocation];
    NSPoint loc=[NSEvent mouseLocation];
    loc.x=loc.x-first.x;
    loc.y=loc.y-first.y;
    [_opengl eyeMove:loc];
}
-(void)keyDown:(NSEvent *)theEvent
{
    unichar c = [[theEvent charactersIgnoringModifiers] characterAtIndex:0];
    switch (c) {
        case 'w':
        case 's':
        case 'a':
        case 'd':
          //  [_opengl objmove:c];
            break;
        case '1':
            [_opengl addObj];
        default:
            break;
    }
}
@end
