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
#include "base_gameCore.h"
#include "base_copter.h"
#include "phys_model.h"
#include <string>
#include <vector>

/// \brief game core running of cocoa
class cocoa_gameCore :public PhysEngine
{
    MyOpenGl* gra;
    
    std::vector<xmodel *> phys_list;
public:
    ///\brief init game core with an opengl session
    cocoa_gameCore(MyOpenGl *_opengl):
        gra(_opengl),PhysEngine()
    {
        
    PxMaterial* aMaterial;
    aMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.5f);    //static friction, dynamic friction, restitution
    }
    
    ///>add demo to game
    void addDemo();
    
    void pre_sim();
    
    void Loop();
};

extern double throttle;
class stl_copter:public base_copter,public stlmodel
{
public:
    stl_copter(std::string path,PhysEngine *pe):
        stlmodel(path),base_copter(pe)
    {
        ((stlmodel * ) this)->actor =  ((base_copter * ) this)->actor;
        init_default_quad();
    }
    void run()
    {
        set_throttle(throttle);
        calc();
    }
};

#endif /* defined(__dSim__cocoa_gamecore__) */
