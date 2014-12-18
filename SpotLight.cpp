//
//  SpotLight.cpp
//  CSE167 Final Project
//
//  Created by Zhaoyang Zeng on 12/17/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "SpotLight.h"
#include <GLUT/GLUT.h>
//#include "ParticleEngine.cpp"
float randomFloat2() {
    return (float)rand() / ((float)RAND_MAX + 1);
}

SpotLight::SpotLight()
{
    position = Vector3(0, 0, 0);
    ambient = Vector3(0, 0, 0);
    specular = Vector3(0, 0, 0);
    dir = Vector3(0, 0, 0);

}

SpotLight::~SpotLight()
{

}

void SpotLight::calculateDir()
{
    //dir = target->
}

void SpotLight::apply()
{
    
    
    float spotposition[]  = {(float)position.x, (float)position.y, (float)position.z, 1.0};	// lightsource position
    GLfloat  ambientLight[] = { (float)ambient.x, (float)ambient.y, (float)ambient.z, 1.0f};
    GLfloat  direction[] = { (float)dir.x, (float)dir.y, (float)dir.z, 0.0f};
    GLfloat  specularLight[] = { (float)specular.x, (float)specular.y, (float)specular.z, 1.0f};
    GLfloat diffuseLight[] ={ (float)diffuse.x, (float)diffuse.y, (float)diffuse.z, 1.0f};
    // The light is composed of just diffuse and specular components
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT2, GL_POSITION, spotposition);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);
    ////////////////////////////////////////////////
    
    
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 5.0);// set cutoff angle
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.01); // set focusing strength
    
}

void SpotLight::draw()
{
    if(target == 0)
    {
        dir = Vector3(-0.2, -1, 0);
    }
    if(target == 1)
    {
        dir = Vector3(-0.1, -1, 0);

    }
    if (target == 2) {
        dir = Vector3(0.1, -1, 0);

    }
    if (target==3) {
        dir = Vector3(0.2, -1, 0);

    }

    if(!on)
    {
        float rand = randomFloat2();
        if (rand<0.25) {
            dir = Vector3(-0.2, -1, 0);
        }else if(rand<0.5)
        {
            dir = Vector3(-0.1, -1, 0);

        }else if(rand < 0.75)
        {
            dir = Vector3(0.1, -1, 0);

        }else if(rand < 1)
        {
            dir = Vector3(0.2, -1, 0);

        }
        
        
        rand = randomFloat2();
        if (rand<0.25) {
            GLfloat diffuseLight[] ={ (1.0f, 0.0f, 0.0f, 1.0f)};
            glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
        }else if(rand<0.5)
        {
            GLfloat diffuseLight[] ={ (0.0f, 1.0f, 0.0f, 1.0f)};
            glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
            
        }else if(rand < 0.75)
        {
            GLfloat diffuseLight[] ={ (0.0f, 0.0f, 1.0f, 1.0f)};
            glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
            
        }else if(rand < 1)
        {
            GLfloat diffuseLight[] ={ (1.0f, 1.0f, 0.0f, 1.0f)};
            glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
            
        }

    }
    
    if(target==4)
    {
        dir = Vector3(0, 0, 0);
    }
    
    GLfloat  direction[] = { (float)dir.x, (float)dir.y, (float)dir.z, 0.0f};
    float spotposition[]  = {(float)position.x, (float)position.y, (float)position.z, 1.0};	// lightsource position

    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
    glLightfv(GL_LIGHT2, GL_POSITION, spotposition);


}

void SpotLight::enable()
{
    glEnable(GL_LIGHT2);

}

void SpotLight::disable()
{
    glDisable(GL_LIGHT2);

}
