//
//  hil_mode_main.cpp
//  dSim
//
//  Created by Hao Xu on 15/4/16.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "hil_mode_main.h"

#include <iostream>
#include "HIL_Copter.h"
#include <thread>


int test_hil()
{
    // insert code here...
    std::cout << "Hello, World!\n";
    PhysEngine pe;
    hil_copter hc(&pe,"/dev/cu.SLAB_USBtoUART",921600);
    
    
    std::thread sim([&]{
        while(true)
        {
            hc.send_att();
            long time = getCurrentTime();
            pe.sim(0.01);
            long last = getCurrentTime() - time;
            if(last<10000)
                usleep( int( 10000 - last));
        }
    });
    
    hc.serial_wait();
    sim.join();
    return 0;
}