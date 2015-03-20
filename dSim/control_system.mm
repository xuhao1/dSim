//
//  control_system.cpp
//  dSim
//
//  Created by Hao Xu on 15/3/19.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "control_system.h"
#include "base_gameCore.h"

void control_yaw(base_copter *qiaochu)
{
    qiaochu->set_yaw_con = (base_gamecore::set_yaw_rate - qiaochu->yaw_rate)*2.5;
}

void control_pitch(base_copter *qiaochu)
{
    qiaochu->set_pitch_con = (base_gamecore::set_pitch_rate - qiaochu->pitch_rate)*0.5;
}

void control_roll(base_copter *qiaochu)
{
    qiaochu->set_roll_con =  (base_gamecore::set_roll_rate - qiaochu->roll_rate)*0.5;
}