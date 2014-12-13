//
//  Window.h
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/7/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167_Final_Project__Window__
#define __CSE167_Final_Project__Window__

#include <stdio.h>
#include <GLUT/GLUT.h>
#include "Matrix4.h"
#include "main.h"
#include "SOIL.h"

extern "C" void stopPlaying();
//extern "C" void replay();


class Window	  // OpenGL output window related routines
{
public:
    static int width, height; 	            // window size
    static Matrix4 world;
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void processSpecialKeys(int key, int x, int y);
    static void processNormalKeys(unsigned char key, int x, int y);
    
    static void displayParticle(void);
    static void updateParticle(int);
    
    static void displayPikachu(void);
    static void idlePikachu(void);
    
};
#endif /* defined(__CSE167_Final_Project__Window__) */
