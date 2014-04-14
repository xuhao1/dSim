//
//  MyOpenGl.m
//  test
//
//  Created by XuHao on 14-4-11.
//  Copyright (c) 2014年 xuhao. All rights reserved.
//

#import "MyOpenGl.h"
#include <OpenGL/gl.h>
#include <OPenGL/glu.h>
#include <GLKit/GLKMath.h>
#include "stlmodel.h"
#include <vector>
#include "vector3f.h"

@implementation MyOpenGl
{
    struct camera
    {
        double    eyeX;
        double    eyeY;
        double    eyeZ;
        double    centerX;
        double    centerY;
        double    centerZ;
        double    upX;
        double    upY;
        double    upZ;
    } cam;
    std::vector<stlmodel*> objs;
    double rad;
}

- (void) drawAnObject
{
    glEnable(GL_POLYGON_STIPPLE);
    glMatrixMode (GL_MODELVIEW);
    for(stlmodel plane:objs)
    {
        printf("pl%f %f\n",plane->pos.x,plane->pos.y);
        plane.draw();
    }
}

//(0, 0, 0, 0, 0,-1, 0, 1, 0);
- (void)prepareOpenGL
{
    NSLog(@"u");
    rad=5;
    cam.eyeX=rad;
    cam.eyeY=rad;
    cam.eyeZ=2;
    cam.centerX=0;
    cam.centerY=0;
    cam.centerZ=-5;
    cam.upX=0;
    cam.upY=0;
    cam.upZ=1;
    objx=0;
    objy=0;
    
    NSLog(@"this");
    //[self setcam];
    glMatrixMode (GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    gluPerspective(40,1.33333,0.01,1000);
    glMatrixMode (GL_MODELVIEW);
    gluLookAt(2, 2, 2, 0, 0,0, 0, 0, 1);
    [self mkBox];
}
-(void) addObj:(stlmodel*)model
{
    objs.push_back(model);
    NSLog(@"Add Successful:%i\n",objs.size());

}

- (void) setcam
{
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
        gluLookAt(cam.eyeX, cam.eyeY, cam.eyeZ, cam.centerX, cam.centerY,cam.centerZ, cam.upX, cam.upY, cam.upZ);
}
-(void)eyeMove:(NSPoint)u;
{
    cam.eyeX=u.x/100.0f+rad;
    cam.eyeY=u.y/100.0f+rad;
    cam.centerX=cam.eyeX-rad;
    cam.centerY=cam.eyeY-rad;
}

- (void)drawRect:(NSRect) dirtyRect
{
    //glLoadIdentity ();
    //xro+=omega;
    //cam.eyeZ+=zro;
    [self setcam];
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    [self drawAnObject];
    glFlush();
}
/*
-(void)objmove:(char)c
{
    switch (c) {
        case 'w':
            objy+=3;
            break;
        case 's':
            objy-=3;
            break;
        case 'a':
            objx+=3;
            break;
        case 'd':
            objx-=3;
            break;
        default:
            break;
    }
}
-(void) mkBox
{
    box=glGenLists(1);
    glNewList(box,GL_COMPILE);
    glBegin(GL_QUADS);
    {
        glColor3f(0.0f,1.0f,0.0f);          // 颜色改为蓝色
        glVertex3f( 1.0f, 1.0f,-1.0f);          // 四边形的右上顶点 (顶面)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // 四边形的左上顶点 (顶面)
        glVertex3f(-1.0f, 1.0f, 1.0f);          // 四边形的左下顶点 (顶面)
        glVertex3f( 1.0f, 1.0f, 1.0f);          // 四边形的右下顶点 (顶面)
        
        glColor3f(1.0f,0.5f,0.0f);          // 颜色改成橙色
        glVertex3f( 1.0f,-1.0f, 1.0f);          // 四边形的右上顶点(底面)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // 四边形的左上顶点(底面)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // 四边形的左下顶点(底面)
        glVertex3f( 1.0f,-1.0f,-1.0f);
        
        glColor3f(1.0f,0.0f,0.0f);          // 颜色改成红色
        glVertex3f( 1.0f, 1.0f, 1.0f);          // 四边形的右上顶点(前面)
        glVertex3f(-1.0f, 1.0f, 1.0f);          // 四边形的左上顶点(前面)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // 四边形的左下顶点(前面)
        glVertex3f( 1.0f,-1.0f, 1.0f);
        glColor3f(1.0f,1.0f,0.0f);          // 颜色改成黄色
        glVertex3f( 1.0f,-1.0f,-1.0f);          // 四边形的右上顶点(后面)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // 四边形的左上顶点(后面)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // 四边形的左下顶点(后面)
        glVertex3f( 1.0f, 1.0f,-1.0f);          // 四边形的右下顶点(后面)
        glColor3f(0.0f,0.0f,1.0f);          // 颜色改成蓝色
        glVertex3f(-1.0f, 1.0f, 1.0f);          // 四边形的右上顶点(左面)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // 四边形的左上顶点(左面)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // 四边形的左下顶点(左面)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // 四边形的右下顶点(左面)
        
        glColor3f(1.0f,0.0f,1.0f);          // 颜色改成紫罗兰色
        glVertex3f( 1.0f, 1.0f,-1.0f);          // 四边形的右上顶点(右面)
        glVertex3f( 1.0f, 1.0f, 1.0f);          // 四边形的左上顶点(右面)
        glVertex3f( 1.0f,-1.0f, 1.0f);          // 四边形的左下顶点(右面)
        glVertex3f( 1.0f,-1.0f,-1.0f);          // 四边形的右下顶点(右面)
        
    }
    glEnd();
    glEndList();
}
*/
@end

