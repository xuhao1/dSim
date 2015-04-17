//
//  cocoa_gamecore.h
//  dSim
//
//  Created by Hao Xu on 15/3/18.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#ifndef __dSim__cocoa_gamecore__
#define __dSim__cocoa_gamecore__

#include <stdio.h>
#include "stlmodel.h"
#include "base_copter.h"
#include "phys_model.h"
#include <string>
#include <vector>
#include "MyOpenGl.h"
#include "HIL_Copter.h"
#include <thread>

/// \brief game core running of cocoa
class stl_copter:public base_copter
{
public:
    stlmodel * stl;
    stl_copter(std::string path,PhysEngine *pe):
        base_copter(pe)
    {
        init_default_quad();
        stl = new stlmodel(path,this);
    }
    void run();
};


class cocoa_gameCore :public PhysEngine
{
public:
    MyOpenGl* gra;
    
    static stl_copter * cop0;
    
    std::vector<xmodel *> phys_list;
public:
    ///\brief init game core with an opengl session
    cocoa_gameCore(MyOpenGl *_opengl):
        gra(_opengl),PhysEngine()
    {
        
    }
    
    ///>add demo to game
    virtual void addDemo();
    
    void pre_sim();
    
    virtual void Loop();
};

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
        hc = new hil_copter(this,"/dev/cu.SLAB_USBtoUART",115200);
        phys_list.push_back((xmodel *)hc);
    }
    
    void addDemo();
    void Loop();
    void reset();
};

#endif /* defined(__dSim__cocoa_gamecore__) */
