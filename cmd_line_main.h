//
//  cmd_line_main.h
//  dSim
//
//  Created by Hao Xu on 15/4/6.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#ifndef __dSim__cmd_line_main__
#define __dSim__cmd_line_main__

#include <stdio.h>
#include <vector>
#include "base_copter.h"

class cmd_phys_engin : public PhysEngine
{
    
public:
    void create_deme()
    {
        
        base_copter * cop = new base_copter(this);
        phys_list.push_back(cop);

    }
    
};

#endif /* defined(__dSim__cmd_line_main__) */
