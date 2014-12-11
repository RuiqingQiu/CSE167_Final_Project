//
//  Window.cpp
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/7/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "Window.h"
#define PI 3.14159265f

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
float t = 0.0;//A time counter
const float number_of_curves = 3;
Matrix4 Window::world = Matrix4();
/// a structure to hold a control point of the surface
struct Point {
    float x;
    float y;
    float z;
};
Point Points[3][4] ={
    {
        {0,0,5},
        {0,5,5},
        {0,10,5},
        {0,15,5}
    }
,
    {
        { 0,0,20 },
        { 0,0,15},
        { 0,0,10 },
        { 0,0,5 }
    },
    {
        { 10,0,-10 },
        { 10,0,-5},
        { 10,0,15 },
        { 0,0,20 }

    }
   };

Point CalculateU(float t,int row) {
    
    // the final point
    Point p;
    float tmp = t;
    while(t > 1){
        t--;
    }
    //cout << "t is " << t << endl;
    // the t value inverted
    float it = 1.0f-t;
    
    // calculate blending functions
    float b0 = t*t*t;
    float b1 = 3*t*t*it;
    float b2 = 3*t*it*it;
    float b3 =  it*it*it;
    row = int(tmp);
    // sum the effects of the Points and their respective blending functions
    p.x = b0*Points[row][0].x +
		  b1*Points[row][1].x +
		  b2*Points[row][2].x +
		  b3*Points[row][3].x ;
    
    p.y = b0*Points[row][0].y +
		  b1*Points[row][1].y +
		  b2*Points[row][2].y +
		  b3*Points[row][3].y ;
    
    p.z = b0*Points[row][0].z +
		  b1*Points[row][1].z +
		  b2*Points[row][2].z +
		  b3*Points[row][3].z ;
    return p;
}

//------------------------------------------------------------	Calculate()
// On our bezier patch, we need to calculate a set of points
// from the u and v parametric range of 0,0 to 1,1. This calculate
// function performs that evaluation by using the specified u
// and v parametric coordinates.
//
Point Calculate(float t) {
    // calculate each point on our final v curve
    return CalculateU(t,0);
}



void Window::processSpecialKeys(int key, int x, int y){
    //Display ball mode
    if(key == GLUT_KEY_F1){
        glutDisplayFunc(Window::displayPikachu);
        glutIdleFunc(Window::idlePikachu);
    }
    else if(key == GLUT_KEY_F2){
        glutDisplayFunc(Window::displayNyarth);
        glutIdleFunc(Window::idleNyarth);
    }
}

