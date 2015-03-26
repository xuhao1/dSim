//
//  cocoa_gamecore.mm
//  dSim
//
//  Created by Hao Xu on 15/3/18.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "cocoa_gamecore.h"
#include "base_copter.h"
#include "base_gameCore.h"

void stl_copter::run()
{
    calc();
}

void cocoa_gameCore::addDemo()
{
    
    NSString * pat = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"stl" inDirectory:@"models" ];
    const char * pa = [pat UTF8String];
    
    printf("pa %s\n",pa);
    
    stl_copter * demo = new stl_copter(pa,this);
    
    phys_list.push_back((xmodel *)demo);
    [gra addObj:demo->stl];
    
}
void cocoa_gameCore::Loop()
{
    sim(0.033f);
    [gra setNeedsDisplay:true];
}

void cocoa_gameCore::pre_sim()
{
    for(auto a : phys_list){
        a->run();
    }
}