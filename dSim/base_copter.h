//
//  base_copter.h
//  dSim
//
//  Created by Hao Xu on 15/3/18.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#ifndef __dSim__base_copter__
#define __dSim__base_copter__

#include <stdio.h>
#include "motor.h"
#include <vector>
#include "phys_model.h"
#include "PhysEngine.h"

///\brief the base class of copters

class base_copter:public xmodel
{
    std::vector<motor> motors;///> motors of the copter
    
    xmodel * body;///> body of the copter
    
    double mass,///>mass of the copter
    Ixx ,///> Ixx of the copter
    Iyy ,///> Iyy of the copter
    Izz ;///> Izz of the copter
    
    vector3f force,///> force now
    torque;///> torque now
public:
    
    ///\brief build a copter with default values
    base_copter(PhysEngine* pe):
        motors(4),xmodel(pe->mPhysics,pe->mScene)
    {
        init_default_quad();
    }
    
    
    ///\brief set up with default values
    void init_default_quad();
    
    ///\brief calcute and set into physics model
    virtual void calc();
    
    ///\brief test throttle
    void set_throttle(double v);
    
    ///\brief run
    //@overload
    void run();
};

#endif /* defined(__dSim__base_copter__) */