void Window::displayPikachu(void){
    t += 0.01;
    if(t > number_of_curves){
        t = 0;
    }

    Globals::pikachu->getMatrix().identity();
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(-(Globals::pikachu->x_max + Globals::pikachu->x_min)/2, -(Globals::pikachu->y_max + Globals::pikachu->y_min)/2, -(Globals::pikachu->z_max + Globals::pikachu->z_min)/2);
    tmp.print("tranlation matrix");
    cout << "tranlate bunny to origin" << endl;
    Globals::pikachu->getMatrix() =  tmp * Globals::pikachu->getMatrix();
    
    
    //Calculating the bounds for the image display for bunny
    float xMin = float(width)/height * (0 - tan(30 * PI / 180.0) * 20);
    cout << xMin << endl;
    float xMax = float(width)/height * (0 + tan(30 * PI / 180.0) * 20);
    float yMax = 0 + tan(30 * PI / 180.0) * 20;
    cout << yMax << endl;
    float yMin = 0 - tan(30* PI/ 180.0) * 20;
    cout << yMin << endl;
    
    float y_scale = (yMax - yMin) / (Globals::pikachu->y_max - Globals::pikachu->y_min);
    cout << "y scale " << y_scale << endl;
    
    float x_scale = (xMax - xMin) / (Globals::pikachu->x_max - Globals::pikachu->x_min);
    cout << "x scale " << x_scale << endl;
    float zMin = -20;
    float zMax = 20;
    float z_scale = (zMax - zMin)/ (Globals::pikachu->z_max - Globals::pikachu->z_min);
    cout << "z scale " << z_scale << endl;
    
    
    float scale = x_scale;
    if(y_scale < scale){
        scale = y_scale;
    }
    if(z_scale < scale){
        scale = z_scale;
    }
    
    cout << "scale is " << scale << endl;
    tmp.makeScale(0.3*scale, 0.3*scale, 0.3*scale);
    tmp.print("scale matrix");
    Globals::pikachu->getMatrix() =  tmp * Globals::pikachu->getMatrix();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    glEnable(GL_DEPTH_TEST);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    Point tt = Calculate(t);
    
    glPushMatrix();
    glEnable(GL_LIGHTING);
    
    Globals::main_camera->e->x = tt.x;
    Globals::main_camera->e->y = tt.y;
    Globals::main_camera->e->z = tt.z;
    Globals::main_camera->update();
    Matrix4 camera = Globals::main_camera->getMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    
    Matrix4 glmatrix = camera * world * Globals::pikachu->getMatrix();
    
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());
    //gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    cout << "total number of faces: " << Globals::pikachu->face_number << endl;
    for (int i = 0; i < Globals::pikachu->face_number; i++)
    {
        for(int j = 0; j < Globals::pikachu->switch_position.size();j++){
            if(i == Globals::pikachu->switch_position[j]){
                cout << "face number is " << i << endl;
                cout << "bind texture " << Globals::pikachu->material_list[j] << endl;
                glBindTexture(GL_TEXTURE_2D, Globals::pikachu->texture[Globals::pikachu->material_list[j]-1]);
                // Make sure no bytes are padded:
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                
                // Select GL_MODULATE to mix texture with polygon color for shading:
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                
                // Use bilinear interpolation:
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glEnable(GL_TEXTURE_2D);
            }
        }
        Vector4 face_v = Globals::pikachu->face_vertices[i];
        Vector4 face_n = Globals::pikachu->face_normal[i];
        Vector4 face_t = Globals::pikachu->face_texture[i];
        //glColor3f(color_list[face_v.x].x, color_list[face_v.x].y, color_list[face_v.x].z);
        //glNormal3f(Globals::pikachu->normal_list[face_n.x-1].x, Globals::pikachu->normal_list[face_n.x-1].y,Globals::pikachu->normal_list[face_n.x-1].z);
        
       
        glBegin(GL_QUADS);
        glTexCoord2f(Globals::pikachu->texture_coordinates[face_t.x-1].x, Globals::pikachu->texture_coordinates[face_t.y-1].y);
        glNormal3f(Globals::pikachu->normal_list[face_n.x-1].x, Globals::pikachu->normal_list[face_n.x-1].y, Globals::pikachu->normal_list[face_n.x-1].z);
        glVertex3f(Globals::pikachu->x_list[face_v.x-1], Globals::pikachu->y_list[face_v.x-1], Globals::pikachu->z_list[face_v.x-1]);
                   
                   
        //glTexCoord2f(1, 0);
        glTexCoord2f(Globals::pikachu->texture_coordinates[face_t.y-1].x, Globals::pikachu->texture_coordinates[face_t.y-1].y);
        glNormal3f(Globals::pikachu->normal_list[face_n.y-1].x, Globals::pikachu->normal_list[face_n.y-1].y, Globals::pikachu->normal_list[face_n.y-1].z);
        glVertex3f(Globals::pikachu->x_list[face_v.y-1], Globals::pikachu->y_list[face_v.y-1], Globals::pikachu->z_list[face_v.y-1]);
                   
                   
        //glTexCoord2f(1, 1);
        glTexCoord2f(Globals::pikachu->texture_coordinates[face_t.z-1].x, Globals::pikachu->texture_coordinates[face_t.z-1].y);
        glNormal3f(Globals::pikachu->normal_list[face_n.z-1].x, Globals::pikachu->normal_list[face_n.z-1].y, Globals::pikachu->normal_list[face_n.z-1].z);
        glVertex3f(Globals::pikachu->x_list[face_v.z-1], Globals::pikachu->y_list[face_v.z-1], Globals::pikachu->z_list[face_v.z-1]);
                   
                   
        //glTexCoord2f(0, 1);
        glTexCoord2f(Globals::pikachu->texture_coordinates[face_t.w-1].x, Globals::pikachu->texture_coordinates[face_t.w-1].y);
        glNormal3f(Globals::pikachu->normal_list[face_n.w-1].x, Globals::pikachu->normal_list[face_n.w-1].y, Globals::pikachu->normal_list[face_n.w-1].z);
        glVertex3f(Globals::pikachu->x_list[face_v.w-1], Globals::pikachu->y_list[face_v.w-1], Globals::pikachu->z_list[face_v.w-1]);
        glEnd();

    }
    glFlush();
    glutSwapBuffers();
}
void Window::idlePikachu(void){
    displayPikachu();
}


