//
//  processstd.cpp
//  test
//
//  Created by XuHao on 14-4-13.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#include "stlmodel.h"
#include <fstream>
#include <string>
#include <sys/time.h>    
#include <iostream>

using namespace std;

long getCurrentTime()  
{  
    struct timeval tv;  
    gettimeofday(&tv,NULL);  
    return tv.tv_sec * 1000000 + tv.tv_usec;  
}

stlmodel::stlmodel(char*filepath,physx::PxRigidDynamic* actor):
    list(0),xmodel(actor)
{
    std::ifstream file=std::ifstream(filepath);
    string str;
    while (!file.eof())
    {
        file>>str;
        if(str=="loop")
        {
            triangle temp;
            file>>temp;
            list.push_back(temp); 
        }
    }
    
    resize(0.01);
}
void stlmodel::resize(double r)
{
    for(triangle &e:list)
    {
        e.resize(r);
    }
}
GLuint stlmodel::model()
{
    if(maked==1)
        return ptr;
    maked=1;
    long st=getCurrentTime();
    ptr=glGenLists(1);
    glNewList(ptr,GL_COMPILE);
    glBegin(GL_TRIANGLES);
    {
        for(triangle e:list)
        {
            glColor3f(e.po1.x/1+0.2,e.po1.z/3+0.2,e.po1.y*2+0.2);
            e.gldraw();
        }
    }
    glEnd();
    glEndList();
    long ed=getCurrentTime();
    return ptr;
}
void stlmodel::draw()
{
    updatepos();
    //printf("li:%f %f %f\n",pos.x,pos.y,pos.z );
    glTranslatef(pos.x,pos.y,pos.z);              // 左移 1.5 单位，并移入屏幕 6.0
    glRotatef(angle,ax,ay,az);
    glCallList(model());
    glRotatef(-angle,ax,ay,az);
    glTranslatef(-pos.x,-pos.y,-pos.z);             // 左移 1.5 单位，并移入屏幕 6.0
}
std::istream& operator>>(std::istream& is,vector3f&objects)
{
    string str;
    is>>str;
    is>>objects.x;
    is>>objects.y;
    is>>objects.z;
    return is;
}
std::istream& operator>>(std::istream& is,triangle&objects)
{
    is>>objects.po1;
    is>>objects.po2;
    is>>objects.po3;
    string str;
    is>>str;
    return is;
}