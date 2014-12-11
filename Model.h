//
//  Model.h
//  CSE167HW1
//
//  Created by Ruiqing Qiu on 11/17/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167HW1__Model__
#define __CSE167HW1__Model__

#include <stdio.h>
#include <vector>
#include "Vector3.h"
#include "Material.h"
#include "Light.h"
#include "Matrix4.h"

using namespace std;
class Model{
public:
    vector<float> x_list;
    vector<float> y_list;
    vector<float> z_list;
    vector<Vector3> normal_list;
    vector<Vector3> color_list;
    vector<Vector3> image_vertices;
    vector<Vector4> face_vertices;
    vector<Vector4> face_normal;
    vector<Vector4> face_texture;
    vector<Vector3> texture_coordinates;
    vector<int> material_list;
    vector<int> switch_position;
    Matrix4 model2world;

    
    GLuint texture[10];
    int texture_num = 0;
    
    
    Material material;
    Light light;
    Matrix4 light_m2w;
    Matrix4 light_m2w2;
    int face_number;
    float x_min, x_max, y_min, y_max, z_min, z_max;
    Model();
    void update();
    Matrix4& getMatrix();
    void spin(double);      // spin cube [degrees]

    void push();
    void moveLeft();
    void moveRight();
    void moveIn();
    void moveOut();
    void moveDown();
    void moveUp();
    void reset();
    void scaleUp();
    void scaleDown();

};
#endif /* defined(__CSE167HW1__Model__) */
