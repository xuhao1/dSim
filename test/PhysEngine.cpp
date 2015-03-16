//
//  PhysEngine.cpp
//  test
//
//  Created by XuHao on 14-4-15.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#include "PhysEngine.h"
int PhysEngine::init()
{
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
    if(!mFoundation)
        printf("Failed\n");
    
    auto mProfileZoneManager = &PxProfileZoneManager::createProfileZoneManager(mFoundation);
    if(!mProfileZoneManager)
        printf("PxProfileZoneManager::createProfileZoneManager failed!");
    
    bool recordMemoryAllocations = true;
    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation,
                               PxTolerancesScale(), recordMemoryAllocations, mProfileZoneManager );
    if(!mPhysics)
        printf("PxCreatePhysics failed!");
    sceneDesc=new PxSceneDesc(mPhysics->getTolerancesScale());
    sceneDesc->gravity = PxVec3(0.0f, 0, -9.78f);
    //customizeSceneDesc(sceneDesc);
    if(!sceneDesc->cpuDispatcher)
    {
        auto mCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
        if(!mCpuDispatcher)
            printf("PxDefaultCpuDispatcherCreate failed!");
        printf("this");
        sceneDesc->cpuDispatcher    = mCpuDispatcher;
    }
    
    if(!sceneDesc->filterShader)
    {
        printf("here");
        sceneDesc->filterShader    = gDefaultFilterShader;
    }
    mScene = mPhysics->createScene(*sceneDesc);
    if (!mScene)
        printf("createScene failed!");
    
    return 0;
}