//
//  main.cpp
//  OliviaHil
//
//  Created by Hao Xu on 15/4/13.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include <iostream>
#include "HIL_Copter.h"
#include <serial/serial.h>
#include <thread>

void test();
int test_hil();

int main(int argc, const char * argv[])
{
    test_hil();
}
int test_hil()
{
    // insert code here...
    std::cout << "Hello, World!\n";
    PhysEngine pe;
    hil_copter hc(&pe,"/dev/cu.SLAB_USBtoUART",921600);
    
    
    std::thread sim([&]{
        while(true)
        {
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
/*

void test()
{
    serial::Serial ser("/dev/cu.SLAB_USBtoUART",115200);
    printf("wiring\n");
    uint8_t buf[64];
    while (true) {
        int res = ser.write(buf, 32);
        printf("res%d\n",res);
    }
}*/