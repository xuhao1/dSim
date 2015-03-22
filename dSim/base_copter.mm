//
//  base_copter.cpp
//  dSim
//
//  Created by Hao Xu on 15/3/18.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "base_copter.h"
#include <math.h>
#include "base_gameCore.h"
#include "control_system.h"

double randomf()
{
    return ((double)(random()%19940707))/19940707.0f;
}
void base_copter::init_default_quad()
{
    mass = 1.2;
    Ixx = 0.01;
    Iyy = 0.01;
    Izz = 0.02;
    
    //setMass(mass);
    //setInteria(Ixx, Iyy, Izz);
    
   
    double err_throttle = 0;
    double err_torque = 0;
    
    motors[0] = motor::createMaxValues(6+err_throttle*randomf(), 0.1+err_torque*(randomf()-0.5));
    motors[0].set_pose(0.225, 0);
    
    motors[1] = motor::createMaxValues(6+err_throttle*randomf(), 0.1+err_torque*(randomf()-0.5));
    motors[1].set_pose(-0.225, 0);
    
    motors[2] = motor::createMaxValues(6+err_throttle*randomf(), -0.1+err_torque*(randomf()-0.5) );
    motors[2].set_pose(0, 0.225);
    
    motors[3] = motor::createMaxValues(6+err_throttle*randomf(), -0.1+err_torque*(randomf()-0.5) );
    
    motors[3].set_pose(0, -0.225);
    
}



void base_copter::set_servo()
{
    double throttle = sqrt(base_gamecore::throttle);
    
    motors[0].set(throttle + set_yaw_con - set_pitch_con);
    motors[1].set(throttle + set_yaw_con + set_pitch_con);
    motors[2].set(throttle - set_yaw_con + set_roll_con);
    motors[3].set(throttle - set_yaw_con - set_roll_con);
}

void base_copter::calc()
{
    control_yaw_rate(this);
    control_pitch_rate(this);
    control_roll_rate(this);
    set_roll_con = 0;
    set_pitch_con = 0;
    
    control_location_z(this);
    
    set_servo();
    static int i = 0;
    i ++;
    
    force = 0;
    torque = 0;
    
    for (auto m:motors)
    {
        force += m.force();
        torque += m.torque();
    }
    force = force/mass;
    force = (force * up_vec)* up_vec;
    
    actor->addForce(PxVec3(force.x,force.y,force.z),PxForceMode::eACCELERATION);
    actor->addTorque(PxVec3(torque.x/Ixx,torque.y/Iyy,torque.z/Izz),PxForceMode::eACCELERATION);
    
}

void base_copter::run()
{
    calc();
}