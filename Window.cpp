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
const float number_of_curves = 5;
Matrix4 Window::world = Matrix4();
float distance_to_camera = 20;
/// a structure to hold a control point of the surface
struct Point {
    float x;
    float y;
    float z;
};
Point Points[5][4] ={
    {
        {0,2,25},
        {0,2,35},
        {0,2,45},
        {0,2,60}
    }
,
    {
        { 30,2,-5 },
        { 30,2,10},
        { 15,2,25},
        { 0,2,25 }
    },
    {
        {0,2,-35},
        {15,2,-35},
        {30,2,-20},
        {30,2,-5}
    },
    {
        { -30,2,-5},
        { -30,2,-20},
        { -15,2,-35 },
        { 0,2,-35 }

    },
    {
        {0,2,25},
        {-15,2,25},
        {-30,2,10},
        {-30,2,-5}
    }
   };
GLuint texture[5];

int Window::LoadGLTextures(){
    texture[0] = SOIL_load_OGL_texture
    (
     "/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/nightsky_north.bmp"
     //"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/()airFT.tga"
     ,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
    if(texture[0] == 0)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        return false;
    }
    texture[1] = SOIL_load_OGL_texture
    (
     "/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/nightsky_south.bmp"
     //"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/()airBK.tga"
     ,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
    if(texture[1] == 0)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        return false;
    }
    
    texture[2] = SOIL_load_OGL_texture
    (
     "/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/nightsky_west.bmp"
     //"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/()airRT.tga"
     ,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
    if(texture[2] == 0)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        return false;
    }
    
    texture[3] = SOIL_load_OGL_texture
    (
     "/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/nightsky_east.bmp"
     //"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/()airLT.tga"
     ,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
    if(texture[3] == 0)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        return false;
    }
    
    texture[4] = SOIL_load_OGL_texture
    (
     "/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/()airUP.tga"
     ,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
    if(texture[4] == 0)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        return false;
    }
    
    /*
     glBindTexture(GL_TEXTURE_2D, texture[0]);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     */
    return true;
}

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
    row = int(tmp)%5;
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
    //cout << "here" << endl;
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    glLoadIdentity();
    Matrix4 camera;
    if(Globals::secondCameraOn){
        Globals::second_camera->e->x = 0;
        Globals::second_camera->e->y = 100;
        Globals::second_camera->e->z = 100;
        Globals::second_camera->update();
        camera = Globals::second_camera->getMatrix();
        camera.transpose();
        glLoadMatrixd(camera.getPointer());
    }
    if(Globals::camera_line_on){
        glBegin(GL_POINTS);
        for(int i = 0; i < 5; i++){
            for(int j = 1; j < 300; j++){
                Point tt = Calculate(1.0/300*j+i);
                glVertex3f(tt.x,tt.y,tt.z);

            }
        }
        glEnd();
    }
    Point tt = Calculate(t);
    Globals::main_camera->e->x = tt.x;
    Globals::main_camera->e->y = tt.y;
    Globals::main_camera->e->z = tt.z;
    Globals::main_camera->update();
    camera = Globals::main_camera->getMatrix();
    Matrix4 scale;
    scale.makeScale(10, 10, 10);
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    Matrix4 glmatrix;
    glmatrix.identity();
    // Tell OpenGL what ModelView matrix to use:
    if(Globals::secondCameraOn){
        Globals::second_camera->e->x = 0;
        Globals::second_camera->e->y = 100;
        Globals::second_camera->e->z = 100;
        Globals::second_camera->update();
        camera = Globals::second_camera->getMatrix();
    }
    
    //camera.identity();
    
    glEnable(GL_LIGHTING);
    glDisable(GL_LIGHT1);
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
    //glBegin(GL_QUADS);
    glPushMatrix();
    glmatrix.identity();
    Matrix4 trans2;
    trans2.makeTranslate(-100, -5, -100);
    Matrix4 scale2;
    scale2.makeScale(0.2, 0.2, 0.2);
    scale2.identity();
    glmatrix = camera * glmatrix * scale2*trans2;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::terrain->draw();
    glPopMatrix();

    glDisable(GL_LIGHTING);
    float size_of_texture_cube = 150;
    glPushMatrix();
    glmatrix.identity();
    scale2.identity();
    trans2.identity();
    glmatrix = camera * glmatrix * scale2*trans2;
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());

    glEnable(GL_TEXTURE_2D);
    //glActiveTexture(GL_TEXTURE1);
    
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Use bilinear interpolation:
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glTexCoord2f(0, 0); glVertex3f( size_of_texture_cube,-size_of_texture_cube,size_of_texture_cube );
    glTexCoord2f(1, 0); glVertex3f(-size_of_texture_cube,-size_of_texture_cube,size_of_texture_cube);
    glTexCoord2f(1, 1); glVertex3f( -size_of_texture_cube, size_of_texture_cube,size_of_texture_cube); //back up right
    glTexCoord2f(0, 1); glVertex3f(  size_of_texture_cube,size_of_texture_cube, size_of_texture_cube ); //back up left
    glEnd();
    
    //Front[0]
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Use bilinear interpolation:
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(  -size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
    glTexCoord2f(1, 0); glVertex3f( size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
    glTexCoord2f(1, 1); glVertex3f( size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube);   //up right
    glTexCoord2f(0, 1); glVertex3f(  -size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //up left
    glEnd();
    
    //Left[2]
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Use bilinear interpolation:
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(  -size_of_texture_cube, -size_of_texture_cube, size_of_texture_cube);
    glTexCoord2f(1, 0); glVertex3f( -size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
    glTexCoord2f(1, 1); glVertex3f( -size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //up
    glTexCoord2f(0, 1); glVertex3f(  -size_of_texture_cube, size_of_texture_cube, size_of_texture_cube); //up
    glEnd();
    
    
    //Right[3]
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Use bilinear interpolation:
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f( size_of_texture_cube, -size_of_texture_cube, -size_of_texture_cube);
    glTexCoord2f(1, 0); glVertex3f( size_of_texture_cube, -size_of_texture_cube, size_of_texture_cube);
    glTexCoord2f(1, 1); glVertex3f( size_of_texture_cube, size_of_texture_cube, size_of_texture_cube);
    glTexCoord2f(0, 1); glVertex3f( size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube);
    glEnd();
    
    //Top[4]
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Use bilinear interpolation:
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0, 1); glVertex3f( -size_of_texture_cube, size_of_texture_cube, size_of_texture_cube); //connect to back up left
    glTexCoord2f(0, 0); glVertex3f( -size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //connect to front up left
    glTexCoord2f(1, 0); glVertex3f( size_of_texture_cube, size_of_texture_cube, -size_of_texture_cube); //connect to front up right
    glTexCoord2f(1, 1); glVertex3f( size_of_texture_cube, size_of_texture_cube, size_of_texture_cube);  //connect to back right
    
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();

    

    glEnable(GL_LIGHTING);

    glEnable(GL_CULL_FACE);
    glmatrix.identity();
    Matrix4 pos = Globals::pika -> localpos;
    Globals::pika->localpos = Globals::pika->localpos;
    Matrix4 trans = Matrix4();
    trans.makeTranslate(-5, 0, -40+distance_to_camera);
    Matrix4 rot = Matrix4();
    rot.makeRotateY(180);
    trans = trans * rot;
    
    //If it's equal to 180 (which means it's turned around completely)
    if (Globals::pika->turned && Globals::pika->angle == 180.0){
        rot.makeRotateY(Globals::pika->angle);
        Matrix4 tmp = Matrix4();
        if(Globals::pika->distance < 8){
            tmp.makeTranslate(0, 0, -Globals::pika->distance);
            Globals::pika->distance+=0.5;
        }
        else{
            tmp.makeTranslate(0, 0, -Globals::pika->distance);
            if (Globals::spotlight->target==1) {
                Globals::spotlight->on =1 ;
            }else{
                //Globals::spotlight->on =0 ;
            }
        }
        trans = trans * tmp* rot;
    }
    //Turn back
    else if(!Globals::pika->turned && Globals::pika->angle >= 180.0){
        Matrix4 tmp = Matrix4();
        tmp.makeTranslate(0, 0, -Globals::pika->distance);
        rot.makeRotateY(Globals::pika->angle);
        trans = trans * tmp * rot;
        Globals::pika->angle += 5.0;
        if(Globals::pika->angle == 360.0){
            Globals::pika->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::pika->turned && Globals::pika->angle != 180.0){
        rot.makeRotateY(Globals::pika->angle);
        trans = trans * rot;
        Globals::pika->angle += 5.0;
    }
    else if(!Globals::pika->turned && Globals::pika->distance > 0){
        Matrix4 tmp = Matrix4();
        tmp.makeTranslate(0, 0, -Globals::pika->distance);
        Globals::pika->distance-=0.5;
        trans = trans * tmp;
    }
    
    glmatrix = camera*glmatrix*trans*scale*pos;
    glmatrix.transpose();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::pika->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans.makeTranslate(-15, -1, -10+distance_to_camera);
    //If it's equal to 180
    if (Globals::bulbasaur->turned && Globals::bulbasaur->angle == 180.0){
        rot.makeRotateY(Globals::bulbasaur->angle);
        trans = trans * rot;
    }
    //Turn back
    else if(!Globals::bulbasaur->turned && Globals::bulbasaur->angle >= 180.0){
        rot.makeRotateY(Globals::bulbasaur->angle);
        trans = trans * rot;
        Globals::bulbasaur->angle += 5.0;
        if(Globals::bulbasaur->angle == 360.0){
            Globals::bulbasaur->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::bulbasaur->turned && Globals::bulbasaur->angle != 180.0){
        rot.makeRotateY(Globals::bulbasaur->angle);
        trans = trans * rot;
        Globals::bulbasaur->angle += 5.0;
    }
    
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::bulbasaur->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans = Matrix4();
    trans.makeTranslate(-5, 0, -10+distance_to_camera);
    //If it's equal to 180
    if (Globals::charmander->turned && Globals::charmander->angle == 180.0){
        rot.makeRotateY(Globals::charmander->angle);
        trans = trans * rot;
    }
    //Turn back
    else if(!Globals::charmander->turned && Globals::charmander->angle >= 180.0){
        rot.makeRotateY(Globals::charmander->angle);
        trans = trans * rot;
        Globals::charmander->angle += 5.0;
        if(Globals::charmander->angle == 360.0){
            Globals::charmander->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::charmander->turned && Globals::charmander->angle != 180.0){
        rot.makeRotateY(Globals::charmander->angle);
        trans = trans * rot;
        Globals::charmander->angle += 5.0;
    }
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::charmander->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    
    trans = Matrix4();
    trans.makeTranslate(5, 0, -10+distance_to_camera);
    //If it's equal to 180
    if (Globals::meowth->turned && Globals::meowth->angle == 180.0){
        rot.makeRotateY(Globals::meowth->angle);
        trans = trans * rot;
    }
    //Turn back
    else if(!Globals::meowth->turned && Globals::meowth->angle >= 180.0){
        rot.makeRotateY(Globals::meowth->angle);
        trans = trans * rot;
        Globals::meowth->angle += 5.0;
        if(Globals::meowth->angle == 360.0){
            Globals::meowth->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::meowth->turned && Globals::meowth->angle != 180.0){
        rot.makeRotateY(Globals::meowth->angle);
        trans = trans * rot;
        Globals::meowth->angle += 5.0;
    }
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    
    Globals::meowth->draw();
    
    
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans = Matrix4();
    trans.makeTranslate(15, -1, -9+distance_to_camera);
    //If it's equal to 180
    if (Globals::Snorlax->turned && Globals::Snorlax->angle == 180.0){
        rot.makeRotateY(Globals::Snorlax->angle);
        trans = trans * rot;
    }
    //Turn back
    else if(!Globals::Snorlax->turned && Globals::Snorlax->angle >= 180.0){
        rot.makeRotateY(Globals::Snorlax->angle);
        trans = trans * rot;
        Globals::Snorlax->angle += 5.0;
        if(Globals::Snorlax->angle == 360.0){
            Globals::Snorlax->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::Snorlax->turned && Globals::Snorlax->angle != 180.0){
        rot.makeRotateY(Globals::Snorlax->angle);
        trans = trans * rot;
        Globals::Snorlax->angle += 5.0;
    }
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::Snorlax->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans = Matrix4();
    trans.makeTranslate(-15, 0, -40+distance_to_camera);
    rot.makeRotateY(180);
    trans = trans * rot;
    //If it's equal to 180 (which means it's turned around completely)
    if (Globals::psyduck->turned && Globals::psyduck->angle == 180.0){
        rot.makeRotateY(Globals::psyduck->angle);
        Matrix4 tmp = Matrix4();
        if(Globals::psyduck->distance < 8){
            tmp.makeTranslate(0, 0, -Globals::psyduck->distance);
            Globals::psyduck->distance+=0.5;
        }
        else{
            tmp.makeTranslate(0, 0, -Globals::psyduck->distance);
            if (Globals::spotlight->target==0) {
                Globals::spotlight->on =1 ;
            }else{
                //Globals::spotlight->on =0 ;
            }

        }
        trans = trans * tmp* rot;
        
    }
    //Turn back
    else if(!Globals::psyduck->turned && Globals::psyduck->angle >= 180.0){
        Matrix4 tmp = Matrix4();
        tmp.makeTranslate(0, 0, -Globals::psyduck->distance);
        rot.makeRotateY(Globals::psyduck->angle);
        trans = trans * tmp * rot;
        Globals::psyduck->angle += 5.0;
        if(Globals::psyduck->angle == 360.0){
            Globals::psyduck->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::psyduck->turned && Globals::psyduck->angle != 180.0){
        rot.makeRotateY(Globals::psyduck->angle);
        trans = trans * rot;
        Globals::psyduck->angle += 5.0;
    }
    else if(!Globals::psyduck->turned && Globals::psyduck->distance > 0){
        Matrix4 tmp = Matrix4();
        tmp.makeTranslate(0, 0, -Globals::psyduck->distance);
        Globals::psyduck->distance-=0.5;
        trans = trans * tmp;
    }
    

    
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::psyduck->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans = Matrix4();
    trans.makeTranslate(5, -1, -40+distance_to_camera);
    rot.makeRotateY(180);
    glmatrix.identity();
    trans = trans * rot;
    //If it's equal to 180 (which means it's turned around completely)
    if (Globals::vulpix->turned && Globals::vulpix->angle == 180.0){
        rot.makeRotateY(Globals::vulpix->angle);
        Matrix4 tmp = Matrix4();
        if(Globals::vulpix->distance < 8){
            tmp.makeTranslate(0, 0, -Globals::vulpix->distance);
            Globals::vulpix->distance+=0.5;
        }
        else{
            tmp.makeTranslate(0, 0, -Globals::vulpix->distance);
            if (Globals::spotlight->target==2) {
                Globals::spotlight->on =1 ;
            }else{
                //Globals::spotlight->on =0 ;
            }        }
        trans = trans * tmp* rot;
        
    }
    //Turn back
    else if(!Globals::vulpix->turned && Globals::vulpix->angle >= 180.0){
        Matrix4 tmp = Matrix4();
        tmp.makeTranslate(0, 0, -Globals::vulpix->distance);
        rot.makeRotateY(Globals::vulpix->angle);
        trans = trans * tmp * rot;
        Globals::vulpix->angle += 5.0;
        if(Globals::vulpix->angle == 360.0){
            Globals::vulpix->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::vulpix->turned && Globals::vulpix->angle != 180.0){
        rot.makeRotateY(Globals::vulpix->angle);
        trans = trans * rot;
        Globals::vulpix->angle += 5.0;
    }
    else if(!Globals::vulpix->turned && Globals::vulpix->distance > 0){
        Matrix4 tmp = Matrix4();
        tmp.makeTranslate(0, 0, -Globals::vulpix->distance);
        Globals::vulpix->distance-=0.5;
        trans = trans * tmp;
    }
    
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::vulpix->draw();
    
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
    trans = Matrix4();
    trans.makeTranslate(15, -1, -40+distance_to_camera);
    rot.makeRotateY(180);
    
    trans = trans * rot;
    //If it's equal to 180 (which means it's turned around completely)
    if (Globals::Eevee->turned && Globals::Eevee->angle == 180.0){
        rot.makeRotateY(Globals::Eevee->angle);
        Matrix4 tmp = Matrix4();
        if(Globals::Eevee->distance < 8){
            tmp.makeTranslate(0, 0, -Globals::Eevee->distance);
            Globals::Eevee->distance+=0.5;
        }
        else{
            tmp.makeTranslate(0, 0, -Globals::Eevee->distance);
            if (Globals::spotlight->target==3) {
                Globals::spotlight->on =1 ;
            }else{
                //Globals::spotlight->on =0 ;
            }
        }
        trans = trans * tmp* rot;
        
    }
    //Turn back
    else if(!Globals::Eevee->turned && Globals::Eevee->angle >= 180.0){
        Matrix4 tmp = Matrix4();
        tmp.makeTranslate(0, 0, -Globals::Eevee->distance);
        rot.makeRotateY(Globals::Eevee->angle);
        trans = trans * tmp * rot;
        Globals::Eevee->angle += 5.0;
        if(Globals::Eevee->angle == 360.0){
            Globals::Eevee->angle = 0.0;
        }
    }
    //Turn around
    else if(Globals::Eevee->turned && Globals::Eevee->angle != 180.0){
        rot.makeRotateY(Globals::Eevee->angle);
        trans = trans * rot;
        Globals::Eevee->angle += 5.0;
    }
    else if(!Globals::Eevee->turned && Globals::Eevee->distance > 0){
        Matrix4 tmp = Matrix4();
        tmp.makeTranslate(0, 0, -Globals::Eevee->distance);
        Globals::Eevee->distance-=0.5;
        trans = trans * tmp;
    }
    
    glmatrix.identity();
    glmatrix = camera * glmatrix * trans *pos*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::Eevee->draw();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glColor4f(1, 1, 1,1);
    //This part is for drawing L-system
    scale.makeScale(3, 3, 3);
    
    for(int i = 0; i < 4; i++){
        trans.makeTranslate(-20+i*10, -5, -60+distance_to_camera);
        glmatrix = camera * trans * scale;
        glmatrix.transpose();
        glLoadMatrixd(glmatrix.getPointer());
        Globals::l_system->draw();
    }
    
    for(int j = 1; j < 4; j++){
        trans.makeTranslate(-20, -5, -60 + j * 15+distance_to_camera);
        glmatrix = camera * trans * scale;
        glmatrix.transpose();
        glLoadMatrixd(glmatrix.getPointer());
        Globals::l_system->draw();
    }
    
    scale.makeScale(0.4, 0.4, 0.4);
    for(int j = 1; j < 4; j++){
        trans.makeTranslate(20, -5, -60 + j * 15+distance_to_camera);
        glmatrix = camera * trans * scale;
        glmatrix.transpose();
        glLoadMatrixd(glmatrix.getPointer());
        Globals::l_system1->draw();
    }
    
    scale.makeScale(0.7, 0.7, 0.7);
    for(int j = 1; j < 4; j++){
        trans.makeTranslate(30, -5, -60 + j * 15+distance_to_camera);
        glmatrix = camera * trans * scale;
        glmatrix.transpose();
        glLoadMatrixd(glmatrix.getPointer());
        Globals::l_system2->draw();
    }

    if(Globals::particle_effect_on){
        //Particle effect
        glDisable(GL_LIGHTING);
        glMatrixMode(GL_MODELVIEW);
        trans = Matrix4();
        trans.makeTranslate(0, 30, -40+distance_to_camera);
        glmatrix.identity();
        glmatrix = camera * glmatrix * trans *pos*scale ;
        glmatrix.transpose();
        glLoadIdentity();
        glLoadMatrixd(glmatrix.getPointer());
        glDisable(GL_CULL_FACE);
        Globals::particle_engine->advance(t*25 / 1000.0f);
        Globals::particle_engine->draw();
    }
    //glEnable(GL_LIGHT1);

    glColor4f(1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    trans2.makeTranslate(0, 30, -80);
    glmatrix.identity();
    scale.makeScale(10, 10, 10);
    glmatrix = camera * glmatrix * trans2*scale ;
    glmatrix.transpose();
    glLoadIdentity();
    glLoadMatrixd(glmatrix.getPointer());
    Globals::text->drawTitle();
    
    //Globals::spotlight->dir = Vector3(0, -10, -Globals::meowth->distance);
    Globals::spotlight->draw();
    //Globals::spotlight->enable();
}
void Window::displayPikachu(void){
    clock_t startTime = clock();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers

    t += 0.01;
    if(t >= number_of_curves){
        t = 1.01;
    }
    draw_scene();
    glFlush();
    glutSwapBuffers();
    glColor4f(1, 1, 1, 1);
    clock_t endTime = clock();
    cout << "frame rate: " << 1.0/(float((endTime - startTime))/CLOCKS_PER_SEC) << endl;
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
    glViewport(0, 0, w, h);  // set new viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0);// set perspective projection viewing frustum
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
        Globals::camera_line_on = !Globals::camera_line_on;
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
        //play(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/BabyCutted.wav");
        play(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/BabyCutted.wav");
        //play(0, tmp,"/Users/Ennuma/Desktop/CSE167_Final_Project/BabyCutted.wav");
    }
    //playing let it go
    else if(key == '4'){
        stopPlaying();
        char *tmp[4];
        //play(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/LetItGoCutted.wav");
        play(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/LetItGoCutted.wav");
        //play(0, tmp,"/Users/Ennuma/Desktop/CSE167_Final_Project/LetItGoCutted.wav");

    }
    //playing let it go
    else if(key == '5'){
        stopPlaying();
        char *tmp[4];
        //play(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/RoarCutted.wav");
        play(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/RoarCutted.wav");
        //play(0, tmp,"/Users/Ennuma/Desktop/CSE167_Final_Project/RoarCutted.wav");

    }
    //playing applause
    else if(key == '6'){
        //stopPlaying();
        char *tmp[4];
        //playApplause(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/Applause_clipped.wav");
        playApplause(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/Applause_clipped.wav");
        //playApplause(0, tmp,"/Users/Ennuma/Desktop/CSE167_Final_Project/Applause_clipped.wav");
       }
    //playing boo
    else if(key == '7'){
        //stopPlaying();
        char *tmp[4];
        //playBoo(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/boo.wav");
        playBoo(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/boo.wav");

       
    }
    //Motion controller
    else if(key == 'q'){
        if(Globals::bulbasaur->angle == 0.0){
            Globals::bulbasaur->turned = true;
            char *tmp[4];
            //playTurnback(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/002.WAV");
            playTurnback(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/002.WAV");

        }
        if(Globals::bulbasaur->angle == 180.0){
            Globals::bulbasaur->turned = false;
        }
    }
    else if (key =='w'){
        if(Globals::charmander->angle == 0.0){
            Globals::charmander->turned = true;
            char *tmp[4];
            //playTurnback(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/002.WAV");
            playTurnback(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/002.WAV");
        }
        if(Globals::charmander->angle == 180.0){
            Globals::charmander->turned = false;
        }
    }
    else if (key == 'e'){
        if(Globals::meowth->angle == 0.0){
            Globals::meowth->turned = true;
            char *tmp[4];
            //playTurnback(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/002.WAV");
            playTurnback(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/002.WAV");
        }
        if(Globals::meowth->angle == 180.0){
            Globals::meowth->turned = false;
        }
    }
    else if (key == 'r'){
        if(Globals::Snorlax->angle == 0.0){
            Globals::Snorlax->turned = true;
            char *tmp[4];
            //playTurnback(0, tmp,"/Users/margaretwm3/Dropbox/CSE167_Final_Project/002.WAV");
            playTurnback(0, tmp,"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/002.WAV");
        }
        if(Globals::Snorlax->angle == 180.0){
            Globals::Snorlax->turned = false;
        }
       
    }
    else if (key == 'a'){
        if(Globals::psyduck->angle == 0.0)
            Globals::psyduck->turned = true;
        if(Globals::psyduck->angle == 180.0){
            Globals::psyduck->turned = false;
        }
        Globals::spotlight->on = 0;

        Globals::spotlight->target =0 ;
    }
    else if (key == 's'){
        if(Globals::pika->angle == 0.0)
            Globals::pika->turned = true;
        if(Globals::pika->angle == 180.0){
            Globals::pika->turned = false;
        }
        Globals::spotlight->on = 0;

        Globals::spotlight->target =1;
    }
    else if (key == 'd'){
        if(Globals::vulpix->angle == 0.0)
            Globals::vulpix->turned = true;
        if(Globals::vulpix->angle == 180.0){
            Globals::vulpix->turned = false;
        }
        Globals::spotlight->on = 0;

        Globals::spotlight->target = 2;
    }
    else if (key == 'f'){
        if(Globals::Eevee->angle == 0.0)
            Globals::Eevee->turned = true;
        if(Globals::Eevee->angle == 180.0){
            Globals::Eevee->turned = false;
        }
        Globals::spotlight->on = 0;

        Globals::spotlight->target = 3;

    }
    else if(key == 'l')
    {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
    }
}


