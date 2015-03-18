//
//  motor.h
//  dSim
//
//  Created by Hao Xu on 15/3/18.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#ifndef __dSim__motor__
#define __dSim__motor__

#include <stdio.h>
#include "vector3f.h"


/// \brief motor类，用于模拟一个电动机
///
/// F = 0.5 * alpha * omega^2;
/// M = 0.5 * beta * omega^2;
class motor
{
    double alpha,///< 升力系数
    beta,  ///< 扭矩系数
    max_omega, ///最大转速
    omega; ///<目前转速
    vector3f pose;///<相对于重心的位置
    
public:
    
    /// \brief all value to zero
    motor();
    
    /// \brief 构造一个motor
    /// \param _alpha 升力系数
    /// \param _beta 扭矩系数
    /// \return 构造一个motor
    motor(double _alpha,double _beta,double _max_o);
    
    /// \brief 设置motor的动力值
    /// \param value 为0-1的浮点数
    void set(double value);
    
    /// \brief 获得motor的动力值
    /// \return motor的动力，单位为牛顿
    double force_rotor();
    
    /// \brief 获得motor的动力矢量
    vector3f force();
    
    /// \brief 设置并设置motor的动力矢量
    /// \param value 为0-1的浮点数
    vector3f force(double value);
    
    /// \brief 设置omega并且获得motor的动力值
    /// \return motor的动力，单位为牛顿
    double force_rotor(double value);
    
    /// \brief 设置omega并且获得motor的扭矩值
    /// \return motor的扭矩，单位为牛顿米
    double torque_rotor(double value);
    
    /// \brief 获得motor的动力值
    /// \return motor的动力，单位为牛顿米
    double torque_rotor();
    
    /// \brief 设置并获得motor的扭矩矢量
    /// \return motor的扭矩，单位为牛顿米
    vector3f torque(double value);
    
    /// \brief 获得motor的扭矩矢量
    /// \return motor的扭矩，单位为牛顿米
    vector3f torque();
    
    /// \brief 设置位置
    void set_pose(double x,double y);
   
    /// \brief 用最大推力和最大扭矩创建motor,假定最大转速为1
    /// \param max_force 电机的最大升力
    /// \param max_force 电机的最大扭矩
    /// \return 创造出来的电机，最大转速为1
    static motor createMaxValues(double max_force,double max_torque);
    
    /// \brief 用最大推力和最大扭矩以及最大转速创建motor,假定最大转速为1
    /// \param max_force 电机的最大升力
    /// \param max_force 电机的最大扭矩
    /// \param max_force 电机的最大转速
    /// \return 创造出来的电机
    static motor createMaxValues(double max_force,double max_torque,double max_omega);
};

#endif /* defined(__dSim__motor__) */