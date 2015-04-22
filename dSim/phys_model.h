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
    vector3f up_vec;
    
public:
    /// Position
    vector3f pos;
    
    /// Velocity
    vector3f vel;
    
    /// Velocity
    vector3f acc;
    
    physx::PxRigidDynamic* actor;///< actor in PhysX
    
    float angle,///< angle of quat,
    ax, ///< x of quat
    ay, ///< y of quat
    az; ///< z of quat
    
    struct quat{
        float w,x,y,z;
    } _quat;
    
    float yaw = 0,///rotate of z
    pitch = 0,///rotate of y
    roll = 0;///rotate of x
    
    float roll_rate;///roll rate
    float yaw_rate;///roll rate
    float pitch_rate;///roll rate
    
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
    xmodel(PxPhysics * mPhysics,PxScene* mScene,double mass);
    
    
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
    
    
    ///\brief Get euler angles
    void get_angles(double w,double x,double y,double z);
    
    
    ///\brief 加载自身的力
    virtual void run(float dt) =0;
   
};

#endif /* defined(__test__model__) */
