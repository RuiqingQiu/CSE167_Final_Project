//
//  Window.cpp
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/7/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "Window.h"
#include "Sound.h"

#define PI 3.14159265f

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
float t = 0.0;//A time counter
const float number_of_curves = 6;
Matrix4 Window::world = Matrix4();
/// a structure to hold a control point of the surface
struct Point {
    float x;
    float y;
    float z;
};
Point Points[6][4] ={
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
        {15,0,5},
        {10,0,7},
        {5,0,13},
        {0,0,20}
    },
    {
        { 0,0,-25 },
        { 5,0,-13},
        { 10,0,-7 },
        { 15,0,5 }

    },
    {
        {-5,0,-15},
        {0,0,-15},
        {5,0,-15},
        {0,0,-25}
    },
    {
        {0,15,5},
        {0,10,0},
        {0,5,-10},
        {-5,0,-15}
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


void draw_scene(){
    Point tt = Calculate(t);
    Globals::main_camera->e->x = tt.x;
    Globals::main_camera->e->y = tt.y;
    Globals::main_camera->e->z = tt.z;
    Globals::main_camera->update();
    Matrix4 camera = Globals::main_camera->getMatrix();
    Matrix4 scale;
    scale.makeScale(10, 10, 10);
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    Matrix4 glmatrix;
    glmatrix.identity();
    // Tell OpenGL what ModelView matrix to use:
    if(Globals::secondCameraOn){
        Globals::second_camera->e->x = 5;
        Globals::second_camera->e->y = 5;
        Globals::second_camera->e->z = 10;
        Globals::second_camera->update();
        camera = Globals::second_camera->getMatrix();
    }
    
    //camera.identity();
    
    glEnable(GL_LIGHTING);
    Matrix4 tmp;
    tmp.makeTranslate(tt.x, tt.y, tt.z);
    glmatrix = camera*glmatrix*tmp;
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();
    
    glDisable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);

    //glBegin(GL_QUADS);
    glPushMatrix();
    glmatrix.identity();
    Matrix4 trans2;
    trans2.makeTranslate(-150, -5, -100);
    Matrix4 scale2;
    scale2.makeScale(0.2, 0.2, 0.2);
    scale2.identity();
    glmatrix = camera * glmatrix * scale2*trans2;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    glBegin( GL_QUADS );
    //glColor3b(1,1,1);
    for (int i = 0;  i < Globals::terrain->getWidth()-1 ; i++) {
        for (int j = 0 ; j < Globals::terrain->getWidth()-1; j++) {
            float h1 =Globals::terrain->getData(i, j);
            float h2 =Globals::terrain->getData(i+1, j);
            float h3 =Globals::terrain->getData(i+1, j+1);
            float h4 =Globals::terrain->getData(i, j+1);
            Vector3 v1 = Vector3(i,j,h1);
            Vector3 v2 = Vector3(i+1,j,h2);
            Vector3 v3 = Vector3(i,j+1,h4);
            Vector3 n1 = v2-v1;
            Vector3 n2 = v3 -v1;
            Vector3 n = n1.cross(n1, n2);
            
            glColor3f(1-h2/3, 1, 1-h2/3);
            glNormal3f( -n.x,-n.y,-n.z );
            glVertex3f(i, h1, j);
            //glNormal3f( 0,0,1 );
            glVertex3f((i+1),h2, j);
            //glNormal3f( 0,0,1 );
            glVertex3f((i+1),h3, (j+1));
            //glNormal3f( 0,0,1 );
            glVertex3f(i, h4,(j+1));
            
            //printf("x %i,y %i, height %f\n",i,j,h1);
        }
    }
    glColor3f(1, 1, 1);

    /**
    glNormal3f(0, 1, 0);
    glVertex3f(-2, -3.5, -2);
    glVertex3f(2, -3.5, -2);
    glVertex3f(2, -3.5, 2);
    glVertex3f(-2, -3.5, 2);
     **/
    glEnd();
    glPopMatrix();
    
    glEnable(GL_CULL_FACE);
    glmatrix.identity();
    Matrix4 pos = Globals::pika -> localpos;
    Globals::pika->localpos = Globals::pika->localpos;
    Matrix4 trans = Matrix4();
    trans.makeTranslate(0, 0, -30);
    Matrix4 rot = Matrix4();
    glmatrix = camera*glmatrix*trans*scale*pos;
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::pika->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans.makeTranslate(-10, -1, -10);
    //If it's equal to 180
    if (Globals::bulbasaur->turned && Globals::bulbasaur->angle == 180.0){
        rot.makeRotateY(Globals::bulbasaur->angle);
        trans = trans * rot;
    }
    //Turn back
    else if(!Globals::bulbasaur->turned && Globals::bulbasaur->angle >= 180.0){
        rot.makeRotateY(Globals::bulbasaur->angle);
        trans = trans * rot;
        Globals::bulbasaur->angle += 1.0;
        if(Globals::bulbasaur->angle == 360.0){
            Globals::bulbasaur->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::bulbasaur->turned && Globals::bulbasaur->angle != 180.0){
        rot.makeRotateY(Globals::bulbasaur->angle);
        trans = trans * rot;
        Globals::bulbasaur->angle += 1.0;
    }
    
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::bulbasaur->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans = Matrix4();
    trans.makeTranslate(0, 0, -10);
    //If it's equal to 180
    if (Globals::charmander->turned && Globals::charmander->angle == 180.0){
        rot.makeRotateY(Globals::charmander->angle);
        trans = trans * rot;
    }
    //Turn back
    else if(!Globals::charmander->turned && Globals::charmander->angle >= 180.0){
        rot.makeRotateY(Globals::charmander->angle);
        trans = trans * rot;
        Globals::charmander->angle += 1.0;
        if(Globals::charmander->angle == 360.0){
            Globals::charmander->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::charmander->turned && Globals::charmander->angle != 180.0){
        rot.makeRotateY(Globals::charmander->angle);
        trans = trans * rot;
        Globals::charmander->angle += 1.0;
    }
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::charmander->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    
    trans = Matrix4();
    trans.makeTranslate(8, 0, -10);
    //If it's equal to 180
    if (Globals::meowth->turned && Globals::meowth->angle == 180.0){
        rot.makeRotateY(Globals::meowth->angle);
        trans = trans * rot;
    }
    //Turn back
    else if(!Globals::meowth->turned && Globals::meowth->angle >= 180.0){
        rot.makeRotateY(Globals::meowth->angle);
        trans = trans * rot;
        Globals::meowth->angle += 1.0;
        if(Globals::meowth->angle == 360.0){
            Globals::meowth->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::meowth->turned && Globals::meowth->angle != 180.0){
        rot.makeRotateY(Globals::meowth->angle);
        trans = trans * rot;
        Globals::meowth->angle += 1.0;
    }
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    
    Globals::meowth->draw();
    
    
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans = Matrix4();
    trans.makeTranslate(15, -1, -9);
    //If it's equal to 180
    if (Globals::Snorlax->turned && Globals::Snorlax->angle == 180.0){
        rot.makeRotateY(Globals::Snorlax->angle);
        trans = trans * rot;
    }
    //Turn back
    else if(!Globals::Snorlax->turned && Globals::Snorlax->angle >= 180.0){
        rot.makeRotateY(Globals::Snorlax->angle);
        trans = trans * rot;
        Globals::Snorlax->angle += 1.0;
        if(Globals::Snorlax->angle == 360.0){
            Globals::Snorlax->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::Snorlax->turned && Globals::Snorlax->angle != 180.0){
        rot.makeRotateY(Globals::Snorlax->angle);
        trans = trans * rot;
        Globals::Snorlax->angle += 1.0;
    }
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::Snorlax->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans = Matrix4();
    trans.makeTranslate(-8, 0, -30);
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::psyduck->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans = Matrix4();
    trans.makeTranslate(8, -1, -30);
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::vulpix->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans = Matrix4();
    trans.makeTranslate(15, -1, -30);
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::Eevee->draw();
    
    
    
    //Particle effect
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    trans = Matrix4();
    trans.makeTranslate(0, 30, -15);
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    if(Globals::particle_effect_on){
        glDisable(GL_CULL_FACE);
        Globals::particle_engine->advance(t*25 / 1000.0f);
        Globals::particle_engine->draw();
    }
    
    
}
void Window::displayPikachu(void){
    clock_t startTime = clock();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers

    t += 0.01;
    if(t > number_of_curves){
        t = 0;
    }
    draw_scene();
    glFlush();
    glutSwapBuffers();
    glColor4f(1, 1, 1, 1);
    clock_t endTime = clock();
    //cout << "frame rate: " << 1.0/(float((endTime - startTime))/CLOCKS_PER_SEC) << endl;
}
void Window::idlePikachu(void){
  displayPikachu();
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
void Window::processSpecialKeys(int key, int x, int y){
    //Display ball mode
    if(key == GLUT_KEY_F1){
        //glEnable(GL_CULL_FACE);
        glutDisplayFunc(Window::displayPikachu);
        glutIdleFunc(Window::idlePikachu);
    }
    //Particle system
    else if(key == GLUT_KEY_F2){
        Globals::particle_effect_on = !Globals::particle_effect_on;
    }
    else if (key == GLUT_KEY_F3){
        //shadow_set_up();
    }
}
/**
 * Method for process keyboard actions
 **/
void Window::processNormalKeys(unsigned char key, int x, int y){
    if (key == 27){
        exit(0);
    }
    
    //Music controller
    //Key 1 for second camera look at bezier curve
    else if(key == '1'){
        Globals::secondCameraOn = !Globals::secondCameraOn;
        t = 0;
        //stop playing the music
    }else if(key == '2'){
        stopPlaying();
        //playing justin biber baby
    }else if(key == '3'){
        stopPlaying();
        char *tmp[4];
        play(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/BabyCutted.wav");
//        play(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/BabyCutted.wav");
        //play(0, tmp,"/Users/Ennuma/Desktop/CSE167_Final_Project/BabyCutted.wav");
    }
    //playing let it go
    else if(key == '4'){
        stopPlaying();
        char *tmp[4];
        play(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/LetItGoCutted.wav");
        //play(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/LetItGoCutted.wav");
        //play(0, tmp,"/Users/Ennuma/Desktop/CSE167_Final_Project/LetItGoCutted.wav");

    }
    //playing let it go
    else if(key == '5'){
        stopPlaying();
        char *tmp[4];
        play(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/RoarCutted.wav");
        //play(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/RoarCutted.wav");
        //play(0, tmp,"/Users/Ennuma/Desktop/CSE167_Final_Project/RoarCutted.wav");

    }
    
    //Motion controller
    else if(key == 'q'){
        if(Globals::bulbasaur->angle == 0.0)
            Globals::bulbasaur->turned = true;
        if(Globals::bulbasaur->angle == 180.0){
            Globals::bulbasaur->turned = false;
        }
    }
    else if (key =='w'){
        if(Globals::charmander->angle == 0.0)
            Globals::charmander->turned = true;
        if(Globals::charmander->angle == 180.0){
            Globals::charmander->turned = false;
        }
    }
    else if (key == 'e'){
        if(Globals::meowth->angle == 0.0)
            Globals::meowth->turned = true;
        if(Globals::meowth->angle == 180.0){
            Globals::meowth->turned = false;
        }
    }
    else if (key == 'r'){
        if(Globals::Snorlax->angle == 0.0)
            Globals::Snorlax->turned = true;
        if(Globals::Snorlax->angle == 180.0){
            Globals::Snorlax->turned = false;
        }
        
    }
}


