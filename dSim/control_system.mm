//
//  control_system.cpp
//  dSim
//
//  Created by Hao Xu on 15/3/19.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "control_system.h"
#include "base_gameCore.h"

double intt_yaw_rate = 0;
double intt_pitch_rate = 0;
double intt_roll_rate = 0;
double intt_height_err = 0;

void control_yaw_rate(base_copter *qiaochu)
{
    static double set_yaw_la = 0;
    
    if (set_yaw_la - base_gamecore::set_yaw_rate>1e-3)
    {
        intt_yaw_rate  = 0;
    }
    
    double err = (base_gamecore::set_yaw_rate - qiaochu->yaw_rate);
    
    intt_yaw_rate += err * 1e-4;
    
    qiaochu->set_yaw_con = intt_yaw_rate * 2 + err;
}

void control_pitch_rate(base_copter *qiaochu)
{
    qiaochu->set_pitch_con = (base_gamecore::set_pitch_rate - qiaochu->pitch_rate)*0.5;
}

void control_roll_rate(base_copter *qiaochu)
{
    qiaochu->set_roll_con =  (base_gamecore::set_roll_rate - qiaochu->roll_rate)*0.5;
}
void control_location_z(base_copter *qiaochu)
{
    
    if (base_gamecore::set_height < 1)
        return;
    static double last_set_height = 0;
    
    if (last_set_height - base_gamecore::set_height>1e-3)
    {
        intt_height_err = 0;
    }
   
    double height_now = base_gamecore::kfx.value_x();
    double height_dot_now = base_gamecore::kfx.value_x_dot();
    
    double err = base_gamecore::set_height - height_now;
    
    intt_height_err += err * 1e-4;
    if (intt_height_err > 10)
        intt_height_err = 10;
    if(intt_height_err < -10)
        intt_height_err = -10;
    
    double height_rate = height_dot_now ;
    
    double p_height = 0.294512;
    double i_height = 0.294512;
    double d_height = 0.707128;
    
    base_gamecore::throttle = 0.5 + p_height*err + i_height*intt_height_err - d_height * height_rate;
    
    if (base_gamecore::throttle > 1)
        base_gamecore::throttle = 1;
    
    if (base_gamecore::throttle < 0)
        base_gamecore::throttle = 0;
    
    static int count = 0;
    count ++;
    /*
    if (count%100 == 0)
    printf("Set height %3f, height %3f, intt_height %3f\n",base_gamecore::set_height,qiaochu->pos.z,intt_height_err);
    */
}