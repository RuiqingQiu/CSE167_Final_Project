//
//  Material.cpp
//  CSE167HW1
//
//  Created by Ruiqing Qiu on 11/18/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "Material.h"

void Material::set_mat_specular(float x, float y, float z, float w){
    mat_specular[0] = x;
    mat_specular[1] = y;
    mat_specular[2] = z;
    mat_specular[3] = w;
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
