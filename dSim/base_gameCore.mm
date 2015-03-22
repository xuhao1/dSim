//
//  gameCore.cpp
//  test
//
//  Created by XuHao on 14-4-15.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#include "base_gameCore.h"
#include <string>


namespace base_gamecore {
    /// Main Copter for control system
    stl_copter * cop = nullptr;
    double throttle = 0 ;
    
    double set_roll_rate = 0;
    
    double set_pitch_rate = 0;
    
    double set_yaw_rate = 0;
    
    double set_height = 0.2;
}