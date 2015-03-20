//
//  AppDelegate.m
//  test
//
//  Created by XuHao on 14-4-11.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#import "AppDelegate.h"
#import "MyOpenGl.h"
#include "stlmodel.h"
@implementation AppDelegate
{
    NSPoint first;
}

@synthesize timer;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    timer = [NSTimer scheduledTimerWithTimeInterval:0.03 target:self selector:@selector(update) userInfo:nil repeats:YES];
    _core=new cocoa_gameCore(_opengl);
    
    [_win initall];
     first=[NSEvent mouseLocation];
    
}

- (void)keyDown:(NSEvent *)theEvent {
    NSLog(@"hey");
}

- (IBAction)left:(id)sender {
    //[_opengl up];
    _core->addDemo();
    
}

- (IBAction)right:(id)sender {
    //[_opengl down];
    
}
- (IBAction)slide:(id)sender
{
    base_gamecore::throttle = [sender doubleValue]/100;
    /*
    _opengl.xro=[sender doubleValue]/100*3.14;
    [_opengl setNeedsDisplay:true];
    */
}
- (void)update
{
    //printf("%f\n",[_Slider0 doubleValue]);
    //_opengl.xro=[_Slider0 doubleValue]/100*3.14;
    //[_opengl setNeedsDisplay:true];
    _core->Loop();
}
- (IBAction)reset:(id)sender 
{
    //_opengl.zro=0;
}
@end
