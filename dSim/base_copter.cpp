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
    Ixx = 0.5;
    Iyy = 0.5;
    Izz = 1;
    
    //setMass(mass);
    //setInteria(Ixx, Iyy, Izz);
    
   
    double err_throttle = 0;
    double err_torque = 0;
    
    double default_torque =  + 0.5;
    
    motors[3] = motor::createMaxValues(6+err_throttle*randomf(), - default_torque +err_torque*(randomf()-0.5));
    motors[3].set_pose(0.225, 0);
    
    motors[2] = motor::createMaxValues(6+err_throttle*randomf(), - default_torque +err_torque*(randomf()-0.5));
    motors[2].set_pose(-0.225, 0);
    
    
    motors[1] = motor::createMaxValues(6+err_throttle*randomf(), default_torque +err_torque*(randomf()-0.5) );
    motors[1].set_pose(0, 0.225);
    
    motors[0] = motor::createMaxValues(6+err_throttle*randomf(), default_torque +err_torque*(randomf()-0.5) );
    
    motors[0].set_pose(0, -0.225);
    
    
}



void base_copter::set_servo()
{
    double throttle = sqrt(base_gamecore::throttle);
    
    motors[0].set(throttle + set_yaw_con - set_pitch_con);
    motors[1].set(throttle + set_yaw_con + set_pitch_con);
    motors[2].set(throttle - set_yaw_con + set_roll_con);
    motors[3].set(throttle - set_yaw_con - set_roll_con);
}

void base_copter::control()
{
    control_yaw_rate(this);
    control_pitch_rate(this);
    control_roll_rate(this);
    control_location_z(this);
    
    set_servo();
}

void base_copter::calc()
{
    updatepos();
    
    static int count = 0;
    
    count ++;
    
    if(count % 500 == 0)
    {
        base_gamecore::kfx.update_with_z(this->pos.z);
    }
    
    
    //833 per second
    
    
    if (count % 12 == 0)
    {
        control();
    }
    
    
    static int i = 0;
    i ++;
    
    force = 0;
    torque = 0;
    
    for (auto m:motors)
    {
        force += m.force();
        torque += m.torque();
    }
    force = (force * up_vec)* up_vec;
    force = force/mass;
    
    
//    torque.x = 0;
//    torque.z = 0;
    
    actor->addForce(PxVec3(force.x,force.y,force.z),PxForceMode::eACCELERATION);
    actor->addTorque(PxVec3(torque.x/Ixx,torque.y/Iyy,torque.z/Izz),PxForceMode::eACCELERATION);
    
//    actor->addTorque(PxVec3(torque.x/Ixx,0,0),PxForceMode::eACCELERATION);
    
    if (count % 10 == 0)
    {
        base_gamecore::kfx.update_with_a(acc.z);
    }
    
}

void base_copter::run(float dt)
{
    calc();
}