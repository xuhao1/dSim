//
//  gameCore.h
//  test
//
//  Created by XuHao on 14-4-15.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#ifndef __test__gameCore__
#define __test__gameCore__

#include <iostream>
#include "PhysEngine.h"
#import "MyOpenGl.h"
#include "stlmodel.h"
#include "phys_model.h"

/// \brief The core of all the simulation, with physics engine, and commucation part

class base_gameCore: public PhysEngine
{
public:

    base_gameCore():
        PhysEngine()
    {}

    
    ///> a unit of aloop
    virtual void Loop()=0;
};



#endif /* defined(__test__gameCore__) */
