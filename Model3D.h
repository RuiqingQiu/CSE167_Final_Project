//
//  Model3D.h
//  CSE167 Final Project
//
//  Created by Zhaoyang Zeng on 12/9/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167_Final_Project__Model3D__
#define __CSE167_Final_Project__Model3D__

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include "Face.h"
#include "Material.h"
#include "Matrix4.h"
using namespace std;

class Model3D {
public:
    float angle = 0.0;
    float distance = 0.0;
    Model3D( const char* );
    ~Model3D();
    
    void draw();
    void print();
    Matrix4 localpos;
    //For turn around
    bool turned = false;
    //virtual BoundingSphere* getBoundingSphere();
private:
    void readMaterial( const char*, vector<Material*>& );
    void readModel( const char* );
    void getIndices( char*, int*, int*, int* );
    void normalize();
    
    GLuint dList;
    float radius;
    bool isCompiled;
    vector<Face*> faces;
    
};
#endif /* defined(__CSE167_Final_Project__Model3D__) */
