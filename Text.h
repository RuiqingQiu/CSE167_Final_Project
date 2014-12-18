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
    const char* song1[4] = {"Superheroes", "By", "The", "Psyduck"};
    const char* song2[4] = {"Baby", "By", "Justin", "Pikachu"};
    const char* song3[5] = {"Let", "It", "Go From", "Vulpix"};
    const char* song4[4] = {"Roar", "By", "Katy", "Eevee"};

    int song = 0; //0 title, 1 song1, 2 song2, 3 song3, 4 song4

    //Computes a scaling value so that the strings
    float computeScale(const char* strs[4]);
    
    void cleanup();
    
    void initRendering();
    
    void drawTitle();
    
    void drawSong1();
    void drawSong2();

    void drawSong3();
    void drawSong4();
    void draw();


    
};
#endif /* defined(__CSE167_Final_Project__Text__) */
