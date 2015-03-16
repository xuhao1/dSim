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
}
/*
-(void)mouseMoved:(NSEvent *)theEvent
{
    NSPoint mousepos=[NSEvent mouseLocation];
    NSPoint loc=[NSEvent mouseLocation];
    loc.x=loc.x-first.x;
    loc.y=loc.y-first.y;
    [_opengl eyeMove:loc];
}
 */
-(void)keyDown:(NSEvent *)theEvent
{
    unichar c = [[theEvent charactersIgnoringModifiers] characterAtIndex:0];
    switch (c) {
        case 'w':
        case 's':
        case 'a':
        case 'd':
            [_opengl eyeOri:c];
            break;
        case '1':
        default:
            break;
    }
}
@end
