//
//  main.h
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/7/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167_Final_Project__main__
#define __CSE167_Final_Project__main__

#include <stdio.h>
#include "Window.h"
#include "Model.h"
#include "Camera.h"

namespace Globals
{
    extern Model* pikachu;
    extern Camera* main_camera;
    extern Model* nyarth;
};
static void load_model_pikachu();
static void load_model_nyarth();
#endif /* defined(__CSE167_Final_Project__main__) */
