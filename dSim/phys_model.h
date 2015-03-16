//
//  model.h
//  test
//
//  Created by XuHao on 14-4-15.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#ifndef __test__model__
#define __test__model__

#include "vector3f.h"
#include <OpenGL/glu.h>
#ifndef NDEBUG
#define NDEBUG
#endif

#include "PxPhysicsAPI.h"

using namespace physx;
class xmodel
{
public:
    bool maked;
    physx::PxRigidDynamic* actor;
    GLuint ptr;
    float angle,ax,ay,az;
    void setPos(float x,float y);
    void setPos(float x,float y,float z);
    xmodel(physx::PxRigidDynamic* _actor):
        maked(0),pos(0,0,0),actor(_actor)
    {
        physx::PxVec3 p=actor->getGlobalPose().p;
        pos.x=p.x;
        pos.y=p.y;
        pos.z=p.z;
        
    }
    
    xmodel(PxPhysics * mPhysics,PxScene* mScene):
        maked(0),pos(0,0,0)
    {
        PxMaterial* aMaterial;
        
        aMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.3f);    //static friction, dynamic friction, restitution
        if(!aMaterial)
            printf("createMaterial failed!");
        
        PxTransform pt(PxVec3(0,0,8),PxQuat(1, 0, 0, 3.1415926/2));
        
        actor =  PxCreateDynamic(*mPhysics, pt, PxBoxGeometry(10,2,10),*aMaterial, 1);
        
        
        //actor->setLinearVelocity(PxVec3((random()-0.5)*10,(random()-0.5)*10,0));
        mScene->addActor(*actor);
        
        physx::PxVec3 p=actor->getGlobalPose().p;
        pos.x=p.x;
        pos.y=p.y;
        pos.z=p.z;
    }
    
    void updatepos();
   
    vector3f pos;
    //virtual GLuint model() = 0;
    
};

#endif /* defined(__test__model__) */
