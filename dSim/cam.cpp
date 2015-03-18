//
//  cam.cpp
//  test
//
//  Created by XuHao on 14-4-15.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#include "cam.h"

cam::cam(
        double    eyeX,
        double    eyeY,
        double    eyeZ,
        double    centerX,
        double    centerY,
        double    centerZ,
        double    upX,
        double    upY,
        double    upZ):
        eye(eyeX,eyeY,eyeZ),center(centerX,centerY,centerZ),pose(upX,upY,upZ)
    {
        float rad=(center-eye).abs();
        theta=asin( (center-eye).y/rad);
        fai=atan((center.x-eye.x)/(center.y-eye.y));
        
    }
cam::cam():
        eye(0,0,0),center(0,1,1),pose(0,0,1),theta(0),fai(0)
    {

    }

void cam::setcam()
    {
        glMatrixMode (GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye.x, eye.y, eye.z, center.x, center.y,center.z, pose.x, pose.y, pose.z);
    }

void cam::moveEve(float x,float y,float z)
 {
        eye.x += x;
        eye.y += y;
        eye.z += z;
        
        movefirstVision(0,0);
        
    }

void cam::movefirstVision(float x,float y)
    {
        theta+=y;
        fai+=x;
        center.x=10*sin(fai)*cos(theta)+eye.x;
        center.y=10*cos(fai)*cos(theta)+eye.y;
        center.z=10*sin(theta)+eye.z;
        setcam();
        printf("%f %f %f\n",center.x,center.y,center.z );
    }