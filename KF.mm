//
//  KF.cpp
//  dSim
//
//  Created by Hao Xu on 15/3/26.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "KF.h"
#include <iostream>
#include "random.h"

namespace base_gamecore
{
    extern double set_height;
}
FILE * fp;
kalman_filter_x::kalman_filter_x(double _sigma_a,double _sigma_b,double _dt)
    :Q(1,1),sigma_a(_sigma_a),sigma_b(_sigma_b),dt(_dt),A(2,2),B(2,1),last(2,1),covar(2,2),C(1,2)
{
    B(0,0) = dt*dt/2.0f;
    B(1,0) = dt;
    
    R = sigma_a*sigma_a*( B  * B.transpose());
    
    Q(0,0) = sigma_b * sigma_b;
    
    A(0,0) = 1;
    A(0,1) = dt;
    A(1,1) = 1;
    
    C(0,0) = 1;
    C(0,1) = 0;
    
    fp = fopen("/Users/xuhao/data/log.txt", "w");
    
    
}

void kalman_filter_x::setx(double _x)
{
    this ->last(0,0) = 0;
    this ->last(1,0) = 0;
    this ->covar = Eigen::MatrixXd(2,2);
}

double kalman_filter_x::update_with_a(double a)
{
    last = A*last + B * a;
    covar = A*covar*A.transpose() + R;
    
//    fprintf(fp,"%3f\n", last(0,0));
    
    return last(0,0);
}

double kalman_filter_x::update_with_z(double _z)
{
    
    double z = normal_s(0, 0.02) + _z;
    
    Eigen::MatrixXd K = covar*C.transpose()* ((C*covar*C.transpose()+Q).inverse());
    
    last = last + K*(z - (C*last)(0,0));
   
    covar = (Eigen::MatrixXd::Identity(2,2) - K * C) * covar;
  
    val = last(0,0);
    
    return last(0,0);
}

double kalman_filter_x::value_x()
{
    //return last(0,0);
     return val;
}

double kalman_filter_x::value_x_dot()
{
    return last(1,0);
}

void eigen_test()
{
    MatrixXd m(2,2);
    std::cout << m << std::endl;
}