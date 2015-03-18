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
#include "cam.h"

@implementation MyOpenGl
{
    std::vector<stlmodel*> objs;
    double rad;
    cam* cam0;
}

- (void) drawObjects
{
    //glEnable();
    glMatrixMode (GL_MODELVIEW);
    
    //AUX_RGBImageRec *TextureImage[1];
   // memset(TextureImage,0,sizeof(void *)*1);
    
    //TextureImage[0]=LoadBMP("Data/NeHe.bmp")
    
    glBegin(GL_POLYGON);
    {
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(-100,-100,0);
        glVertex3f(-100,100,0);
        glVertex3f(100,100,0);
        glVertex3f(100,-100,0);
    }
    glEnd();
    for(stlmodel *plane:objs)
    {
        plane->draw();
    }
}

//(0, 0, 0, 0, 0,-1, 0, 1, 0);
- (void)prepareOpenGL
{
    NSLog(@"u");
    rad=20;
    cam0=new cam( -rad,0,5,0,0,5,0,0,1);
    NSLog(@"this");
    glMatrixMode (GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    gluPerspective(40,1.33333,0.01,1000);
    cam0->setcam();
}
-(void)addObj:(stlmodel*)model
{
    objs.push_back(model);
    NSLog(@"Add Successful:%lu\n",objs.size());
}

- (void) setcam
{
    cam0->setcam();
}


- (void)drawRect:(NSRect) dirtyRect
{
    //glLoadIdentity ();
    //xro+=omega;
    //cam.eyeZ+=zro;
    [self setcam];
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    [self drawObjects];
    glFlush();
}
-(void)eyeOri:(unichar)c
{
    printf("here\n");
    switch (c) {
            
        case 'w':
            cam0->movefirstVision(0,0.02);
            break;
        case 's':
            cam0->movefirstVision(0,-0.02);
            break;
        case 'a':
            cam0->movefirstVision(-0.02,0);
            break;
        case 'd':
            cam0->movefirstVision(0.02,0);
            break;
        case NSLeftArrowFunctionKey:
            cam0->moveEve(0, -1, 0);
            break;
        case NSRightArrowFunctionKey:
            cam0->moveEve(0, 1, 0);
            break;
        case NSUpArrowFunctionKey:
            cam0->moveEve(1, 0, 0);
            break;
        case NSDownArrowFunctionKey:
            cam0->moveEve(-1, 0, 0);
            break;
            
        case NSHomeFunctionKey:
            cam0->moveEve(0, 0, 0.5);
            break;
            
        case NSEndFunctionKey:
            cam0->moveEve(0, 0, -0.5);
            break;
        default:
            break;
    }
}

@end

