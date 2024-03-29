//
//  Sound.h
//  CSE167 Final Project
//
//  Created by Mingshan Wang on 12/12/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167_Final_Project__Sound__
#define __CSE167_Final_Project__Sound__

#include <iostream>
#include <stdio.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <OpenGL/gl.h>
#include <OPengl/glu.h>
#include <GLUT/GLUT.h>

extern int play(int, char **, char* filepath);
extern int playApplause(int, char **, char* filepath);
extern int playTurnback(int, char **, char* filepath);
extern void stopPlaying();
extern int playBoo(int, char **, char* filepath);




#endif /* defined(__CSE167_Final_Project__Sound__) */
