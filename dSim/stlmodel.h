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

class stlmodel:public xmodel
{
public:
    bool maked;
    GLint ptr;
    std::vector<triangle> list;
    stlmodel();
    stlmodel(std::string filename,physx::PxPhysics *pp,physx::PxScene *ms);
    stlmodel(std::string filename,PhysEngine *pe);
    GLuint model();
    void resize(double r);
    void draw();
    void init_stl(std::string filename);
   
    virtual void run();
    
  
};

#endif /* defined(__test__processstd__) */