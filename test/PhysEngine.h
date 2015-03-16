//
//  PhysEngine.h
//  test
//
//  Created by XuHao on 14-4-15.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#ifndef __test__PhysEngine__
#define __test__PhysEngine__

#include <iostream>
#define NDEBUG
#include "PxPhysicsAPI.h"

using namespace physx;

class PhysEngine
{
    float random()
    {
        float i=rand()%1000; 
        return i/1000.0f;
    }
public:
    PxDefaultErrorCallback gDefaultErrorCallback;
    PxDefaultAllocator gDefaultAllocatorCallback;
    physx::PxPhysics *mPhysics;
    PxSimulationFilterShader gDefaultFilterShader=PxDefaultSimulationFilterShader;
    PxScene* mScene;
    void *mScratchBlock;
    physx::PxFoundation * mFoundation;
    int init();
    PhysEngine()
    {
        init();
        //setupActor();
        //sim(1);
        PxMaterial* aMaterial;
        aMaterial = mPhysics->createMaterial(0.5f, 0.5f, 1.0f);    //static friction, dynamic friction, restitution
        PxRigidStatic*plane;
        plane =  PxCreatePlane(*mPhysics, PxPlane(PxVec3(0,0,1), 0), *aMaterial);
        mScene->addActor(*plane);
    }
    PxSceneDesc *sceneDesc;
    /*
    int setupActor()
    {
        
        aSphereActor =  PxCreateDynamic(*mPhysics, PxTransform( PxVec3(1, 0 ,5) ) , PxSphereGeometry(1),*aMaterial, 1);
        plane =  PxCreatePlane(*mPhysics, PxPlane(PxVec3(0,0,1), 0), *aMaterial);
        mScene->addActor(*aSphereActor);
        mScene->addActor(*plane);
        return  0;
    }
    */
    PxRigidDynamic* addDemo()
    {

        PxMaterial* aMaterial;
        aMaterial = mPhysics->createMaterial(0.5f, 0.5f, 1.0f);    //static friction, dynamic friction, restitution
        if(!aMaterial)
            printf("createMaterial failed!");
        PxRigidDynamic* aSphereActor ;
        aSphereActor =  PxCreateDynamic(*mPhysics, PxTransform( PxVec3(0, 0 ,10) ) , PxBoxGeometry(1,1,1),*aMaterial, 1);
        aSphereActor->setLinearVelocity(PxVec3((random()-0.5)*10,(random()-0.5)*10,0));
        mScene->addActor(*aSphereActor);

        return aSphereActor;
    }
    
    int sim(double time)
    {
        for (int j=0; j<time*10000; j++)
        {
            mScene->simulate(1e-4);
            mScene->fetchResults(true);
        }
        return 0;
    }
};
#endif /* defined(__test__PhysEngine__) */
