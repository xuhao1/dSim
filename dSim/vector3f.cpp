//
//  vector3f.cpp
//  Rand_Walk
//
//  Created by xuhao on 13-12-16.
//  Copyright (c) 2013年 xuhao. All rights reserved.
//

#include "vector3f.h"
/// \brief plus

vector3f operator +(vector3f a,vector3f b)
{
	vector3f res(a.x+b.x,a.y+b.y,a.z+b.z);
	return res;
}

/// \brief minus
vector3f operator -(vector3f a,vector3f b)
{
	vector3f res(a.x-b.x,a.y-b.y,a.z-b.z);
	return res;
}
/// \brief dot
double operator *(vector3f a,vector3f b)
{
	double res=a.x*b.x+a.y*b.y+a.z*b.z;
	return res;
}

/// \brief times
vector3f operator *(vector3f a,double b)
{
	vector3f res(a.x*b,a.y*b,a.z*b);
	return res;
}
/// \brief times
vector3f operator *(double b,vector3f a)
{
	vector3f res(a.x*b,a.y*b,a.z*b);
	return res;
}

/// \breif divide
vector3f operator /(vector3f a,double b)
{
	vector3f res(a.x/b,a.y/b,a.z/b);
	return res;
}

/// \brief cross
vector3f operator %(vector3f a,vector3f b)
{
	vector3f res(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
	return res;
}

vector3f& vector3f::operator=(const vector3f&a)
{
	x=a.x;
	y=a.y;
	z=a.z;
	return *this;
}
vector3f& vector3f::operator=(const double t)
{
	x=t;
    y=t;
    z=t;
	return *this;
}

vector3f& vector3f::operator+=(const vector3f&a)
{
	x+=a.x;
	y+=a.y;
	z+=a.z;
	return *this;
}
