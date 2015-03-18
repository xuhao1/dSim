//
//  model.cpp
//  test
//
//  Created by XuHao on 14-4-15.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#include "phys_model.h"

xmodel::xmodel(physx::PxRigidDynamic* _actor):
    pos(0,0,0),actor(_actor)
{
    physx::PxVec3 p=actor->getGlobalPose().p;
    pos.x=p.x;
    pos.y=p.y;
    pos.z=p.z;
    
}

xmodel::xmodel(PxPhysics * mPhysics,PxScene* mScene):
    pos(0,0,0)
{
    PxMaterial* aMaterial;
    
    aMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.4);    //static friction, dynamic friction, restitution
    if(!aMaterial)
        printf("createMaterial failed!");
    
    
    PxTransform pt(PxVec3(0,0,10),PxQuat(1, 0, 0, 3.1415926535/4));
    actor =  PxCreateDynamic(*mPhysics, pt, PxBoxGeometry(10,2,10),*aMaterial, 0.01);
    
    actor->setLinearVelocity(PxVec3(0,0,0));
    mScene->addActor(*actor);
    
    physx::PxVec3 p=actor->getGlobalPose().p;
    pos.x=p.x;
    pos.y=p.y;
    pos.z=p.z;
}
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

void xmodel::setInteria(double Ixx, double Iyy, double Izz)
{
    actor->setMassSpaceInertiaTensor(PxVec3(Ixx,Iyy,Izz));
}

void xmodel::setMass(double mass)
{
    
    actor->setMass((PxReal)mass);
}


xmodel::xmodel():
    actor(nullptr)
{
    
}