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
#include "SOIL.h"

using namespace std;

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
};


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
    Globals::pika = new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Pikachu.obj");
    Globals::bulbasaur = new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Bulbasaur.obj");
    Globals::charmander= new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Charmander.obj");
    Globals::vulpix= new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Vulpix.obj");
    Globals::meowth = new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Meowth.obj");
    Globals::psyduck = new Model3D("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Psyduck.obj");
    
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
    

    //Shader
//    Globals::s = new Shader("","", true);
//    Globals::s->bind();
//    Globals::s->printLog("hello");
    glutMainLoop();
    return 0;
}
