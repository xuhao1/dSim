//
//  helicopter_sim.h
//  dSim
//
//  Created by Hao Xu on 15/4/18.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#ifndef __dSim__helicopter_sim__
#define __dSim__helicopter_sim__

#include <stdio.h>
#include "Helicopter/heli_phys.h"
#include "phys_model.h"
#include "PhysEngine.h"


class helicopter:public xmodel
{
    FILE * fp;
public:
    base_heli_phys * hp;
    float ser_pitch,ser_roll;
    helicopter(PhysEngine * pe):
        xmodel(pe->mPhysics,pe->mScene,1.2)
    {
        hp = new base_heli_phys;
        
        setMass(hp->m);
        setInteria(hp->Ixx, hp->Iyy, 1);
        
        fp = fopen("/Users/xuhao/heli_data.txt", "w");
    }
    
    virtual void run(float dt) override;
    virtual void control(float dt) ;
};

#endif /* defined(__dSim__helicopter_sim__) */
