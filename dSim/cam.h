//
//  cam.h
//  test
//
//  Created by XuHao on 14-4-15.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#ifndef __test__cam__
#define __test__cam__

#include <iostream>
#include "vector3f.h"
#include <OpenGL/gl.h>
#include <OPenGL/glu.h>
#include <math.h>
class cam
{
public:
    vector3f eye,center,pose;
        float theta,fai;
    cam(
        double    eyeX,
        double    eyeY,
        double    eyeZ,
        double    centerX,
        double    centerY,
        double    centerZ,
        double    upX,
        double    upY,
        double    upZ);
    cam();
    
    void setcam();
    void moveEve(float x,float y,float z);
    void movefirstVision(float x,float y);
};
#endif /* defined(__test__cam__) */
