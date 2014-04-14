//
//  vector3f.cpp
//  Rand_Walk
//
//  Created by xuhao on 13-12-16.
//  Copyright (c) 2013年 xuhao. All rights reserved.
//

#include "vector3f.h"
vector3f operator +(vector3f a,vector3f b)
{
	vector3f res(a.x+b.x,a.y+b.y,a.z+b.z);
	return res;
}
vector3f operator -(vector3f a,vector3f b)
{
	vector3f res(a.x-b.x,a.y-b.y,a.z-b.z);
	return res;
}
double operator *(vector3f a,vector3f b)//dot
{
	double res=a.x*b.x+a.y*b.y+a.z*b.z;
	return res;
}

vector3f operator *(vector3f a,double b)//times
{
	vector3f res(a.x*b,a.y*b,a.z*b);
	return res;
}
vector3f operator *(double b,vector3f a)//times
{
	vector3f res(a.x*b,a.y*b,a.z*b);
	return res;
}
vector3f operator/(vector3f a,double b)//div
{
	vector3f res(a.x/b,a.y/b,a.z/b);
	return res;
}
vector3f operator %(vector3f a,vector3f b)//cross
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

vector3f& vector3f::operator+=(const vector3f&a)
{
	x+=a.x;
	y+=a.y;
	z+=a.z;
	return *this;
}
