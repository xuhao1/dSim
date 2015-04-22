//
//  cocoa_hil_core.mm
//  dSim
//
//  Created by Hao Xu on 15/4/21.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "cocoa_hil_core.h"
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
    
    hc = new hil_copter(this,"/dev/cu.SLAB_USBtoUART",115200);
    phys_list.push_back((xmodel *)hc);
    
    stl = new stlmodel(pa,hc);
    [gra addObj:stl];
    
    sim_th = new std::thread([&]{
        while(true)
        {
            long time = getCurrentTime();
            static float simt = 0;
            
            hc->send_att();
            
            float dtime  = 0.008;
            simt += dtime;
            
            
            this->sim(dtime);
            
            long last = getCurrentTime() - time;
            
            if(last < dtime * 1000000)
                usleep( int(dtime * 1000000  - last));
            
            static int count = 0;
            if(count ++ %100 == 0)
            {
                printf("sim:%4.2f\n",simt);
            }
            
        }
    });
    
    waitforserial = new std::thread([&]{
        while(hc == nullptr)
            usleep(10000);
        hc->serial_wait();
    });
}

void cocoa_hil_core::reset()
{
    PxTransform pt(PxVec3(0,0,0.3),PxQuat(0.1,0,0,1));
    hc->actor->setGlobalPose(pt);
}
