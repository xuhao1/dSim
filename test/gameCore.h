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

class gameCore
{
public:
    PhysEngine physcore;
    MyOpenGl* gra;
    gameCore(MyOpenGl *_opengl):
        gra(_opengl),physcore()
    {
    }
};
#endif /* defined(__test__gameCore__) */