void Window::displayNyarth(void){
    t += 0.01;
    if(t > number_of_curves){
        t = 0;
    }
    
    Globals::nyarth->getMatrix().identity();
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(-(Globals::nyarth->x_max + Globals::nyarth->x_min)/2, -(Globals::nyarth->y_max + Globals::nyarth->y_min)/2, -(Globals::nyarth->z_max + Globals::nyarth->z_min)/2);
    tmp.print("tranlation matrix");
    cout << "tranlate bunny to origin" << endl;
    Globals::nyarth->getMatrix() =  tmp * Globals::nyarth->getMatrix();
    
    
    //Calculating the bounds for the image display for bunny
    float xMin = float(width)/height * (0 - tan(30 * PI / 180.0) * 20);
    cout << xMin << endl;
    float xMax = float(width)/height * (0 + tan(30 * PI / 180.0) * 20);
    float yMax = 0 + tan(30 * PI / 180.0) * 20;
    cout << yMax << endl;
    float yMin = 0 - tan(30* PI/ 180.0) * 20;
    cout << yMin << endl;
    
    float y_scale = (yMax - yMin) / (Globals::nyarth->y_max - Globals::nyarth->y_min);
    cout << "y scale " << y_scale << endl;
    
    float x_scale = (xMax - xMin) / (Globals::nyarth->x_max - Globals::nyarth->x_min);
    cout << "x scale " << x_scale << endl;
    float zMin = -20;
    float zMax = 20;
    float z_scale = (zMax - zMin)/ (Globals::nyarth->z_max - Globals::nyarth->z_min);
    cout << "z scale " << z_scale << endl;
    
    
    float scale = x_scale;
    if(y_scale < scale){
        scale = y_scale;
    }
    if(z_scale < scale){
        scale = z_scale;
    }
    
    cout << "scale is " << scale << endl;
    tmp.makeScale(0.3*scale, 0.3*scale, 0.3*scale);
    tmp.print("scale matrix");
    Globals::nyarth->getMatrix() =  tmp * Globals::nyarth->getMatrix();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    glEnable(GL_DEPTH_TEST);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    Point tt = Calculate(t);
    
    glPushMatrix();
    glEnable(GL_LIGHTING);
    
    Globals::main_camera->e->x = tt.x;
    Globals::main_camera->e->y = tt.y;
    Globals::main_camera->e->z = tt.z;
    Globals::main_camera->update();
    Matrix4 camera = Globals::main_camera->getMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    
    Matrix4 glmatrix = camera * world * Globals::nyarth->getMatrix();
    
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());
    //gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    cout << "total number of faces: " << Globals::nyarth->face_number << endl;
    for (int i = 0; i < Globals::nyarth->face_number; i++)
    {
        for(int j = 0; j < Globals::nyarth->switch_position.size();j++){
            if(i == Globals::nyarth->switch_position[j]){
                cout << "face number is " << i << endl;
                cout << "bind texture " << Globals::nyarth->material_list[j] << endl;
                glBindTexture(GL_TEXTURE_2D, Globals::nyarth->texture[Globals::nyarth->material_list[j]-1]);
                // Make sure no bytes are padded:
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                
                // Select GL_MODULATE to mix texture with polygon color for shading:
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                
                // Use bilinear interpolation:
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glEnable(GL_TEXTURE_2D);
            }
        }
        Vector4 face_v = Globals::nyarth->face_vertices[i];
        Vector4 face_n = Globals::nyarth->face_normal[i];
        Vector4 face_t = Globals::nyarth->face_texture[i];
        //glColor3f(color_list[face_v.x].x, color_list[face_v.x].y, color_list[face_v.x].z);
        //glNormal3f(Globals::pikachu->normal_list[face_n.x-1].x, Globals::pikachu->normal_list[face_n.x-1].y,Globals::pikachu->normal_list[face_n.x-1].z);
        
        
        glBegin(GL_QUADS);
        glTexCoord2f(Globals::nyarth->texture_coordinates[face_t.x-1].x, Globals::nyarth->texture_coordinates[face_t.y-1].y);
        if(Globals::nyarth->normal_list.size() != 0)
            glNormal3f(Globals::nyarth->normal_list[face_n.x-1].x, Globals::nyarth->normal_list[face_n.x-1].y, Globals::nyarth->normal_list[face_n.x-1].z);
        glVertex3f(Globals::nyarth->x_list[face_v.x-1], Globals::nyarth->y_list[face_v.x-1], Globals::nyarth->z_list[face_v.x-1]);
        
        
        //glTexCoord2f(1, 0);
        glTexCoord2f(Globals::nyarth->texture_coordinates[face_t.y-1].x, Globals::nyarth->texture_coordinates[face_t.y-1].y);
        if(Globals::nyarth->normal_list.size() != 0)
            glNormal3f(Globals::nyarth->normal_list[face_n.y-1].x, Globals::nyarth->normal_list[face_n.y-1].y, Globals::nyarth->normal_list[face_n.y-1].z);
        glVertex3f(Globals::nyarth->x_list[face_v.y-1], Globals::nyarth->y_list[face_v.y-1], Globals::nyarth->z_list[face_v.y-1]);
        
        
        //glTexCoord2f(1, 1);
        glTexCoord2f(Globals::nyarth->texture_coordinates[face_t.z-1].x, Globals::nyarth->texture_coordinates[face_t.z-1].y);
        if(Globals::nyarth->normal_list.size() != 0)
            glNormal3f(Globals::nyarth->normal_list[face_n.z-1].x, Globals::nyarth->normal_list[face_n.z-1].y, Globals::nyarth->normal_list[face_n.z-1].z);
        glVertex3f(Globals::nyarth->x_list[face_v.z-1], Globals::nyarth->y_list[face_v.z-1], Globals::nyarth->z_list[face_v.z-1]);
        
        
        //glTexCoord2f(0, 1);
        glTexCoord2f(Globals::nyarth->texture_coordinates[face_t.w-1].x, Globals::nyarth->texture_coordinates[face_t.w-1].y);
        if(Globals::nyarth->normal_list.size() != 0)
            glNormal3f(Globals::nyarth->normal_list[face_n.w-1].x, Globals::nyarth->normal_list[face_n.w-1].y, Globals::nyarth->normal_list[face_n.w-1].z);
        glVertex3f(Globals::nyarth->x_list[face_v.w-1], Globals::nyarth->y_list[face_v.w-1], Globals::nyarth->z_list[face_v.w-1]);
        glEnd();
        
    }
    glFlush();
    glutSwapBuffers();
}
void Window::idleNyarth(void){
    displayNyarth();
}

