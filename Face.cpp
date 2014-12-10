//
//  Face.cpp
//  CSE167 Final Project
//
//  Created by Zhaoyang Zeng on 12/9/14.
//  Copyright (c) 2014 Ruiqing Qiu. All rights reserved.
//

#include "Face.h"
Face::Face() {}

void Face::addVertex( Vector3& v ) {
    vertices.push_back( new Vector3( v ) );
}

void Face::addNormal( Vector3& v ) {
    normals.push_back( new Vector3( v ) );
}

void Face::setMaterial( Material& m ) {
    //material.setR( m.getR() );
    //material.setG( m.getG() );
    //material.setB( m.getB() );
    material =  m;
}

vector<Vector3*>* Face::getVertices() { return &vertices; }

void Face::draw() {
    glPushMatrix();
    material.apply();
    
    if( vertices.size() == 3 ) {
        glBegin( GL_TRIANGLES );
    } else if ( vertices.size() == 4 ) {
        glBegin( GL_QUADS );
    }
    for( int i = 0; i < vertices.size(); i++ ) {
        glNormal3f( normals[i]->x, normals[i]->y, normals[i]->z );
        glVertex3f( vertices[i]->x, vertices[i]->y, vertices[i]->z );
    }
    
    
    glEnd();
    
    glPopMatrix();
}
