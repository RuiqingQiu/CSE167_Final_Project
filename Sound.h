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

#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

class Sound{
    public :
     //ALuint buffers[NUM_BUFFERS];
     //ALuint source[NUM_SOURCES];
        ALuint bufferID;
        ALuint sourceID;

        void* data;
        int format;
        int sampleRate;
        int size;
    
    Sound(int format,int sampleRate,void* data,int size);
    static Sound* loadWAVE(const char* filename);
    void play();

};

#endif /* defined(__CSE167_Final_Project__Sound__) */
