//
//  HIL_Copter.h
//  dSim
//
//  Created by Hao Xu on 15/4/13.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#ifndef __dSim__HIL_Copter__
#define __dSim__HIL_Copter__

#include <stdio.h>
#include "base_copter.h"
#include <pixhawk/mavlink.h>
#include <functional>
#include <stdio.h>
#include <fcntl.h>   /* File control definitions */
#include <unistd.h>  /* UNIX standard function definitions */

class hil_copter : public base_copter
{
    int fd; /* File descriptor for the port */
    int open_port(const char *port);
    bool setup_port(int baud, int data_bits, int stop_bits, bool parity, bool hardware_control);
    
    float actuator[8];
    
    void handle_msg(mavlink_message_t * msg);
    
    int send_msg(mavlink_message_t * msg);
public:
    hil_copter(PhysEngine * pe,std::string add,int baud):
        base_copter(pe)
    {
        fd = open_port(add.c_str());
        
        if(fd < 0)
        {
            printf("Failed!\n");
            exit(EXIT_FAILURE);
        }
        
       	bool setup = setup_port(baud, 8, 1, false, false);
//        bool setup = true;
        
        if (!setup)
        {
            printf("failure, could not configure port.\n");
            exit(EXIT_FAILURE);
        }
    }
    
    float cvtpwm2act(uint16_t );
    
    void control() override;
    
    
    void run() override;
    
    int send_att();
    
    int serial_wait();
    
};
#endif /* defined(__dSim__HIL_Copter__) */
