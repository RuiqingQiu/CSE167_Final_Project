//
//  L_System.cpp
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/16/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "L_System.h"
void L_System::push(){
    glPushMatrix();
    if (lineWidth > 0)
        lineWidth -= 1;
    
}

void L_System::pop(){
    glPopMatrix();
    lineWidth += 1;
    
}

void L_System::rotL(){
    glRotatef(ANGLE, 1, 0, 0);
    glRotatef(ANGLE*4, 0, 1, 0);
    glRotatef(ANGLE, 0, 0, 1);
}
void L_System::rotR(){
    glRotatef(-ANGLE, 1, 0, 0);
    glRotatef(ANGLE*4, 0, 1, 0);
    glRotatef(-ANGLE, 0, 0, 1);
}
void L_System::drawLine(){
    glPushAttrib(GL_LIGHTING_BIT);//saves current lighting stuff
    
    
    //glColor3f(0.55, 0.27, 0.07);
    GLfloat ambient[4] = {0.55, 0.27, 0.07};    // ambient reflection
    GLfloat specular[4] = {0.55, 0.27, 0.07};   // specular reflection
    GLfloat diffuse[4] = {0.55, 0.27, 0.07};   // diffuse reflection
    
    
    // set the ambient reflection for the object
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    // set the diffuse reflection for the object
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    // set the specular reflection for the object
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glLineWidth(lineWidth);
    
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, length, 0);
    glEnd();
    
    glTranslatef(0, length, 0);
    glPopAttrib();
}

void L_System::draw(){
    
    string ch = "";
    string LSystem = trees->at(depth);
    cout << "drawing at depth " << depth << endl;
    for (int i = 0; i < LSystem.length(); i++){
        ch = LSystem.at(i);
        
        if (ch.compare("F") == 0){
            drawLine();
        } else if (ch.compare("[") == 0){
            push();
        } else if (ch.compare("]") == 0){
            pop();
        }
        //Turn right
        else if (ch.compare("+") == 0){
            rotR();
        }
        //Turn left
        else if (ch.compare("-") == 0){
            rotL();
        }
    }
}
void L_System::expand(float num)
{
    string ch = "";
    
    for (int i = 0; i < str.length(); i++){
        ch = str.at(i);
        
        if (ch.compare("F") == 0){
            //            str.replace(i, 1, "FF");
            //            i = i + 1;
            str.replace(i,1,"FF-[-F+F+F]+[+F-F-F]");
            i = i + 19;
        }
        else if (ch.compare("X") == 0){
            //str.replace(i,1,"F-[[X]+X]+F[+FX]-X");
            str.replace(i,1,"F");
            i = i + 1;
        }
        
    }
    trees->push_back(str);
}
