//
//  Material.cpp
//  CSE167HW1
//
//  Created by Ruiqing Qiu on 11/18/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "Material.h"
#include <stdlib.h>
#include <string.h>

void Material::set_mat_specular(float x, float y, float z, float w){
    mat_specular[0] = x;
    mat_specular[1] = y;
    mat_specular[2] = z;
    mat_specular[3] = w;
}

void Material::set_mat_ambient(float x, float y, float z, float w){
    mat_ambient[0] = x;
    mat_ambient[1] = y;
    mat_ambient[2] = z;
    mat_ambient[3] = w;
}

void Material::set_mat_shininess(float x){
    mat_shininess[0] = x;
}
void Material::set_mat_diffuse(float x, float y, float z, float w){
    mat_diffuse[0] = x;
    mat_diffuse[1] = y;
    mat_diffuse[2] = z;
    mat_diffuse[3] = w;
}

void Material::setName( const char *str ) {
    strcpy( name, str );
}
char* Material::getName() { return name; }

void Material::setR( float f ) { r = f; }
void Material::setG( float f ) { g = f; }
void Material::setB( float f ) { b = f; }
float Material::getR() { return r; }
float Material::getG() { return g; }
float Material::getB() { return b; }

void Material::apply() {
    //glColor3f( 1, 1, 0 );
    //GLfloat mat_ambient[] = { ar, ag, ab, 1.0 };
    //GLfloat mat_diffuse[] = { dr, dg, db, 1.0 };
    //GLfloat mat_specular[] = { sr, sg, sb, 1.0 };
    //GLfloat no_shininess[] = { shiness };
    
    //printf("diffuse %f %f %f\n",dr,dg,db);
    //printf("ambient %f %f %f\n",ar,ag,ab);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Use bilinear interpolation:
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}
