//
//  Text.h
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/17/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167_Final_Project__Text__
#define __CSE167_Final_Project__Text__

#include <iostream>
#include <stdlib.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include "text3d.h"

using namespace std;
class Text{
public:
    float _angle = -30.0f;
    float _scale;
    //The four strings that are drawn
    const char* STRS[4] = {"Voice", "Of", "Pokemon", "Competition"};
    //Computes a scaling value so that the strings
    float computeScale(const char* strs[4]);
    
    void cleanup();
    
    void initRendering();
    
    void drawScene();
};
#endif /* defined(__CSE167_Final_Project__Text__) */
