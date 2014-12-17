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
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdbool.h>


#include <GLUT/glut.h>
#include <OpenAL/alc.h>
#include <OpenAL/al.h>
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
    Model3D* Eevee;
    Model3D* Snorlax;
    bool secondCameraOn = false;
    bool particle_effect_on = false;
    //Particle System
    ParticleEngine* particle_engine;
    //Terrain
    Terrain1* terrain;
    L_System* l_system;

};

const int TIMER_MS = 25; //The number of milliseconds to which the timer is set

int main(int argc, char *argv[])
{
    
    float specular[]  = {1.0, 1.0, 1.0, 1.0};
    float shininess[] = {100.0};
    
    glutInit(&argc, argv);      	      	      // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(Window::width, Window::height);      // set initial window size
    glutCreateWindow("CSE 167 Final Project");    	      // open window and set window title
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);             	      // set shading to smooth
    glMatrixMode(GL_PROJECTION);
    
    // Generate material properties:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    
    // Generate light source:
    float position[]  = {0.0, 10.0, 0.0, 0.0};	// lightsource position
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
       //pika = new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Pikachu.obj");
    
//    Globals::pika = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Pikachu.obj");
//    Globals::bulbasaur = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Bulbasaur.obj");
//    Globals::charmander= new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Charmander.obj");
//    Globals::vulpix= new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Vulpix.obj");
//    Globals::meowth = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Meowth.obj");
//    Globals::psyduck = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Psyduck.obj");
//    Globals::Eevee = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Eevee.obj");
//    Globals::Snorlax = new Model3D("/Users/margaretwm3/Dropbox/CSE167_Final_Project/Snorlax.obj");
//
    Globals::pika = new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Pikachu.obj");
    Globals::bulbasaur = new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Bulbasaur.obj");
    Globals::charmander= new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Charmander.obj");
    Globals::vulpix= new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Vulpix.obj");
    Globals::meowth = new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Meowth.obj");
    Globals::psyduck = new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Psyduck.obj");
    Globals::Eevee = new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Eevee.obj");
    Globals::Snorlax = new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Snorlax.obj");
   
//        Globals::pika = new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Pikachu.obj");
//        Globals::bulbasaur = new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Bulbasaur.obj");
//        Globals::charmander= new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Charmander.obj");
//        Globals::vulpix= new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Vulpix.obj");
//        Globals::meowth = new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Meowth.obj");
//        Globals::psyduck = new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Psyduck.obj");
//        Globals::Eevee = new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Eevee.obj");
//        Globals::Snorlax = new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Snorlax.obj");

    // Install callback functions:
    glutDisplayFunc(Window::displayPikachu);
    glutIdleFunc(Window::idlePikachu);
    glutReshapeFunc(Window::reshapeCallback);
    
    
    //Window::shadow_set_up();//Uncomment this line if you want the screen effect for shadow mapping

    
    glutSpecialFunc(Window::processSpecialKeys);
    glutKeyboardFunc(Window::processNormalKeys);
    Window::world.identity();
   
    Globals::main_camera = new Camera();
    Globals::second_camera = new Camera();
    
    //Init particle engine texture
    GLuint textureID = ParticleEngine::initRendering();
    //Create the particle engine
    Globals::particle_engine = new ParticleEngine(textureID);
    
    //play(argc, argv,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/Superheroes.wav");
    play(argc, argv,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Superheroes.wav");

    
    //Gen Terrain
    Globals::terrain = new Terrain1(200);
    int seed = time(0);
    
#warning param is seed, displace, roughness, smooth(0-1)
    Globals::terrain->generate(seed, 100, 2, 0.3);
    
    Globals::l_system = new L_System();
    Globals::l_system->trees = new vector<string>();
    for(int i = 0; i <= Globals::l_system->DEPTH; i++){
        Globals::l_system->expand(0);
    }
    //printf("height is %f\n", Globals::terrain->getData(0, 0));
    //printf("height is %f\n", Globals::terrain->getHeightMap()[0]);

    glutMainLoop();
    
    return 0;
}
