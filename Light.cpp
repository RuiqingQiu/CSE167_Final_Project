//
//  Light.cpp
//  CSE167HW1
//
//  Created by Ruiqing Qiu on 11/18/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "Light.h"
void Light::set_light_position(float x, float y, float z, float w){
    light_position[0] = x;
    light_position[1] = y;
    light_position[2] = z;
    light_position[3] = w;
}
void Light::set_light_ambient(float x, float y, float z, float w){
    light_ambient[0] = x;
    light_ambient[1] = y;
    light_ambient[2] = z;
    light_ambient[3] = w;
}
void Light::set_light_diffuse(float x, float y, float z, float w){
    light_diffuse[0] = x;
    light_diffuse[1] = y;
    light_diffuse[2] = z;
    light_diffuse[3] = w;
}
void Light::set_light_specular(float x, float y, float z, float w){
    light_specular[0] = x;
    light_specular[1] = y;
    light_specular[2] = z;
    light_specular[3] = w;
}
void Light::set_light_position2(float x, float y, float z, float w){
    light_position2[0] = x;
    light_position2[1] = y;
    light_position2[2] = z;
    light_position2[3] = w;
}
