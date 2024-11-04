    // //// //
    // DADO //
    // //// //

#include <iostream>
#include<cmath>
#include "include/Dado.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>	

using namespace std;


    Dado::Dado(){

    }


void Dado::draw() {
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);    
    glBindTexture(GL_TEXTURE_2D, texId);
    glMaterialfv(GL_FRONT, GL_AMBIENT, reflectividad_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, reflectividad_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, reflectividad_especular);
    glMaterialf(GL_FRONT, GL_SHININESS,e);
    

    glBegin(GL_QUADS);

    // Cara frontal (orden antihorario)
    glNormal3f(0.0f, 0.0f, 1.0f);  // Normal hacia afuera
    glTexCoord2f(0.25f,0.5f); glVertex3f(-1.0f, -1.0f,  1.0f); // Inferior izquierda
    glTexCoord2f(0.5f, 0.5f); glVertex3f( 1.0f, -1.0f,  1.0f); // Inferior derecha
    glTexCoord2f(0.5f, 0.75f); glVertex3f( 1.0f,  1.0f,  1.0f); // Superior derecha
    glTexCoord2f(0.25f, 0.75f); glVertex3f(-1.0f,  1.0f,  1.0f); // Superior izquierda

    // Cara trasera (orden antihorario)
    glNormal3f(0.0f, 0.0f, -1.0f); // Normal hacia afuera
    glTexCoord2f(0.75f,0.25f); glVertex3f(-1.0f, -1.0f, -1.0f); // Inferior izquierda
    glTexCoord2f(0.75f,0.5f); glVertex3f(-1.0f,  1.0f, -1.0f); // Superior izquierda
    glTexCoord2f(1.0f,0.5f); glVertex3f( 1.0f,  1.0f, -1.0f); // Superior derecha
    glTexCoord2f(1.0f,0.25f); glVertex3f( 1.0f, -1.0f, -1.0f); // Inferior derecha

    // Cara izquierda (orden antihorario)
    glNormal3f(-1.0f, 0.0f, 0.0f); // Normal hacia afuera
    glTexCoord2f(0.5f,0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Inferior trasera
    glTexCoord2f(0.5f,0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); // Inferior frontal
    glTexCoord2f(0.5f,0.0f); glVertex3f(-1.0f,  1.0f,  1.0f); // Superior frontal
    glTexCoord2f(0.5f,0.0f); glVertex3f(-1.0f,  1.0f, -1.0f); // Superior trasera

    // Cara derecha (orden antihorario)
    glNormal3f(1.0f, 0.0f, 0.0f); // Normal hacia afuera
    glVertex3f(1.0f, -1.0f, -1.0f); // Inferior trasera
    glVertex3f(1.0f,  1.0f, -1.0f); // Superior trasera
    glVertex3f(1.0f,  1.0f,  1.0f); // Superior frontal
    glVertex3f(1.0f, -1.0f,  1.0f); // Inferior frontal

    // Cara superior (orden antihorario)
    glNormal3f(0.0f, 1.0f, 0.0f); // Normal hacia afuera
    glVertex3f(-1.0f, 1.0f, -1.0f); // Trasera izquierda
    glVertex3f(-1.0f, 1.0f,  1.0f); // Frontal izquierda
    glVertex3f( 1.0f, 1.0f,  1.0f); // Frontal derecha
    glVertex3f( 1.0f, 1.0f, -1.0f); // Trasera derecha

    // Cara inferior (orden antihorario)
    glNormal3f(0.0f, -1.0f, 0.0f); // Normal hacia afuera
    glVertex3f(-1.0f, -1.0f, -1.0f); // Trasera izquierda
    glVertex3f( 1.0f, -1.0f, -1.0f); // Trasera derecha
    glVertex3f( 1.0f, -1.0f,  1.0f); // Frontal derecha
    glVertex3f(-1.0f, -1.0f,  1.0f); // Frontal izquierda

    glEnd();
    glDisable(GL_TEXTURE_2D);
}


