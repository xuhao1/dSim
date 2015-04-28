# dSim 

## Introduction
This is a high performance physics simulation program for drones, wrote in objective-cpp, base on mavlink OpenGL and PhysX.

## Hardware in Loop

Support Hardware in Loop for simulate for pixhawk,still have problem on position control,attitude control is OK

## Dynamics Support

You can write equations in mathematica and export them to c headers,easy use in this program, I finish the helicopter control simulation base on this.

## GUI
The GUI now is wrote in OpenGL, I have a branch wrote in Unreal communicate with this program by Mavlink is still under developing, hoping someone who know well about game program for helping.

You may use the Mavlink to connect the program with other programs. And after trying to connect with DJI sdks, I will release the version with full unreal 3D engine support. 


##Computer Vision

The next step I will do is export screen capture realtime to OpenCV for realtime computer vision, it will be finish in the middle May after my General Relativity test.