//
//  main.h
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/7/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167_Final_Project__main__
#define __CSE167_Final_Project__main__

#include <stdio.h>
#include "Window.h"
#include "Model.h"
#include "Camera.h"
#include "Model3D.h"
#include <OpenAL/alc.h>
#include <OpenAL/al.h>
#include "ParticleEngine.h"
#include "Terrain.h"
#include "L_System.h"
#include "Text.h"
#include "SpotLight.h"
extern "C" int play(int, char **,char* filePath);
extern "C" int playApplause(int, char **,char* filePath);
extern "C" int playBoo(int, char **,char* filePath);
extern "C" int playTurnback(int, char **, char* filepath);


namespace Globals
{
    extern Camera* main_camera;
    extern Camera* second_camera;
    //These are the Models we use
    extern Model3D *pika;
    extern Model3D* bulbasaur;
    extern Model3D* charmander;
    extern Model3D* vulpix;
    extern Model3D* meowth;
    extern Model3D* psyduck;
    extern Model3D* Eevee;
    extern Model3D* Snorlax;
    
    //These will be the flag we use for keyboard controls:
    extern bool secondCameraOn;
    extern bool particle_effect_on;
    
    //Particle System
    extern ParticleEngine* particle_engine;
    
    //Terrain
    extern Terrain1* terrain;
    
    extern L_System* l_system;
    
    extern Text* text;
    
    extern SpotLight* spotlight;
};
#endif /* defined(__CSE167_Final_Project__main__) */
