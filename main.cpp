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

using namespace std;

namespace Globals
{
    Model* pikachu;
    Camera* main_camera;
};


GLint loc;
GLuint v,f,f2,p;

int main(int argc, char *argv[])
{
    float specular[]  = {1.0, 1.0, 1.0, 1.0};
    float shininess[] = {100.0};
    
    glutInit(&argc, argv);      	      	      // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(Window::width, Window::height);      // set initial window size
    glutCreateWindow("OpenGL Cube");    	      // open window and set window title
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
    
    // Install callback functions:
    glutDisplayFunc(Window::displayCallback);
    glutReshapeFunc(Window::reshapeCallback);
    glutIdleFunc(Window::idleCallback);

    
    glutSpecialFunc(Window::processSpecialKeys);
    glutKeyboardFunc(Window::processNormalKeys);
    
    Globals::pikachu = new Model();
    Globals::main_camera = new Camera();
    
    load_model();
    //Shader
//    Globals::s = new Shader("","", true);
//    Globals::s->bind();
//    Globals::s->printLog("hello");
    glutMainLoop();
    return 0;
}

void load_model(){
    FILE* fp;     // file pointer
    float x,y,z;  // vertex coordinates
    float r,g,b;  // vertex color
    int c1,c2;    // characters read from file
    
    fp = fopen("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Pikachu.obj","r");
    if (fp==NULL) { cerr << "error loading file" << endl; exit(-1); }
    while(true){
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if((c1=='v') && (c2 == ' ')){
            fscanf(fp, "%f %f %f %f %f %f\n", &x, &y, &z, &r, &g, &b);
            //fscanf(fp, "%f %f %f\n", &x, &y, &z);
            Globals::pikachu->x_list.push_back(x);
            Globals::pikachu->y_list.push_back(y);
            Globals::pikachu->z_list.push_back(z);
            Globals::pikachu->color_list.push_back(Vector3(r, g, b));
            if(x > Globals::pikachu->x_max){
                Globals::pikachu->x_max = x;
            }
            if(x < Globals::pikachu->x_min){
                Globals::pikachu->x_min = x;
            }
            if(y > Globals::pikachu->y_max){
                Globals::pikachu->y_max = y;
            }
            if(y < Globals::pikachu->y_min){
                Globals::pikachu->y_min = y;
            }if(z > Globals::pikachu->z_max){
                Globals::pikachu->z_max = z;
            }
            if(z < Globals::pikachu->z_min){
                Globals::pikachu->z_min = z;
            }
            
        }
        else if(c1=='v' && c2 =='n'){
            fscanf(fp, " %f %f %f\n", &x, &y, &z);
            Vector3 normal = Vector3(x, y, z);
            normal.normalize();
            Globals::pikachu->normal_list.push_back(normal);
        }
        else if(c1 == 'f' && c2==' '){
            fscanf(fp, "%f//%f %f//%f %f//%f\n", &x, &y, &z, &r, &g, &b);
            //fscanf(fp, "%f %f %f\n", &x, &y, &z);
            
            Globals::pikachu->face_vertices.push_back(Vector3(x, z, g));
            Globals::pikachu->face_normal.push_back(Vector3(y,r,b));
            Globals::pikachu->face_number++;
        }
        else{
            fscanf(fp, "\n");
        }
        if(feof(fp)){
            break;
        }
    }
    // parse other cases and loop over lines of file
    fclose(fp);   // make sure you don't forget to close the file when done
}
