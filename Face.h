//
//  Face.h
//  CSE167 Final Project
//
//  Created by Zhaoyang Zeng on 12/9/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167_Final_Project__Face__
#define __CSE167_Final_Project__Face__

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <vector>
#include "Vector3.h"
#include "Material.h"
using namespace std;
class Face {
public:
    Face();
    
    void addVertex( Vector3& );
    void addNormal( Vector3& );
    
    void setMaterial( Material& );
    
    void draw();
    
    vector<Vector3*>* getVertices();
    
private:
    vector<Vector3*> normals;
    vector<Vector3*> vertices;
    Material material;
};
#endif /* defined(__CSE167_Final_Project__Face__) */
