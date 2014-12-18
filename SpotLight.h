//
//  SpotLight.h
//  CSE167 Final Project
//
//  Created by Zhaoyang Zeng on 12/17/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//
/**
 USE opengl light2

 */
#ifndef __CSE167_Final_Project__SpotLight__
#define __CSE167_Final_Project__SpotLight__

#include <stdio.h>
#include "Vector3.h"
#include "Model3D.h"
using namespace std;
class SpotLight{
public:
    SpotLight();
    ~SpotLight();
    
    Vector3 position;
    Vector3 ambient;
    Vector3 specular;
    Vector3 diffuse;
    Vector3 dir;
    Model3D* target;
    
    void apply();
    void enable();
    void disable();
    void draw();
private:
    void calculateDir();
    
};
#endif /* defined(__CSE167_Final_Project__SpotLight__) */
