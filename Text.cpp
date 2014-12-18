//
//  Text.cpp
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/17/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "Text.h"
//Computes a scaling value so that the strings
float Text::computeScale(const char* strs[4]) {
    float maxWidth = 0;
    for(int i = 0; i < 4; i++) {
        float width = t3dDrawWidth(strs[i]);
        if (width > maxWidth) {
            maxWidth = width;
        }
    }
    return 2.6f / maxWidth;
}

void Text::cleanup() {
    t3dCleanup();
}

void Text::initRendering() {
    t3dInit();
}

void Text::drawTitle() {
    
    GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat lightPos0[] = {-0.5f, 0.5f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);
    //Draw the strings along the sides of a square
    glScalef(_scale, _scale, _scale);
    glColor3f(0.3f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-5, 0, 1.5f / _scale);
    t3dDraw3D(title[0], 0, 0, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2, 0, 1.5f / _scale);
    t3dDraw3D(title[1], 0, 0, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2, 0, 1.5f / _scale);
    t3dDraw3D(title[2], 0, 0, 0.2f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(9, 0, 1.5f / _scale);
    t3dDraw3D(title[3], 0, 0, 0.2f);
    glPopMatrix();    
}

void Text::drawSong1()
{
    GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat lightPos0[] = {-0.5f, 0.5f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);
    //Draw the strings along the sides of a square
    glScalef(_scale, _scale, _scale);
    glColor3f(0.3f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-5, 0, 1.5f / _scale);
    t3dDraw3D(song1[0], 0, 0, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 0, 1.5f / _scale);
    t3dDraw3D(song1[1], 0, 0, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2, 0, 1.5f / _scale);
    t3dDraw3D(song1[2], 0, 0, 0.2f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5, 0, 1.5f / _scale);
    t3dDraw3D(song1[3], 0, 0, 0.2f);
    glPopMatrix();
    
}

void Text::drawSong2()
{
    GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat lightPos0[] = {-0.5f, 0.5f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);
    //Draw the strings along the sides of a square
    glScalef(_scale, _scale, _scale);
    glColor3f(0.3f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-5, 0, 1.5f / _scale);
    t3dDraw3D(song2[0], 0, 0, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2, 0, 1.5f / _scale);
    t3dDraw3D(song2[1], 0, 0, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1, 0, 1.5f / _scale);
    t3dDraw3D(song2[2], 0, 0, 0.2f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6, 0, 1.5f / _scale);
    t3dDraw3D(song2[3], 0, 0, 0.2f);
    glPopMatrix();
    
}

void Text::drawSong3()
{
    GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat lightPos0[] = {-0.5f, 0.5f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);
    //Draw the strings along the sides of a square
    glScalef(_scale, _scale, _scale);
    glColor3f(0.3f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-7, 0, 1.5f / _scale);
    t3dDraw3D(song3[0], 0, 0, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-5, 0, 1.5f / _scale);
    t3dDraw3D(song3[1], 0, 0, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1, 0, 1.5f / _scale);
    t3dDraw3D(song3[2], 0, 0, 0.2f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4, 0, 1.5f / _scale);
    t3dDraw3D(song3[3], 0, 0, 0.2f);
    glPopMatrix();
    
}

void Text::drawSong4()
{
    GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat lightPos0[] = {-0.5f, 0.5f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);
    //Draw the strings along the sides of a square
    glScalef(_scale, _scale, _scale);
    glColor3f(0.3f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-5, 0, 1.5f / _scale);
    t3dDraw3D(song4[0], 0, 0, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2, 0, 1.5f / _scale);
    t3dDraw3D(song4[1], 0, 0, 0.2f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1, 0, 1.5f / _scale);
    t3dDraw3D(song4[2], 0, 0, 0.2f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5, 0, 1.5f / _scale);
    t3dDraw3D(song4[3], 0, 0, 0.2f);
    glPopMatrix();
    
}


void Text::draw()
{
    if (song == 0) {
        drawTitle();
    }else if(song == 1)
    {
        drawSong1();
    }else if(song == 2)
    {
        drawSong2();
    }else if(song == 3)
    {
        drawSong3();
    }else if(song == 4)
    {
        drawSong4();
    }
}
