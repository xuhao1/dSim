//
//  processstd.h
//  test
//
//  Created by XuHao on 14-4-13.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#ifndef __test__processstd__
#define __test__processstd__

#include <iostream>
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include "vector3f.h"
#include <vector>
class triangle
{
public:
    vector3f po1,po2,po3;
    triangle(vector3f _po1,vector3f _po2,vector3f _po3):
        po1(_po1),po2(_po2),po3(_po3)
    {
    }
    triangle()
    {}
    void resize(double r)
    {
        po1=po1*r;
        po2=po2*r;
        po3=po3*r;
    }
    void gldraw()
    {
        glVertex3f(po1.x,po1.y,po1.z);
        glVertex3f(po2.x,po2.y,po2.z);
        glVertex3f(po3.x,po3.y,po3.z);
    }
};
std::istream& operator>>(std::istream& is,triangle&objects);
std::istream& operator>>(std::istream& is,vector3f&objects);
class stlmodel
{
public:
    bool maked;
    GLuint ptr;
    std::vector<triangle> list;
    stlmodel(char*filename);
    GLuint model();
    void resize(double r);
    void draw();
    void setPos(float x,float y)
    {
        pos.x=x;
        pos.y=y;
    }
    vector3f pos;
};

#endif /* defined(__test__processstd__) */
