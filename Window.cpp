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
    }
}
void Window::displayPikachu(void){
    t += 0.01;
    if(t > number_of_curves){
        t = 0;
    }
    Point tt = Calculate(t);
    Globals::main_camera->e->x = tt.x;
    Globals::main_camera->e->y = tt.y;
    Globals::main_camera->e->z = tt.z;
    Globals::main_camera->update();
    Matrix4 camera = Globals::main_camera->getMatrix();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    // Tell OpenGL what ModelView matrix to use:
    Matrix4 glmatrix;
    glmatrix.identity();
    Matrix4 scale;
    scale.makeScale(10, 10, 10);
    glmatrix = glmatrix*scale;
    Matrix4 pos = Globals::pika -> localpos;
    //Matrix4 rot = Matrix4();
    //rot.makeRotateY(1);
    Globals::pika->localpos = Globals::pika->localpos;
    glmatrix = camera*glmatrix*pos;
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());

    Globals::pika->draw();
    
    glFlush();
    glutSwapBuffers();
}
void Window::idlePikachu(void){
    displayPikachu();
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

