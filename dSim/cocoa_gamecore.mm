//
//  cocoa_gamecore.mm
//  dSim
//
//  Created by Hao Xu on 15/3/18.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "cocoa_gamecore.h"
#include "base_copter.h"


void cocoa_gameCore::addDemo()
{
    std::string path="/Users/xuhao/model.stl";
    
    stl_copter* demo=new stl_copter(path,this);
    //demo->set_throttle(1);
    phys_list.push_back((xmodel *)(base_copter *)demo);
    [gra addObj:demo];
    
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