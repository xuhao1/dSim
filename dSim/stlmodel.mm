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

long getCurrentTime()  
{  
    struct timeval tv;  
    gettimeofday(&tv,NULL);  
    return tv.tv_sec * 1000000 + tv.tv_usec;  
}
void stlmodel::init_stl(std::string filename)
{
    std::ifstream file = std::ifstream(filename);
    string str;
    while (!file.eof())
    {
        file>>str;
        if(str=="loop")
        {
            triangle * temp = new triangle();
            file>>*temp;
            list.push_back(temp); 
        }
    }
    
    resize(0.025);
}


stlmodel::stlmodel(std::string filename,xmodel * x):
 list(0),body(x)
{
    init_stl(filename);
}


void stlmodel::resize(double r)
{
    for(triangle* e:list)
    {
        e->resize(r);
    }
}

GLuint stlmodel::model()
{
    if(maked==1)
        return ptr;
    maked=1;
    //long st=getCurrentTime();
    ptr=glGenLists(1);
    
    glNewList(ptr,GL_COMPILE);
    glBegin(GL_TRIANGLES);
    {
        for(triangle *e:list)
        {
            glColor3f(e->po1.x/1+0.2,e->po1.y/3+0.2,0);
            e->gldraw();
        }
    }
    glEnd();
    glEndList();
    //long ed=getCurrentTime();
    return ptr;
}

void stlmodel::draw()
{
    update_pos();
    glTranslatef(pos.x,pos.y,pos.z);              // 左移 1.5 单位，并移入屏幕 6.0
    glRotatef(angle,ax,ay,az);
    glCallList(model());
    glRotatef(-angle,ax,ay,az);
    glTranslatef(-pos.x,-pos.y,-pos.z);             // 左移 1.5 单位，并移入屏幕 6.0
}

void stlmodel::update_pos()
{
    if (body!=nullptr) {
        body->updatepos();
        pos = body->pos;
        angle = body->angle;
        ax = body->ax;
        ay = body->ay;
        az = body->az;
    }
}

std::istream& operator>>(std::istream& is,vector3f&objects)
{
    string str;
    is>>str;
    is>>objects.x;
    is>>objects.z;
    is>>objects.y;
    objects.z = objects.z + 100;
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

void stlmodel::run()
{
    printf("stl run\n");
}
