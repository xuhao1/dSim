//
//  myWin.m
//  test
//
//  Created by XuHao on 14-4-14.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#import "myWin.h"
#include "base_gameCore.h"
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
        case NSUpArrowFunctionKey:
        case NSDownArrowFunctionKey:
        case NSLeftArrowFunctionKey:
        case NSRightArrowFunctionKey:
        case NSHomeFunctionKey:
        case NSEndFunctionKey:
            [_opengl eyeOri:c];
            break;
            
        case 'l':
        case '\'':
        case 'p':
        case ';':
            keyboard_control(c);
            break;
        default:
            break;
    }
}
@end

void keyboard_control(unichar c)
{
     switch (c) {
        case 'l':
            base_gamecore::set_yaw_rate -=0.01;
            break;
        case '\'':
            base_gamecore::set_yaw_rate +=0.01;
            break;
        case 'p':
             base_gamecore::set_pitch_rate +=0.01;
             break;
        case ';':
             base_gamecore::set_pitch_rate -=0.01;
             break;
            
        default:
            break;
    }
}
