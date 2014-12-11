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
#include "Model3D.h"

using namespace std;

namespace Globals
{
    Model* pikachu;
    Camera* main_camera;
    Model* nyarth;
};


GLint loc;
GLuint v,f,f2,p;
Model3D *pika;

void display(void)
{
    //Window::Point tt = Window::Calculate(t);
    
    //Globals::main_camera->e->x = tt.x;
    //Globals::main_camera->e->y = tt.y;
    //Globals::main_camera->e->z = tt.z;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    // Tell OpenGL what ModelView matrix to use:
    Matrix4 glmatrix;
    glmatrix.identity();
    Matrix4 scale;
    scale.makeScale(5, 5, 5);
    glmatrix = glmatrix*scale;
    Matrix4 pos = pika -> localpos;
    Matrix4 rot = Matrix4();
    rot.makeRotateY(1);
    pika->localpos = pika->localpos*rot;
    glmatrix = glmatrix*pos;
    glmatrix.transpose();
    Matrix4 camera = Globals::main_camera->getMatrix();
    //Globals::main_camera->update();
    //glmatrix =camera * glmatrix;
    glLoadMatrixd(glmatrix.getPointer());
    
    pika->draw();
    
    glFlush();
    glutSwapBuffers();
}


void idle(void)
{
    display();
}

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
    //Globals::pikachu = new Model();
    Globals::nyarth = new Model();
    //load_model_pikachu();
    //load_model_nyarth();/Users/Ennuma/Desktop/CSE167_Final_Project/Pikachu.obj
    pika = new Model3D("/Users/Ennuma/Desktop/CSE167_Final_Project/Pikachu.obj");
    // Install callback functions:
    //glutDisplayFunc(Window::displayCallback);
    glutReshapeFunc(Window::reshapeCallback);
    //glutIdleFunc(Window::idleCallback);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    //glutDisplayFunc(Window::displayPikachu);
    //glutIdleFunc(Window::idlePikachu);
    
    //glutDisplayFunc(Window::displayNyarth);
    //glutIdleFunc(Window::idleNyarth);
    
    glutSpecialFunc(Window::processSpecialKeys);
    glutKeyboardFunc(Window::processNormalKeys);
    Window::world.identity();
   
    Globals::main_camera = new Camera();
    

    //Shader
//    Globals::s = new Shader("","", true);
//    Globals::s->bind();
//    Globals::s->printLog("hello");
    glutMainLoop();
    return 0;
}

