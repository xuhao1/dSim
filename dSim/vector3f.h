//
//  vector3f.h
//  Rand_Walk
//
//  Created by xuhao on 13-12-16.
//  Copyright (c) 2013年 xuhao. All rights reserved.
//

#ifndef __RAND_WALK__vector3f__
#define __RAND_WALK__vector3f__

#include <iostream>
#include<math.h>
//对于二维坐标的基本定义与重载
//后期加入GPU计算部分
class vector3f
{
public:
	double x,y,z;
	vector3f()
	{
		x=0;
		y=0;
		z=0;
	}
	vector3f(double _x,double _y,double _z):
    x(_x),y(_y),z(_z)
	{
	}
	vector3f&operator=(const vector3f&);
	vector3f&operator=(const double);
	vector3f&operator+=(const vector3f&);
	double abs()
	{
		return sqrt(x*x+y*y+z*z);
	}
	void norml()
	{
		double a=abs();
		x/=a;
		y/=a;
		z/=a;
	}
};
vector3f operator +(vector3f a,vector3f b);
vector3f operator -(vector3f a,vector3f b);
double operator *(vector3f a,vector3f b);//dot
vector3f operator *(vector3f a,double b);
vector3f operator *(double b,vector3f a);//times
vector3f operator/(vector3f a,double b);
vector3f operator %(vector3f a,vector3f b);
#endif /* defined(__CUDA_FEA__vector3f__) */
