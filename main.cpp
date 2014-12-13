//
//  main.cpp
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/7/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GLUT/glut.h>
#include <OpenAL/alc.h>
#include <OpenAL/al.h>
#include <CoreGraphics/CoreGraphics.h>
#include "SOIL.h"

using namespace std;

#define NUM_BUFFERS 3
#define BUFFER_SIZE 4096

namespace Globals
{
    Camera* main_camera;
    Camera* second_camera;

    
    Model3D *pika;
    Model3D* bulbasaur;
    Model3D* charmander;
    Model3D* vulpix;
    Model3D* meowth;
    Model3D* psyduck;
    bool secondCameraOn = false;
    //Particle System
    ParticleEngine* particle_engine;
    Sound* sound;
};

const int TIMER_MS = 25; //The number of milliseconds to which the timer is set

int main(int argc, char *argv[])
{
    float specular[]  = {1.0, 1.0, 1.0, 1.0};
    float shininess[] = {100.0};
    
    glutInit(&argc, argv);      	      	      // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(Window::width, Window::height);      // set initial window size
    glutCreateWindow("CSE 167 Final Project");    	      // open window and set window title
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);             	      // set shading to smooth
    glMatrixMode(GL_PROJECTION);
    
    // Generate material properties:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_NORMALIZE);
    
    // Generate light source:
    float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
       //pika = new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Pikachu.obj");
      //pika = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Pikachu.obj");
    Globals::pika = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Pikachu.obj");
    Globals::bulbasaur = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Bulbasaur.obj");
    Globals::charmander= new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Charmander.obj");
    Globals::vulpix= new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Vulpix.obj");
    Globals::meowth = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Meowth.obj");
    Globals::psyduck = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Psyduck.obj");
    
    // Install callback functions:
    //glutDisplayFunc(Window::displayCallback);
    glutReshapeFunc(Window::reshapeCallback);
    //glutIdleFunc(Window::idleCallback);
    glutDisplayFunc(Window::displayPikachu);
    glutIdleFunc(Window::idlePikachu);
    
    glutSpecialFunc(Window::processSpecialKeys);
    glutKeyboardFunc(Window::processNormalKeys);
    Window::world.identity();
   
    Globals::main_camera = new Camera();
    Globals::second_camera = new Camera();
    
    //Init particle engine texture
    GLuint textureID = ParticleEngine::initRendering();
    //Create the particle engine
    Globals::particle_engine = new ParticleEngine(textureID);
    
    Globals::sound = Globals::sound->loadWAVE("/Users/margaretwm3/Dropbox/CSE167_Final_Project/BR_Pikachu.wav");
    Globals::sound->play();
    
    //Shader
    //Globals::s = new Shader("","", true);
    //Globals::s->bind();
    //Globals::s->printLog("hello");
    
    
    /*
    //openAL stuff
    ALCdevice *dev;
    ALCcontext *ctx;
    //struct stat statbuf;
    
    ALuint buffer[NUM_BUFFERS];
    //ALuint source[NUM_SOURCES];
    
    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    
    // Initialization
    dev = alcOpenDevice(NULL); // select the "preferred dev"
    
    if(!dev){
        cout << "Could not set up OpenAL devices " << endl;
        return 1;
    }
    ctx = alcCreateContext(dev,NULL);
    alcMakeContextCurrent(ctx);
   */ 
    
   /*
    
    // Check for EAX 2.0 support
    // g_bEAX = alIsExtensionPresent("EAX2.0");
    
    // Generate Buffers
    alGetError(); // clear error code
    alGenBuffers(NUM_BUFFERS, buffer);
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        DisplayALError("alGenBuffers :", error);
        return 1;
    }
    // Load test.wav
    loadWAVFile("sample.wav", &format, &data, &size, &freq, &loop);
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        DisplayALError("LoadWAVFile sample.wav : ", error);
        alDeleteBuffers(NUM_BUFFERS, buffer);
        return 1;
    }
    
    // Copy test.wav data into AL Buffer 0
    alBufferData(buffer[0], format, data, size, freq);
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        DisplayALError("alBufferData buffer 0 : ", error);
        alDeleteBuffers(NUM_BUFFERS, buffer);
        return 1;
    }
    
    // Unload test.wav
    unloadWAV(format, data, size, freq);
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        DisplayALError("UnloadWAV : ", error);
        alDeleteBuffers(NUM_BUFFERS, buffer);
        return 1;
    }
    // Generate Sources
    alGenSources(1, source);
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        DisplayALError("alGenSources 1 : ", error);
        return 1;
    }
    // Attach buffer 0 to source
    alSourcei(source[0], AL_BUFFER, buffer[0]);
    if ((error = alGetError()) != AL_NO_ERROR)
    {
        DisplayALError("alSourcei AL_BUFFER 0 : ", error);
    }
    
    // Exit
    ctx = alcGetCurrentContext();
    dev = alcGetContextsDevice(ctx);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(dev);
     */
     
    glutMainLoop();
   return 0;
}
