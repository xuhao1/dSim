//
//  model.cpp
//  test
//
//  Created by XuHao on 14-4-15.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#include "phys_model.h"
#include "base_gameCore.h"

xmodel::xmodel(physx::PxRigidDynamic* _actor):
    pos(0,0,0),actor(_actor)
{
    physx::PxVec3 p=actor->getGlobalPose().p;
    pos.x=p.x;
    pos.y=p.y;
    pos.z=p.z;
    
}

xmodel::xmodel(PxPhysics * mPhysics,PxScene* mScene,double mass):
    pos(0,0,0)
{
    PxMaterial* aMaterial;
    
    aMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.1);    //static friction, dynamic friction, restitution
    if(!aMaterial)
        printf("createMaterial failed!");
    
    
    PxTransform pt(PxVec3(0,0,0.3),PxQuat(0.1,0,0,1));
    
    actor =  PxCreateDynamic(*mPhysics, pt, PxBoxGeometry(0.25,0.25,0.128),*aMaterial, mass*16);
    
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
    physx::PxTransform pt;
    pt = actor -> getGlobalPose();
    physx::PxVec3 p=pt.p;
    physx::PxQuat q=pt.q;
    physx::PxVec3 up(0,0,1);
    
    up = pt.rotate(up);
    
    
    up_vec.x = up.x;
    up_vec.y = up.y;
    up_vec.z = up.z;
    
    pos.x=p.x;
    pos.y=p.y;
    pos.z=p.z;
    
    PxVec3 _vel = actor->getLinearVelocity();
    
    vector3f vel;
    vel.x = _vel.x;
    vel.y = _vel.y;
    vel.z = _vel.z;
    
    vector3f acc = (vel - this->vel) * 10000;
    
    if (acc.abs() < 5 * this->acc.abs() || this->acc.abs() <1e-2 )
    {
        this -> acc = acc;
    }
    
    this->vel = vel;
    
    get_angles(q.w,q.x,q.y,q.z);
    
    _quat.w = q.w;
    _quat.x = q.x;
    _quat.y = q.y;
    _quat.z = q.z;
    
    angle=2*acos(q.w)/M_PI*180.0f;
    
    float scale=sqrt(q.x*q.x+q.y*q.y+q.z*q.z);
    if(scale>1e-3)
    {
        ax=q.x/scale;
        ay=q.y/scale;
        az=q.z/scale;
    }
}


void xmodel::get_angles(double w, double x, double y, double z)
{
    roll = atan2(2*(w*x+y*z), 1-2*(x*x+y*y))/M_PI * 180;

    yaw_rate   = actor->getAngularVelocity().z;
    roll_rate  = actor ->getAngularVelocity().x;
    pitch_rate = actor ->getAngularVelocity().y;
    
    pitch = asin(2*(w*y-z*x))/M_PI * 180;
    yaw = atan2(2*(w*z+y*x), 1-2*(z*z+y*y))/M_PI * 180;
    
    //printf("act pit:%5f\n",actor->getAngularVelocity().y);
//    printf("control:%5f\n",base_gamecore::set_pitch_rate);
    
    //printf("roll:%4lf,theta:%4lf,yaw:%4lf\n",roll,pitch,yaw);
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