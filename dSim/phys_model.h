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

/// \brief base physics model
///
/// use for PhysX
class xmodel
{
protected:
    // \brief use actor that already have to initalize
    xmodel(physx::PxRigidDynamic* _actor);
    
    vector3f pos; ///>Position
public:
    
    physx::PxRigidDynamic* actor;///< actor in PhysX
    
    float angle,///< angle of quat
    ax, ///< x of quat
    ay, ///< y of quat
    az; ///< z of quat
    
    
    /// \brief 设置位置
    /// \param x 坐标
    /// \param y 坐标
    void setPos(float x,float y);
    
    
    /// \brief 设置位置
    /// \param x x坐标
    /// \param y y坐标
    /// \param z z坐标
    void setPos(float x,float y,float z);
    
    ///\brief use PxPhysics and PxScene to init
    xmodel(PxPhysics * mPhysics,PxScene* mScene);
    
    
    ///\brief xmodel empty
    xmodel();
    
    
    ///\brief set mass
    ///\param mass 重量，单位千克
    void setMass(double mass);
    
    ///\brief set 转动惯量
    ///\param Ixx
    ///\param Iyy
    ///\param Izz
    void setInteria(double Ixx,double Iyy,double Izz);
    
    ///\brief pull position from PhysX
    void updatepos();
    
    
    ///\brief 加载自身的力
    virtual void run() =0;
   
};

#endif /* defined(__test__model__) */
