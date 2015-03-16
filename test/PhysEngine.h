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
#include "phys_model.h"

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
        aMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.5f);    //static friction, dynamic friction, restitution
        PxRigidStatic*plane;
        plane =  PxCreatePlane(*mPhysics, PxPlane(PxVec3(0,0,1), 0), *aMaterial);
        mScene->addActor(*plane);
    }
    PxSceneDesc *sceneDesc;
    
    xmodel* addDemo()
    {
        xmodel * x0 = new xmodel(this->mPhysics,this->mScene);
        return x0;
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
