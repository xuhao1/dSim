//
//  control_system.h
//  dSim
//
//  Created by Hao Xu on 15/3/19.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#ifndef __dSim__control_system__
#define __dSim__control_system__

#include <stdio.h>
#include "base_copter.h"
//TODO Build Control System in class

void control_yaw_rate(base_copter * cop);
void control_pitch_rate(base_copter *qiaochu);
void control_roll_rate(base_copter *qiaochu);
void control_location_z(base_copter * qiaochu);

#endif /* defined(__dSim__control_system__) */
