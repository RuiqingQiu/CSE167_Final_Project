//
//  ParticleEngine.cpp
//  CSE167 Final Project
//
//  Created by Ruiqing Qiu on 12/12/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "ParticleEngine.h"

//Returns a random float from 0 to < 1
float randomFloat() {
    return (float)rand() / ((float)RAND_MAX + 1);
}

//Rotates the vector by the indicated number of degrees about the specified axis
Vec3f rotate(Vec3f v, Vec3f axis, float degrees) {
    axis = axis.normalize();
    float radians = degrees * PI / 180;
    float s = sin(radians);
    float c = cos(radians);
    return v * c + axis * axis.dot(v) * (1 - c) + v.cross(axis) * s;
}

//Returns the position of the particle, after rotating the camera
Vec3f adjParticlePos(Vec3f pos) {
    return rotate(pos, Vec3f(1, -1, 0), -30);
}

//Returns whether particle1 is in back of particle2
bool compareParticles(Particle* particle1, Particle* particle2) {
    return adjParticlePos(particle1->pos)[2] <
    adjParticlePos(particle2->pos)[2];
}

Vec3f ParticleEngine::curColor(){
    Vec3f color;
    if (colorTime < 0.166667f) {
        color = Vec3f(1.0f, colorTime * 6, 0.0f);
    }
    else if (colorTime < 0.333333f) {
        color = Vec3f((0.333333f - colorTime) * 6, 1.0f, 0.0f);
    }
    else if (colorTime < 0.5f) {
        color = Vec3f(0.0f, 1.0f, (colorTime - 0.333333f) * 6);
    }
    else if (colorTime < 0.666667f) {
        color = Vec3f(0.0f, (0.666667f - colorTime) * 6, 1.0f);
    }
    else if (colorTime < 0.833333f) {
        color = Vec3f((colorTime - 0.666667f) * 6, 0.0f, 1.0f);
    }
    else {
        color = Vec3f(1.0f, 0.0f, (1.0f - colorTime) * 6);
    }
    
    //Make sure each of the color's components range from 0 to 1
    for(int i = 0; i < 3; i++) {
        if (color[i] < 0) {
            color[i] = 0;
        }
        else if (color[i] > 1) {
            color[i] = 1;
        }
    }
    
    return color;
}

Vec3f ParticleEngine::curVelocity() {
    return Vec3f(2 * cos(angle), -0.0f, 2 * sin(angle));
}

//Alters p to be a particle newly produced by the fountain.
void ParticleEngine::createParticle(Particle* p) {
    p->pos = Vec3f(0, 0, 0);
    p->velocity = curVelocity() + Vec3f(5.5f * randomFloat() - 0.25f,
                                        0.5f * randomFloat() - 0.25f,
                                        5.5f * randomFloat() - 0.25f);
    p->color = curColor();
    p->timeAlive = 0;
    p->lifespan = randomFloat() + 2;
}


//Advances the particle fountain by STEP_TIME seconds.
void ParticleEngine::step() {
    colorTime += STEP_TIME / 10;
    while (colorTime >= 1) {
        colorTime -= 1;
    }
    
    for(int i = 0; i < NUM_PARTICLES; i++) {
        Particle* p = particles + i;
        
        p->pos += p->velocity * STEP_TIME;
        p->velocity += Vec3f(0.0f, -GRAVITY * STEP_TIME, 0.0f);
        p->timeAlive += STEP_TIME;
        if (p->timeAlive > p->lifespan) {
            createParticle(p);
        }
    }
}

ParticleEngine::ParticleEngine(GLuint textureId1){
    textureId = textureId1;
    cout << "texture id: " << textureId1 << endl;
    timeUntilNextStep = 0;
    colorTime = 0;
    angle = 0.5*PI;
    for(int i = 0; i < NUM_PARTICLES; i++) {
        createParticle(particles + i);
    }
    for(int i = 0; i < 5 / STEP_TIME; i++) {
        step();
    }
}





void ParticleEngine::draw() {
    vector<Particle*> ps;
    for(int i = 0; i < NUM_PARTICLES; i++) {
        ps.push_back(particles + i);
    }
    sort(ps.begin(), ps.end(), compareParticles);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBegin(GL_QUADS);
    for(unsigned int i = 0; i < ps.size(); i++) {
        Particle* p = ps[i];
        glColor4f(p->color[0], p->color[1], p->color[2],(1 - p->timeAlive / p->lifespan));
        float size = PARTICLE_SIZE / 2;
        
        Vec3f pos = adjParticlePos(p->pos);
        
        glTexCoord2f(0, 0);
        glVertex3f(pos[0] - size, pos[1] - size, pos[2]);
        glTexCoord2f(0, 1);
        glVertex3f(pos[0] - size, pos[1] + size, pos[2]);
        glTexCoord2f(1, 1);
        glVertex3f(pos[0] + size, pos[1] + size, pos[2]);
        glTexCoord2f(1, 0);
        glVertex3f(pos[0] + size, pos[1] - size, pos[2]);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
void ParticleEngine::advance(float dt) {
    while (dt > 0) {
        if (timeUntilNextStep < dt) {
            dt -= timeUntilNextStep;
            step();
            timeUntilNextStep = STEP_TIME;
        }
        else {
            timeUntilNextStep -= dt;
            dt = 0;
        }
    }
}


GLuint _textureId;

//Returns an array indicating pixel data for an RGBA image that is the same as
//image, but with an alpha channel indicated by the grayscale image alphaChannel
char* addAlphaChannel(Image* image, Image* alphaChannel) {
    char* pixels = new char[image->width * image->height * 4];
    for(int y = 0; y < image->height; y++) {
        for(int x = 0; x < image->width; x++) {
            for(int j = 0; j < 3; j++) {
                pixels[4 * (y * image->width + x) + j] =
                image->pixels[3 * (y * image->width + x) + j];
            }
            pixels[4 * (y * image->width + x) + 3] =
            alphaChannel->pixels[3 * (y * image->width + x)];
        }
    }
    
    return pixels;
}

//Makes the image into a texture, using the specified grayscale image as an
//alpha channel and returns the id of the texture
GLuint loadAlphaTexture(Image* image, Image* alphaChannel) {
    char* pixels = addAlphaChannel(image, alphaChannel);
    
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 image->width, image->height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 pixels);
    
    delete pixels;
    return textureId;
}


GLuint ParticleEngine::initRendering() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //Image* image = loadBMP("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/ParticleSystemGood/circle.bmp");
    //Image* alphaChannel = loadBMP("/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/ParticleSystemGood/circlealpha.bmp");
    
    
//    Image* image = loadBMP("/Users/margaretwm3/Dropbox/CSE167_Final_Project/circlealpha.bmp");
//    Image* alphaChannel = loadBMP("/Users/margaretwm3/Dropbox/CSE167_Final_Project/circlealpha.bmp");
    
    Image* image = loadBMP("/Users/Ennuma/Desktop/CSE167_Final_Project/circle.bmp");
    Image* alphaChannel = loadBMP("/Users/Ennuma/Desktop/CSE167_Final_Project/circlealpha.bmp");

    _textureId = loadAlphaTexture(image, alphaChannel);
    delete image;
    delete alphaChannel;
    return _textureId;
}


