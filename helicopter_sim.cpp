//
//  helicopter_sim.cpp
//  dSim
//
//  Created by Hao Xu on 15/4/18.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "helicopter_sim.h"
#include "base_gameCore.h"
#include "HIL_Copter.h"

void helicopter::run(float dt)
{
    static float time = 0.0f;
    time += dt;
    
    
    control(dt);
    
    updatepos();
    
    hp->phi = roll * M_PI / 180.0f;
    hp->theta = pitch * M_PI / 180.0f;
    
    hp->u = - vel.x;
    hp->v = - vel.y;
    
    hp->p = roll_rate;
    hp->q = pitch_rate;
    
    static float la = 0;
    
//    if(pos.z>0.5f && time - la > 0.1)
    if(time - la > 0.1)
    {
       
        la = time;
        static double runtime = 0;
//        printf("time:%f\n",
//        (((double)getCurrentTime() ) - runtime) /100000.0);
//        runtime = (double)getCurrentTime();
        
//        fprintf(fp,"%f\t%f\t%f\t%f\t%f\n",
//                time,
//                hp -> v,
//                hp -> p,
//                hp-> phi,
//                hp-> Olon
//                );
    }
    hp->Olat = ser_pitch;
    hp->Olon = ser_roll;
    
    hp->iter_equs(dt);
    
    actor->addForce(PxVec3( - hp->du,- hp->dv,hp->T/hp->m),PxForceMode::eACCELERATION);
    actor->addTorque(PxVec3(hp->dp,hp->dq,0),PxForceMode::eACCELERATION);
    
    static int count = 0;
    
    static FILE * fp = fopen("/Users/xuhao/data/dp.txt", "w");
    
//    if(count++ % 10 ==0 )
        fprintf(fp, "%f\n",hp->phi);
    
//        printf("acc x,%4.2f,y %4.2f dp:%4.4f, dq:%4.4f roll %4.2f pitch %4.2f\n",
//               hp->du,hp->dv,hp->dp,hp->du,
//               roll,
//               pitch
//           );
    
}

void helicopter::control(float dt)
{
    hp->T = hp->m * 9.8 + (base_gamecore::set_height - 0.5f)*hp->m;
    hp->Omega = 150;
    
    static float f = 0;
    f += 0.1 * dt;
    
    ser_roll = base_gamecore::set_roll_rate /10;
    ser_pitch = base_gamecore::set_pitch_rate /10;
    
}