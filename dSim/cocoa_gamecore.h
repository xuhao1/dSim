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
    
    static xmodel * cop0 ;
    
public:
    ///\brief init game core with an opengl session
    cocoa_gameCore(MyOpenGl *_opengl):
        gra(_opengl),PhysEngine()
    {
    }
    
    
    ///>add demo to game
    virtual void addDemo();
    
    virtual void Loop();
    
    void reset(){};
    
//    void pre_sim();
};

#endif /* defined(__dSim__cocoa_gamecore__) */
