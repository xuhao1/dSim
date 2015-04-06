//
//  cmd_line_main.cpp
//  dSim
//
//  Created by Hao Xu on 15/4/6.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "cmd_line_main.h"
#include "base_copter.h"

int main()
{
    cmd_phys_engin ce;
    
    ce.create_deme();
    
    printf("Hello,world\n");
    
    for (int i=0; i<1000; i++) {
        printf("Start Simulation\n");
        ce.sim(0.03);
    }
    
}