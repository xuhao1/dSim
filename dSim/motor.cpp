//
//  motor.cpp
//  dSim
//
//  Created by Hao Xu on 15/3/18.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "motor.h"

motor::motor():
    alpha(0),max_omega(0),omega(0),pose(0,0,0)
{}

motor::motor(double _alpha,double _beta,double _max_o):
    alpha(_alpha),beta(_beta),max_omega(_max_o),omega(0)
{
    
}

void motor::set(double value)
{
    if (value > 1)
        value = 1;
    if (value < 0)
        value = 0;
    omega = max_omega * value;
}

double motor::force_rotor()
{
    return 0.5*omega*omega * alpha;
}

double motor::torque_rotor()
{
    return 0.5*omega*omega * beta;
}

double motor::force_rotor(double value)
{
    set(value);
    return 0.5*omega*omega * alpha;
}

double motor::torque_rotor(double value)
{
    set(value);
    return 0.5*omega*omega * beta;
}

void motor::set_pose(double x, double y)
{
    pose.x = x;
    pose.y = y;
    pose.z = 0;
}

vector3f motor::force()
{
    return vector3f(0, 0, force_rotor());
}

vector3f motor::force(double value)
{
    set(value);
    
    return force();
}

vector3f motor::torque()
{
    vector3f tor = pose % force() + vector3f(0,0,torque_rotor());
    return tor;
}

vector3f motor::torque(double value)
{
    set(value);
    
    vector3f tor = pose % force() + vector3f(0,0,torque_rotor());
    return tor;
}

motor motor::createMaxValues(double max_force, double max_torque)
{
    return motor(max_force*2,max_torque*2,1);
}

motor motor::createMaxValues(double max_force, double max_torque,double max_omega)
{
    motor mo(max_force*2/(max_omega*max_omega),
                 max_torque*2/(max_omega*max_omega)
                 ,max_omega);
    return mo;
}

