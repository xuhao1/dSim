//
//  model.cpp
//  test
//
//  Created by XuHao on 14-4-15.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#include "phys_model.h"

void xmodel::setPos(float x, float y)
{
    pos.x=x;
    pos.y=y;
}

void xmodel::setPos(float x,float y,float z)
{
    pos.x=x;
    pos.y=y;
    pos.z=z;
}


void xmodel::updatepos()
{
    physx::PxVec3 p=actor->getGlobalPose().p;
    physx::PxQuat q=actor->getGlobalPose().q;
    pos.x=p.x;
    pos.y=p.y;
    pos.z=p.z;
    angle=2*acos(q.w)/M_PI*180.0f;
    float scale=sqrt(q.x*q.x+q.y*q.y+q.z*q.z);
    if(scale>1e-3)
    {
        ax=q.x/scale;
        ay=q.y/scale;
        az=q.z/scale;
    }
}