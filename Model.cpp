//
//  Model.cpp
//  CSE167HW1
//
//  Created by Ruiqing Qiu on 11/17/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "Model.h"
Model::Model(){
    x_min = y_min = z_min = 10000;
    x_max = y_max = z_max = -10000;
    material = Material();
    light = Light();
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(light.light_position[0], light.light_position[1],light.light_position[2]);
    light_m2w = tmp;
    tmp.makeTranslate(light.light_position2[0], light.light_position2[1],light.light_position2[2]);
    light_m2w2 = tmp;
    model2world = Matrix4();
    model2world.identity();

}

Matrix4& Model::getMatrix(){
    return model2world;
}
void Model::update(){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(light.light_position[0], light.light_position[1],light.light_position[2]);
    light_m2w = tmp;
    tmp.makeTranslate(light.light_position2[0], light.light_position2[1],light.light_position2[2]);
    light_m2w2 = tmp;

}
void Model::push(){
    vector<float> x_list;
    vector<float> y_list;
    vector<float> z_list;
    vector<Vector3> normal_list;
    vector<Vector3> color_list;
    vector<Vector3> image_vertices;
    vector<Vector4> face_vertices;
    vector<Vector4> face_normal;
    vector<Vector3> texture_coordinates;
    vector<int> material_list;
}

void Model::spin(double deg)   // deg is in degrees
{
    Matrix4 tmp = Matrix4();
    tmp.makeRotateY(deg);
    model2world = model2world * tmp; //* translate * tmp;
}
void Model::moveLeft(){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(-1, 0, 0);
    model2world = tmp * model2world;
}
void Model::moveRight(){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(1,0,0);
    //T*m
    model2world = tmp * model2world;
    
}
void Model::moveIn(){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0, 0, 1);
    model2world = tmp * model2world;
    
}
void Model::moveOut(){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0, 0, -1);
    model2world = tmp * model2world;
    
}
void Model::moveUp(){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0, 1, 0);
    model2world = tmp * model2world;
    
}
void Model::moveDown(){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(0, -1, 0);
    model2world = tmp * model2world;
    
}

void Model::scaleUp(){
    Matrix4 tmp = Matrix4();
    tmp.makeScale(1.1, 1.1, 1.1);
    model2world = model2world * tmp;
}
void Model::scaleDown(){
    Matrix4 tmp = Matrix4();
    tmp.makeScale(0.9, 0.9, 0.9);
    model2world = model2world * tmp;
}


