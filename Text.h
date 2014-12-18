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
    float _scale;
    //The four strings that are drawn
    const char* title[4] = {"Voice", "Of", "Pokemon", "Competition"};
    const char* song1[4] = {"Superheroes", "By", "The", "Script"};
    const char* song2[4] = {"Baby", "By", "Justin", "Bieber"};
    const char* song3[5] = {"Let", "It", "Go", "From", "Frozen"};
    const char* song4[4] = {"Roar", "By", "Katy", "Perry"};

    

    //Computes a scaling value so that the strings
    float computeScale(const char* strs[4]);
    
    void cleanup();
    
    void initRendering();
    
    void drawTitle();
};
#endif /* defined(__CSE167_Final_Project__Text__) */
