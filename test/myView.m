//
//  myView.m
//  test
//
//  Created by XuHao on 14-4-14.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#import "myView.h"

@implementation myView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    return self;
}
- (void)mouseMoved:(NSEvent *)theEvent
{
    NSLog(@"Mouse Moved");
}
-(void)keyDown:(NSEvent *)theEvent
{
    NSLog(@"viewchar");
}
- (void)drawRect:(NSRect)dirtyRect
{
	[super drawRect:dirtyRect];
	
    // Drawing code here.
}

@end
