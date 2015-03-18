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
#include <vector>

#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include "vector3f.h"
#include "phys_model.h"
#include "PhysEngine.h"
#include <string>

class triangle;

std::istream& operator>>(std::istream& is,triangle&objects);

std::istream& operator>>(std::istream& is,vector3f&objects);

class stlmodel
{
public:
    xmodel * body;
    bool maked;
    GLint ptr;
    std::vector<triangle*> list;
    
    ///> position
    vector3f pos;
    
    ///>  angle of quat
    double angle,
    ///>  ax
    ax,
    ///>  ay
    ay,
    ///>  az
    az;
    
    
    stlmodel(std::string filename,xmodel *x);
    
    GLuint model();
    
    void resize(double r);
    void draw();
    void init_stl(std::string filename);
    
    ///\brief 更新位置坐标
    void update_pos();
   
    virtual void run();
};

#endif /* defined(__test__processstd__) */