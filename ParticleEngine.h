//
//  ParticleEngine.h
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/12/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#ifndef __CSE167_Final_Project__ParticleEngine__
#define __CSE167_Final_Project__ParticleEngine__

#include <stdio.h>
#include <GLUT/GLUT.h>
#include "vec3f.h"
#include <stdlib.h>

#include <math.h>
#include <vector>
#include "imageloader.h"

using namespace std;

const float PI = 3.1415926535f;
//Represents a single particle.
struct Particle {
    Vec3f pos;
    Vec3f velocity;
    Vec3f color;
    float timeAlive; //The amount of time that this particle has been alive.
    float lifespan;  //The total amount of time that this particle is to live.
};

const float GRAVITY = 3.0f;
const int NUM_PARTICLES = 1000;
//The interval of time, in seconds, by which the particle engine periodically
//steps.
const float STEP_TIME = 0.01f;
//The length of the sides of the quadrilateral drawn for each particle.
const float PARTICLE_SIZE = 0.05f;

class ParticleEngine{
private:
    GLuint textureId;
    Particle particles[NUM_PARTICLES];
    //The amount of time until the next call to step().
    float timeUntilNextStep;
    //The color of particles that the fountain is currently shooting.  0
    //indicates red, and when it reaches 1, it starts over at red again.  It
    //always lies between 0 and 1.
    float colorTime;
    //The angle at which the fountain is shooting particles, in radians.
    float angle;
    
    //Returns the current color of particles produced by the fountain.
    Vec3f curColor();
    
    //Returns the average velocity of particles produced by the fountain.
    Vec3f curVelocity();
    //Alters p to be a particle newly produced by the fountain.
    void createParticle(Particle* p);
    //Advances the particle fountain by STEP_TIME seconds.
    void step();
public:
    
    ParticleEngine(GLuint textureId1);
    //Advances the particle fountain by the specified amount of time.
    void advance(float dt);
    //Draws the particle fountain.
    void draw();
    static GLuint initRendering();
};

#endif /* defined(__CSE167_Final_Project__ParticleEngine__) */
