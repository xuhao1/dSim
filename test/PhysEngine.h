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
#include <iostream>
#define NDEBUG
#include "PxPhysicsAPI.h"

using namespace physx;

class PhysEngine
{
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
    }
    PxRigidDynamic* aSphereActor ;
    PxSceneDesc *sceneDesc;
    PxRigidStatic*plane;
    PxMaterial* aMaterial;
    int setupActor()
    {
        
        aMaterial = mPhysics->createMaterial(0.5f, 0.5f, 1.0f);    //static friction, dynamic friction, restitution
        if(!aMaterial)
            printf("createMaterial failed!");
        aSphereActor =  PxCreateDynamic(*mPhysics, PxTransform( PxVec3(1, 0 ,5) ) , PxSphereGeometry(1),*aMaterial, 1);
        plane =  PxCreatePlane(*mPhysics, PxPlane(PxVec3(0,0,1), 0), *aMaterial);
        mScene->addActor(*aSphereActor);
        mScene->addActor(*plane);
        return  0;
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
