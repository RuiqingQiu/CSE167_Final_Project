//
//  Light.h
//  CSE167HW1
//
//  Created by Ruiqing Qiu on 11/18/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167HW1__Light__
#define __CSE167HW1__Light__

#include <stdio.h>
#include <GLUT/glut.h>

class Light{
public:
    GLfloat light_position[4] = { -3.0, 3.0, 5.0, 1.0 };
    GLfloat light_position2[4] = {3.0, 3.0, 5.0, 1.0};
    GLfloat light_ambient[4] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[4] = { 1, 0, 0, 1.0 };
    GLfloat light_specular[4] = { 1.0, 1.0, 1.0, 1.0 };
    void set_light_position(float x, float y, float z, float w);
    void set_light_ambient(float x, float y, float z, float w);
    void set_light_diffuse(float x, float y, float z, float w);
    void set_light_specular(float x, float y, float z, float w);
    void set_light_position2(float x, float y, float z, float w);
};
#endif /* defined(__CSE167HW1__Light__) */
