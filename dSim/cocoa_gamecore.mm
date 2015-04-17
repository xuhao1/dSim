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
    
    NSString * pat = [[NSBundle mainBundle] pathForResource:@"model" ofType:@"stl" inDirectory:@"models" ];
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
void cocoa_hil_core::Loop()
{
    if(stl!=nullptr)
        stl->update_pos();
    [gra setNeedsDisplay:true];
}
void cocoa_hil_core::addDemo()
{
    
    NSString * pat = [[NSBundle mainBundle] pathForResource:@"model" ofType:@"stl" inDirectory:@"models" ];
    const char * pa = [pat UTF8String];
    
//    stl = new stlmodel(pa,hc);
//    [gra addObj:stl];
    
    sim_th = new std::thread([&]{
        while(true)
        {
            hc->send_att();
            long time = getCurrentTime();
            this->sim(0.01);
            long last = getCurrentTime() - time;
            if(last<1000)
                usleep( int( 1000 - last));
        }
    });
    
    waitforserial = new std::thread([&]{
        hc->serial_wait();
    });
}

void cocoa_hil_core::reset()
{
    PxTransform pt(PxVec3(0,0,0.3),PxQuat(0.1,0,0,1));
    hc->actor->setGlobalPose(pt);
}