//
//  KF.h
//  dSim
//
//  Created by Hao Xu on 15/3/26.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#ifndef __dSim__KF__
#define __dSim__KF__

#include <stdio.h>
#include <Eigen/Dense>

using Eigen::MatrixXd;


class kalman_filter_x
{
public:
    Eigen::MatrixXd Q,R,A,B,C,last,covar;
    
    double sigma_a,sigma_b,dt;
    
    double val = 0 ;
    
    ///\brief build up a sigle kalman filter for one coor
    kalman_filter_x(double sigma_a,double sigma_b,double dt);
    
    void setx(double _x);
    
    double update_with_a(double a);
    double update_with_z(double z);
    
    double value_x();
    double value_x_dot();
    
};
void eigen_test();

#endif /* defined(__dSim__KF__) */
