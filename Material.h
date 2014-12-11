//
//  Material.h
//  CSE167HW1
//
//  Created by Ruiqing Qiu on 11/18/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167HW1__Material__
#define __CSE167HW1__Material__

#include <stdio.h>
#include <GLUT/glut.h>
class Material{
public:
    GLfloat mat_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[4] = {0.5, 0.5, 0.5, 1.0};
    GLfloat mat_ambient[4] = {0.5, 0.5, 0.5, 1.0};
    GLfloat mat_shininess[1] = { 128 };
    
    
    void set_mat_specular(float x, float y, float z, float w);
    void set_mat_shininess(float x);
    void set_mat_diffuse(float x, float y, float z, float w);
    void set_mat_ambient(float x, float y, float z, float w);

    void apply();
    
    void setName( const char* );
    char* getName();
    
    void setR( float );
    float getR();
    
    void setG( float );
    float getG();
    
    void setB( float );
    float getB();
    
    GLuint texture;
    
private:
    char name[80];
    float r, g, b;
    
    
};
#endif /* defined(__CSE167HW1__Material__) */
