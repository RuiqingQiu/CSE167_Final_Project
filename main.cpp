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
    bool camera_line_on = false;
    //Particle System
    ParticleEngine* particle_engine;
    //Terrain
    Terrain1* terrain;
    L_System* l_system;
    L_System* l_system1;
    L_System* l_system2;
    Text* text;

    SpotLight* spotlight;
    float tree[50];
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
    //glEnable(GL_LIGHT0);
    
    float spotposition[]  = {0.0, 1.0, 0.0, 0.0};	// lightsource position
    GLfloat  ambientLight[] = { 1.0f, 1, 1, 1.0f};
    GLfloat  dir[] = { 0.0f, -1.0f, 0.0f, 1.0f};
    // The light is composed of just diffuse and specular components
    /**
    glLightfv(GL_LIGHT2,GL_DIFFUSE,ambientLight);
    glLightfv(GL_LIGHT2,GL_SPECULAR,specular);
    //glLightfv(GL_LIGHT2,GL_POSITION,spotposition);
    
    // Specific spot effects
    // Cut off angle is 60 degrees
    glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,1.0f);
    
    // Fairly shiny spot
    glLightf(GL_LIGHT2,GL_SPOT_EXPONENT,10.0f);
    //glEnable(GL_LIGHTING);
    
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 2.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
    
    glLightfv(GL_LIGHT2,GL_POSITION,spotposition);
    glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,dir);
    
    glEnable(GL_LIGHT2);
     **/
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    
    Globals::spotlight = new SpotLight();
    Globals::spotlight->position = Vector3(0, 10, 20);
    Globals::spotlight->dir = Vector3(0,1,0);
    Globals::spotlight->diffuse = Vector3(1.0f,0.0f, 0.0f);
    Globals::spotlight->specular = Vector3(1, 1, 1);
    Globals::spotlight->ambient = Vector3(0.1, 0.1, 0.1);
    Globals::spotlight->target= 4;

    
    Globals::spotlight->apply();
    Globals::spotlight->enable();
       //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
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
    //play(argc, argv,"/Users/Ennuma/Desktop/CSE167_Final_Project/Superheroes.wav");

    
    
    //Gen Terrain
    Globals::terrain = new Terrain1(200);
    int seed = time(0);
    seed = 1000;
#warning param is seed, displace, roughness, smooth(0-1)
    Globals::terrain->generate(seed, 100, 2, 0.3);
    
    Globals::l_system = new L_System();
    Globals::l_system->trees = new vector<string>();
    for(int i = 0; i <= Globals::l_system->DEPTH; i++){
        Globals::l_system->expand(0);
    }
    
    Globals::l_system1 = new L_System();
    Globals::l_system1->DEPTH = 6;
    Globals::l_system1->depth = 6;
    Globals::l_system1->lineWidth = 0.1;
    Globals::l_system1->incr = 0.01;


    Globals::l_system1->trees = new vector<string>();
    for(int i = 0; i <= Globals::l_system1->DEPTH; i++){
        Globals::l_system1->expand1((float)rand()/RAND_MAX);
    }
    
    Globals::l_system2 = new L_System();
    Globals::l_system2->DEPTH = 5;
    Globals::l_system2->depth = 5;
    Globals::l_system2->lineWidth = 0.1;
    Globals::l_system2->incr = 0.01;
    
    
    Globals::l_system2->trees = new vector<string>();
    for(int i = 0; i <= Globals::l_system2->DEPTH; i++){
        Globals::l_system2->expand2((float)rand()/RAND_MAX);
    }

    Globals::text = new Text();
    //printf("height is %f\n", Globals::terrain->getData(0, 0));
    //printf("height is %f\n", Globals::terrain->getHeightMap()[0]);
    Globals::text->initRendering();
    
    Globals::text->_scale = Globals::text->computeScale(Globals::text->title);
    Window::LoadGLTextures();
    srand( time(0));
    for (int i = 0; i<sizeof(Globals::tree)/sizeof(float);  i++) {
        Globals::tree[i] = (float)rand() / ((float)RAND_MAX + 1);
    }
    glutMainLoop();
    
    return 0;
}
