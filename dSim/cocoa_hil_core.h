//
//  cocoa_hil_core.h
//  dSim
//
//  Created by Hao Xu on 15/4/21.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#ifndef __dSim__cocoa_hil_core__
#define __dSim__cocoa_hil_core__

#include <stdio.h>
#include "cocoa_gamecore.h"


class cocoa_hil_core:public cocoa_gameCore
{
public:
    hil_copter * hc = nullptr;
    std::thread * sim_th = nullptr;
    std::thread * waitforserial = nullptr;
    stlmodel * stl = nullptr;
    
    cocoa_hil_core(MyOpenGl * _opengl):
        cocoa_gameCore(_opengl)
    {
    }
    
    void addDemo();
    void Loop();
    void reset();
};

#endif /* defined(__dSim__cocoa_hil_core__) */