/**
 * Method for process keyboard actions
 **/
void Window::processNormalKeys(unsigned char key, int x, int y){
    if (key == 27){
        exit(0);
    }
    else if(key == 'r'){
        Matrix4 tmp = Matrix4();
        tmp.makeRotateY(10);
        world = world * tmp;
    }
}
//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    t += 0.01;
    if(t > number_of_curves){
        t = 0;
    }
    //cout << "t is " << t << endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
        // Tell OpenGL what ModelView matrix to use:
    Point tmp = Calculate(t);
    //cout << tmp.x << " " << tmp.y << " " << tmp.z << endl;
    //Put a point at the camera position
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1, 0, 0);
    Matrix4 translate = Matrix4();
    translate.makeTranslate(tmp.x, tmp.y, tmp.z);
    translate = Globals::main_camera->getMatrix() * translate;
    translate.transpose();
    glLoadMatrixd(translate.getPointer());
    glutSolidSphere(1,20,20);
    
    glPopMatrix();
    
    glPushMatrix();
    glEnable(GL_LIGHTING);

    Globals::main_camera->e->x = tmp.x;
    Globals::main_camera->e->y = tmp.y;
    Globals::main_camera->e->z = tmp.z;
    Globals::main_camera->update();
    Matrix4 glmatrix = Globals::main_camera->getMatrix();
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());
    //gluLookAt( tmp.x, tmp.y, tmp.z, 0, 0, 0, 0, 1, 0);
    //gluLookAt(0, -10, 5, 0, 0, 0, 0, 1, 0);
    
        // Draw all six faces of the cube:
        glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue.
        // To change the color of the other faces you will need to repeat this call before each face is drawn.
        // Draw front face:
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(-5.0,  5.0,  5.0);
        glVertex3f( 5.0,  5.0,  5.0);
        glVertex3f( 5.0, -5.0,  5.0);
        glVertex3f(-5.0, -5.0,  5.0);
        
        // Draw left side:
        glColor3f(1.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue.

        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(-5.0,  5.0,  5.0);
        glVertex3f(-5.0,  5.0, -5.0);
        glVertex3f(-5.0, -5.0, -5.0);
        glVertex3f(-5.0, -5.0,  5.0);
        
        // Draw right side:
        glColor3f(1.0, 0.0, 1.0);		// This makes the cube green; the parameters are for red, green and blue.

        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f( 5.0,  5.0,  5.0);
        glVertex3f( 5.0,  5.0, -5.0);
        glVertex3f( 5.0, -5.0, -5.0);
        glVertex3f( 5.0, -5.0,  5.0);
        
        // Draw back face:
        glColor3f(1.0, 0.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue.

        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(-5.0,  5.0, -5.0);
        glVertex3f( 5.0,  5.0, -5.0);
        glVertex3f( 5.0, -5.0, -5.0);
        glVertex3f(-5.0, -5.0, -5.0);
        
        // Draw top side:
        glColor3f(0.0, 0.0, 1.0);		// This makes the cube green; the parameters are for red, green and blue.

        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-5.0,  5.0,  5.0);
        glVertex3f( 5.0,  5.0,  5.0);
        glVertex3f( 5.0,  5.0, -5.0);
        glVertex3f(-5.0,  5.0, -5.0);
        
        // Draw bottom side:
        glColor3f(0.0, 1.0, 1.0);		// This makes the cube green; the parameters are for red, green and blue.

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-5.0, -5.0, -5.0);
        glVertex3f( 5.0, -5.0, -5.0);
        glVertex3f( 5.0, -5.0,  5.0);
        glVertex3f(-5.0, -5.0,  5.0);
        glEnd();
        glFlush();
    glPopMatrix();
        glutSwapBuffers();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    cout << w << ", " << h << endl;
        cerr << "Window::reshapeCallback called" << endl;
        width = w;
        height = h;
        //static bool first = true;
        glViewport(0, 0, w, h);  // set new viewport size
        //if(first){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0);// set perspective projection viewing frustum
        //first = false;
        //}
        glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
    glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
   displayCallback();
}

