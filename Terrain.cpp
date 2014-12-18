/*
 *  Terrain.cpp
 *  FinalProject
 *
 *  Created by Andrew Huynh on 12/4/09.
 *  Copyright 2009 ATHLabs. All rights reserved.
 *
 */

#include "Terrain.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GLUT/GLUT.h>
#include "Vector3.h"
#include "SOIL.h"
Terrain1::Terrain1( int size ) {
    width = size;
    
    heightMap = (float*)malloc( width * width * sizeof(float) );
    
    // Zero out data
    for( int i = 0; i < width * width; i++ ) {
        heightMap[i] = 0;
    }
    
    grassTex = SOIL_load_OGL_texture
    (
     //strcat(pre,name),
     "/Users/Ennuma/Desktop/CSE167_Final_Project/grass.jpg",
     //"/Users/ruiqingqiu/Desktop/Qiu_Code/CSE167/CSE167 Final Project/grass.jpg",
     //"/Users/margaretwm3/Dropbox/CSE167_Final_Project/grass.jpg",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y
     );
    
    /* check for an error during the load process */
    if( 0 == grassTex )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

}

Terrain1::~Terrain1() {
    free( heightMap );
}

void Terrain1::generate(int seed, float displacement, float r, float s ) {
    srand( seed );
    roughness = r;
    k = s;
    
    // Seed corners
    float t = 5; //genDisp( displacement );
    setData( 0, 0, t );
    setData( 0, width-1, t );
    setData( width-1, 0, t );
    setData( width-1, width-1, t );
    
    // Start terrain generation
    genTerrain( 0, width-1, 0, width-1, displacement );
    
    // Flatten out water.
    for( int i = 0; i < width * width-1; i++ ) {
        if( heightMap[i] < -7.0 ) {
            heightMap[i] = -7.0;
        }
    }
    
    // Smooth out terrain
#warning smooth may make heightmap null !!!!!!!
    smooth();
    
    
    //printf("TEST for terrain!!! %f \n", heightMap[0]);
}

void Terrain1::draw()
{
    
    glBindTexture(GL_TEXTURE_2D, grassTex);
    // Make sure no bytes are padded:
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Select GL_MODULATE to mix texture with polygon color for shading:
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // Use bilinear interpolation:
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    
    //glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glBegin( GL_QUADS );
    //glColor3b(1,1,1);
    for (int i = 0;  i < getWidth()-1 ; i++) {
        for (int j = 0 ; j < getWidth()-1; j++) {
            float h1 =getData(i, j);
            float h2 =getData(i+1, j);
            float h3 =getData(i+1, j+1);
            float h4 =getData(i, j+1);
            Vector3 v1 = Vector3(i,j,h1);
            Vector3 v2 = Vector3(i+1,j,h2);
            Vector3 v3 = Vector3(i,j+1,h4);
            Vector3 n1 = v2-v1;
            Vector3 n2 = v3 -v1;
            Vector3 n = n1.cross(n1, n2);
            
            //glColor3f(1-h2/3, 1, 1-h2/3);
            glNormal3f( -n.x,-n.y,-n.z );

            glTexCoord2f(i%100/100.0, j%100/100.0);
            glVertex3f(i, h1, j);
            //glNormal3f( 0,0,1 );
            glTexCoord2f((i+1)%100/100.0, j%100/100.0);
            glVertex3f((i+1),h2, j);
            //glNormal3f( 0,0,1 );
            glTexCoord2f((i+1)%100/100.0,(j+1)%100/100.0);
            glVertex3f((i+1),h3, (j+1));
            //glNormal3f( 0,0,1 );
            glTexCoord2f(i%100/100.0,(j+1)%100/100.0);
            glVertex3f(i, h4,(j+1));
            
            //printf("x %i,y %i, height %f\n",i,j,h1);
        }
    }
    //glColor3f(1, 1, 1);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

int Terrain1::getWidth() {
    return width;
}

float Terrain1::getData( int x, int y ) {
    return heightMap[x * width + y];
}

float* Terrain1::getHeightMap()
{
    return heightMap;
}

void Terrain1::setData( int x, int y, float val ) {
    //printf("value in height map : %f\n", heightMap[x * width + y]);

    if ( true){//||heightMap[ x * width + y ] == 0 ) {
        heightMap[ x * width + y ] = val;
    }
    //printf("value in height map : %f\n", heightMap[x * width + y]);
    //printf("set data x: %i, y: %i, value %f\n",x,y,val);
}

// Generates a random int [-maxDisp, maxDisp];
float Terrain1::genDisp( float maxDisp ) {
    return (2*maxDisp) * ((float)rand()/RAND_MAX) - maxDisp;
}

void Terrain1::smooth() {
    for( int x = 1; x < width; x++ ) {
        for( int z = 0; z < width; z++ ) {
            heightMap[ x * width + z ] =
            heightMap[ (x-1) * width + z ] * ( 1 - k ) +
            heightMap[ x * width + z ] * k;
        }
    }
    
    for( int x = width-2; x >= 0; x-- ) {
        for( int z = 0; z < width; z++ ) {
            heightMap[ x * width + z ] =
            heightMap[ (x+1) * width + z ] * ( 1 - k ) +
            heightMap[ x * width + z ] * k;
        }
    }
    
    for( int x = 0; x < width; x++ ) {
        for( int z = width-2; z >= 0; z-- ) {
            heightMap[ x * width + z ] =
            heightMap[ x * width + (z+1) ] * ( 1 - k ) +
            heightMap[ x * width + z ] * k;
        }
    }
    
    for( int x = 0; x < width; x++ ) {
        for( int z = 1; z < width; z++ ) {
            heightMap[ x * width + z ] =
            heightMap[ x * width + (z-1) ] * ( 1 - k ) +
            heightMap[ x * width + z ] * k;
        }
    }
    
     
}

void Terrain1::genTerrain( int minX, int maxX, int minY, int maxY, float maxDisp ) {
    
    int mpX = ( maxX + minX ) / 2;
    int mpY = ( maxY + minY ) / 2;
    
    float A = getData( minX, minY );
    float B = getData( maxX, minY );
    float C = getData( minX, maxX );
    float D = getData( maxX, maxY );
    
    float E = ( A + B + C + D ) / 4 + genDisp( maxDisp );
    float F = ( A + C + E ) / 3 + genDisp( maxDisp );
    float G = ( A + B + E ) / 3 + genDisp( maxDisp );
    float H = ( B + D + E ) / 3 + genDisp( maxDisp );
    float I = ( C + D + E ) / 3 + genDisp( maxDisp );
    
    setData( mpX, mpY, E );
    setData( minX, mpY, F );
    setData( mpX, minY, G );
    setData( maxX, mpY, H );
    setData( mpX, maxY, I );
    
    float newDisp = maxDisp * pow( 2.0, -( roughness ) );
    
    if( ( mpX - minX ) > 0 ) {
        genTerrain( minX, mpX, minY, mpY, newDisp );
        genTerrain( mpX, maxX, minY, mpY, newDisp );
        genTerrain( minX, mpX, mpY, maxY, newDisp );
        genTerrain( mpX, maxX, mpY, maxY, newDisp );		
    }
}