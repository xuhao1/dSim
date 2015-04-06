//
//  random.cpp
//  dSim
//
//  Created by Hao Xu on 15/3/27.
//  Copyright (c) 2015年 xuhao. All rights reserved.
//

#include "random.h"
#include <stdlib.h>

double randf()
{
    return ((double)(rand()%10000)) /10000.0f;
}

double normal_s(double a,double b)
{
    double r =
    randf() +randf() +
    randf() +randf() +
    randf() +randf() +
    randf() +randf() +
    randf() +randf() +
    randf() +randf() - 6 ;
    
    return r * b +a;
}