void load_model_pikachu(){
    FILE* fp;     // file pointer
    float x,y,z;  // vertex coordinates
    float a,b,c,d,e,f,g,h,i,j,k,l;
    float w, v;
    int c1,c2;    // characters read from file
    int mat_number;
    Globals::pikachu->face_number = 0;
    Globals::pikachu->x_list.clear();
    Globals::pikachu->y_list.clear();
    Globals::pikachu->z_list.clear();
    Globals::pikachu->normal_list.clear();
    Globals::pikachu->face_vertices.clear();
    Globals::pikachu->face_normal.clear();
    Globals::pikachu->material_list.clear();
    char texture_file_name[80];
    Globals::pikachu->texture_num = 0;
    //Loading material file/Users/Ennuma/Desktop/CSE167_Final_Project/Pikachu.mtl
    fp = fopen("/Users/Ennuma/Desktop/CSE167_Final_Project/Pikachu.mtl","r");
    if (fp==NULL) { cerr << "error loading file" << endl; exit(-1); }
    while(true){
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if(c1 == 'n' && c2 == 'e'){
            fscanf(fp, "wmtl mat%d", &mat_number);
        }
        else if(c1 == 'm' && c2 == 'a'){
            fscanf(fp,"p_Kd Textures\\%s", texture_file_name);
            cout << texture_file_name << endl;
            
            char file_path[80];
            strcpy (file_path,"/Users/Ennuma/Desktop/CSE167_Final_Project/");
            strcat(file_path,texture_file_name);
            
            printf("filepath is : %s\n",file_path);
            Globals::pikachu->texture[Globals::pikachu->texture_num] = SOIL_load_OGL_texture
            (
             file_path
             ,
             SOIL_LOAD_AUTO,
             SOIL_CREATE_NEW_ID,
             SOIL_FLAG_INVERT_Y
             );
            if(Globals::pikachu->texture[Globals::pikachu->texture_num] == 0)
            {
                printf("SOIL loading error: '%s'\n", SOIL_last_result());
            }
            Globals::pikachu->texture_num++;

        }
        else{
            fscanf(fp, "\n");
        }
        if(feof(fp)){
            break;
        }
    }
    fp = fopen("/Users/Ennuma/Desktop/CSE167_Final_Project/Pikachu.obj","r");
    if (fp==NULL) { cerr << "error loading file" << endl; exit(-1); }
    while(true){
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if((c1=='v') && (c2 == ' ')){
            fscanf(fp, "%f %f %f \n", &x, &y, &z);
            //fscanf(fp, "%f %f %f\n", &x, &y, &z);
            Globals::pikachu->x_list.push_back(x);
            Globals::pikachu->y_list.push_back(y);
            Globals::pikachu->z_list.push_back(z);
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
            fscanf(fp, "%f/%f/%f %f/%f/%f %f/%f/%f %f/%f/%f\n", &a, &b, &c,
                                                                &d, &e, &f,
                                                                &g, &h, &i,
                                                                &j, &k, &l);
            //fscanf(fp, "%f %f %f\n", &x, &y, &z);
            Globals::pikachu->face_vertices.push_back(Vector4(a,d,g,j));
            Globals::pikachu->face_texture.push_back(Vector4(b,e,h,k));
            Globals::pikachu->face_normal.push_back(Vector4(c,f,i,l));
            Globals::pikachu->face_number++;
        }
        //Different material texture to use
        else if(c1 == 'u' && c2 == 's'){
            fscanf(fp, "emtl mat%d\n", &mat_number);
            Globals::pikachu->material_list.push_back(mat_number);
            Globals::pikachu->switch_position.push_back(Globals::pikachu->face_vertices.size());
            cout << "switch position is " << Globals::pikachu->face_vertices.size() << endl;
            cout << mat_number << endl;
        }
        else if(c1 == 'v' && c2 == 't'){
            fscanf(fp, " %f %f\n", &x, &y);
            Globals::pikachu->texture_coordinates.push_back(Vector3(x,y,0));
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

void load_model_nyarth(){
    FILE* fp;     // file pointer
    float x,y,z;  // vertex coordinates
    float a,b,c,d,e,f,g,h,i,j,k,l;
    float w, v;
    int c1,c2;    // characters read from file
    int mat_number;
    Globals::nyarth->face_number = 0;
    Globals::nyarth->x_list.clear();
    Globals::nyarth->y_list.clear();
    Globals::nyarth->z_list.clear();
    Globals::nyarth->normal_list.clear();
    Globals::nyarth->face_vertices.clear();
    Globals::nyarth->face_normal.clear();
    Globals::nyarth->material_list.clear();
    char texture_file_name[80];
    Globals::nyarth->texture_num = 0;
    //Loading material file
    fp = fopen("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/BR_Mewtwo.mtl","r");
    if (fp==NULL) { cerr << "error loading file" << endl; exit(-1); }
    while(true){
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if(c1 == 'n' && c2 == 'e'){
            fscanf(fp, "wmtl mat%d", &mat_number);
        }
        else if(c1 == 'm' && c2 == 'a'){
            fscanf(fp,"p_Kd Textures\\%s", texture_file_name);
            cout << texture_file_name << endl;
            
            char file_path[80];
            strcpy (file_path,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/");
            strcat(file_path,texture_file_name);
            Globals::nyarth->texture[Globals::pikachu->texture_num] = SOIL_load_OGL_texture
            (
             file_path
             ,
             SOIL_LOAD_AUTO,
             SOIL_CREATE_NEW_ID,
             SOIL_FLAG_INVERT_Y
             );
            if(Globals::nyarth->texture[Globals::pikachu->texture_num] == 0)
            {
                printf("SOIL loading error: '%s'\n", SOIL_last_result());
            }
            Globals::nyarth->texture_num++;
            
        }
        else{
            fscanf(fp, "\n");
        }
        if(feof(fp)){
            break;
        }
    }
    fp = fopen("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/BR_Mewtwo.obj","r");
    if (fp==NULL) { cerr << "error loading file" << endl; exit(-1); }
    while(true){
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if((c1=='v') && (c2 == ' ')){
            fscanf(fp, "%f %f %f \n", &x, &y, &z);
            //fscanf(fp, "%f %f %f\n", &x, &y, &z);
            Globals::nyarth->x_list.push_back(x);
            Globals::nyarth->y_list.push_back(y);
            Globals::nyarth->z_list.push_back(z);
            if(x > Globals::nyarth->x_max){
                Globals::nyarth->x_max = x;
            }
            if(x < Globals::nyarth->x_min){
                Globals::nyarth->x_min = x;
            }
            if(y > Globals::nyarth->y_max){
                Globals::nyarth->y_max = y;
            }
            if(y < Globals::nyarth->y_min){
                Globals::nyarth->y_min = y;
            }if(z > Globals::nyarth->z_max){
                Globals::nyarth->z_max = z;
            }
            if(z < Globals::nyarth->z_min){
                Globals::nyarth->z_min = z;
            }
        }
        else if(c1=='v' && c2 =='n'){
            fscanf(fp, " %f %f %f\n", &x, &y, &z);
            Vector3 normal = Vector3(x, y, z);
            normal.normalize();
            Globals::nyarth->normal_list.push_back(normal);
        }
        else if(c1 == 'f' && c2==' '){
            fscanf(fp, "%f/%f %f/%f %f/%f\n", &a, &b, &c,
                   &d, &e, &f);
            //fscanf(fp, "%f %f %f\n", &x, &y, &z);
            Globals::nyarth->face_vertices.push_back(Vector4(a,c,e,0));
            Globals::nyarth->face_texture.push_back(Vector4(b,d,k,0));
            Globals::nyarth->face_number++;
        }
        //Different material texture to use
        else if(c1 == 'u' && c2 == 's'){
            fscanf(fp, "emtl mat%d\n", &mat_number);
            Globals::nyarth->material_list.push_back(mat_number);
            Globals::nyarth->switch_position.push_back(Globals::nyarth->face_vertices.size());
            cout << "switch position is " << Globals::nyarth->face_vertices.size() << endl;
            cout << mat_number << endl;
        }
        else if(c1 == 'v' && c2 == 't'){
            fscanf(fp, " %f %f\n", &x, &y);
            Globals::nyarth->texture_coordinates.push_back(Vector3(x,y,0));
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
