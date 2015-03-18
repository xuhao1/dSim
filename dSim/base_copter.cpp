//
//  base_copter.cpp
//  dSim
//
//  Created by Hao Xu on 15/3/18.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "base_copter.h"

void base_copter::init_default_quad()
{
    mass = 1.2;
    Ixx = 0.01;
    Iyy = 0.01;
    Izz = 0.02;
    
    setMass(mass);
    setInteria(Ixx, Iyy, Izz);
    
    motors[0] = motor::createMaxValues(6, 0.01);
    motors[0].set_pose(0.225, 0);
    
    motors[1] = motor::createMaxValues(6, 0.01);
    motors[1].set_pose(-0.225, 0);
    
    motors[2] = motor::createMaxValues(6, -0.01);
    motors[2].set_pose(0, 0.225);
    
    motors[3] = motor::createMaxValues(6, -0.01);
    motors[3].set_pose(0, -0.225);
    
    set_throttle(0);
}


void base_copter::set_throttle(double v)
{
    for (int i =0 ; i<4; i++) {
        motors[i].set(v);
    }
}

void base_copter::calc()
{
    
    force = 0;
    torque = 0;
    for (auto m:motors)
    {
        force += m.force();
        torque += m.torque();
    }
    actor->addForce(PxVec3(force.x,force.y,force.z));
    actor->addTorque(PxVec3(torque.x,torque.y,torque.z));
    
    //printf("vz:%lf\n",actor->getLinearVelocity().z);
}

void base_copter::run()
{
    calc();
}