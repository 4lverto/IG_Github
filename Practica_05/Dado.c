    // //// //
    // DADO //
    // //// //

#include <iostream>
#include<cmath>
#include "include/Dado.h"
#include "include/practicasIG.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>	

using namespace std;


Dado::Dado(float l,int _id){
    this->lado=l;
    this->mitad=this->lado/2;
    this->id=_id;
}


void Dado::draw() {
    glPushAttrib(GL_LIGHTING|GL_TEXTURE_BIT|GL_CURRENT_BIT);

    if(!getModoSeleccion()){
        glMaterialfv(GL_FRONT, GL_AMBIENT, reflectividad_ambiente);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, reflectividad_difusa);
        glMaterialfv(GL_FRONT, GL_SPECULAR, reflectividad_especular);
        glMaterialf(GL_FRONT, GL_SHININESS,e);
        glEnable(GL_TEXTURE_2D); 
    }else{
        colorSeleccion(ID_DADO);
    }

    glBindTexture(GL_TEXTURE_2D, texId);  

    glBegin(GL_QUADS);

    // Cara frontal (Número 1)
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.25f, 0.75f); glVertex3f(-mitad, 0.0f, mitad);  // Vértice inferior izquierdo
    glTexCoord2f(0.5f, 0.75f); glVertex3f(mitad, 0.0f, mitad);  // Vértice inferior derecho
    glTexCoord2f(0.5f, 0.5f); glVertex3f(mitad, lado, mitad);  // Vértice superior derecho
    glTexCoord2f(0.25f, 0.5f); glVertex3f(-mitad,  lado, mitad);  // Vértice superior izquierdo

    // Cara trasera (Número 6)
    glNormal3f(0.0f,0.0f,-1.0f);
    glTexCoord2f(0.75f, 0.75f); glVertex3f(mitad, lado, -mitad);
    glTexCoord2f(1.0f, 0.75f); glVertex3f( mitad, 0.0f, -mitad);
    glTexCoord2f(1.0f, 0.5f); glVertex3f( -mitad,  0.0f, -mitad);
    glTexCoord2f(0.75f, 0.5f); glVertex3f(-mitad, lado, -mitad);

    // Cara izquierda (Número 3)
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.5f, 0.5f); glVertex3f(-mitad, 0.0f, -mitad);
    glTexCoord2f(0.75f, 0.5f); glVertex3f(-mitad, 0.0f,  mitad);
    glTexCoord2f(0.75f, 0.25f); glVertex3f(-mitad,  lado,  mitad);
    glTexCoord2f(0.5f, 0.25f); glVertex3f(-mitad, lado, -mitad);

    // Cara derecha (Número 4)
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f( mitad, 0.0f, -mitad);
    glTexCoord2f(0.75, 1.0f); glVertex3f( mitad, lado, -mitad);
    glTexCoord2f(0.75f, 0.75f); glVertex3f( mitad, lado, mitad);
    glTexCoord2f(0.5f, 0.75f); glVertex3f( mitad,  0.0f, mitad);

    // Cara superior (Número 2)
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.75f, 0.5f); glVertex3f(mitad,  lado, -mitad);
    glTexCoord2f(0.5f, 0.5f); glVertex3f( -mitad, lado, -mitad);
    glTexCoord2f(0.5f, 0.75f); glVertex3f( -mitad, lado, mitad);
    glTexCoord2f(0.75f, 0.75f); glVertex3f(mitad, lado, mitad);

    // Cara inferior (Número 5)
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.25f, 0.5f); glVertex3f(-mitad, 0.0f, -mitad);
    glTexCoord2f(0.0f, 0.5f); glVertex3f( mitad, 0.0f, -mitad);
    glTexCoord2f(0.0f, 0.75f); glVertex3f( mitad, 0.0f, mitad);
    glTexCoord2f(0.25f, 0.75f); glVertex3f(-mitad, 0.0f, mitad);

    glEnd();

    if(!getModoSeleccion()){
        glDisable(GL_TEXTURE_2D);
    }

    glPopAttrib();
}