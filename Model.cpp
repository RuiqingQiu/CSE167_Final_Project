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
}
void Model::update(){
    Matrix4 tmp = Matrix4();
    tmp.makeTranslate(light.light_position[0], light.light_position[1],light.light_position[2]);
    light_m2w = tmp;
    tmp.makeTranslate(light.light_position2[0], light.light_position2[1],light.light_position2[2]);
    light_m2w2 = tmp;

}