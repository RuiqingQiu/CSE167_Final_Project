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
        lineWidth -= incr;
    
}

void L_System::pop(){
    glPopMatrix();
    lineWidth += incr;
    
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
    
    glColor3f(0.15, 1, 0.27);
    glLineWidth(lineWidth);
    
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, length, 0);
    glEnd();
    
    glTranslatef(0, length, 0);
}



void L_System::draw(){
    
    string ch = "";
    string LSystem = trees->at(depth);
    //cout << "drawing at depth " << depth << endl;
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
            if(num < 0.5){
                str.replace(i,1,"FF-[-F+F+F]+[+F-F-F]");
                i = i + 19;
            }
            else{
                str.replace(i,1,"FF+[+F-F-F]-[-F+F+F]");
                i = i + 19;
            }
        }
        else if (ch.compare("X") == 0){
            str.replace(i,1,"F");
            i = i + 1;
        }
        
    }
    trees->push_back(str);
}


void L_System::expand1(float num){
    string ch = "";
    
    for (int i = 0; i < str.length(); i++){
        ch = str.at(i);
        //X→F[+X][-X]FX  F→FF
        if (ch.compare("F") == 0){
            str.replace(i,1,"FF");
            i = i + 1;
        }
        else if (ch.compare("X") == 0){
            str.replace(i,1,"F[+X][-X]FX");
            i = i + 10;
        }
        
    }
    trees->push_back(str);
}
//X→F-[[X]+X]+F[+FX]-X F→FF
void L_System::expand2(float num){
    string ch = "";
    
    for (int i = 0; i < str.length(); i++){
        ch = str.at(i);
        //X→F[+X][-X]FX  F→FF
        if (ch.compare("F") == 0){
            str.replace(i,1,"FF");
            i = i + 1;
        }
        else if (ch.compare("X") == 0){
            str.replace(i,1,"F[+X]F[-X]+X");
            i = i + 11;
        }
        
    }
    trees->push_back(str);
}
