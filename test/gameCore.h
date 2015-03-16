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

class gameCore
{
public:
    PhysEngine physcore;
    MyOpenGl* gra;
    gameCore(MyOpenGl *_opengl):
        gra(_opengl),physcore()
    {
    }
    void addDemo()
    {
        physx::PxRigidDynamic* rig=physcore.addDemo();
        char *path="/Users/xuhao/model.stl";
        stlmodel* demo=new stlmodel(path,rig);
        [gra addObj:demo];
        
    }
    void Loop()
    {
        physcore.sim(0.033f);
        [gra setNeedsDisplay:true];
    }
};

#endif /* defined(__test__gameCore__) */
