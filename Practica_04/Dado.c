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
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    glBegin(GL_QUADS);

    // Cara frontal (1 punto)
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.5f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Vértice inferior izquierdo
    glTexCoord2f(1.0f / 4.0f, 0.5f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Vértice inferior derecho
    glTexCoord2f(1.0f / 4.0f, 0.75f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Vértice superior derecho
    glTexCoord2f(0.0f, 0.75f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Vértice superior izquierdo

    // Cara trasera (2 puntos)
    glNormal3f(0.0f,0.0f,-1.0f);
    glTexCoord2f(0.25f, 0.75f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.5f, 0.75f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.25f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

    // Cara izquierda (3 puntos)
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.5f, 0.75f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.75f, 0.75f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(0.75f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

    // Cara derecha (4 puntos)
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.75f, 0.75f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.75f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.75f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);

    // Cara superior (5 puntos)
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.5f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.25f, 0.5f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.25f, 0.75f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.75f); glVertex3f(-1.0f,  1.0f,  1.0f);

    // Cara inferior (6 puntos)
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.25f, 0.5f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.5f, 0.5f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.5f, 0.75f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(0.25f, 0.75f); glVertex3f(-1.0f, -1.0f,  1.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}



/*
void Dado::draw() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    glBegin(GL_QUADS);

    // Cara frontal
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.5f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Vértice inferior izquierdo
    glTexCoord2f(1.0f / 4.0f, 0.5f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Vértice inferior derecho
    glTexCoord2f(1.0f / 4.0f, 0.75f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Vértice superior derecho
    glTexCoord2f(0.0f, 0.75f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Vértice superior izquierdo

    // Cara trasera (2 puntos)
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f / 4.0f, 0.5f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(2.0f / 4.0f, 0.5f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(2.0f / 4.0f, 0.75f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(1.0f / 4.0f, 0.75f); glVertex3f(-1.0f,  1.0f, -1.0f);

    // Cara izquierda (3 puntos)
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(2.0f / 4.0f, 0.5f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(3.0f / 4.0f, 0.5f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(3.0f / 4.0f, 0.75f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(2.0f / 4.0f, 0.75f); glVertex3f(-1.0f,  1.0f, -1.0f);

    // Cara derecha (4 puntos)
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f / 4.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f / 4.0f, 0.25f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.25f); glVertex3f( 1.0f,  1.0f, -1.0f);

    // Cara superior (5 puntos)
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f / 4.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(2.0f / 4.0f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(2.0f / 4.0f, 0.25f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f / 4.0f, 0.25f); glVertex3f(-1.0f,  1.0f,  1.0f);

    // Cara inferior (6 puntos)
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(2.0f / 4.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(3.0f / 4.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(3.0f / 4.0f, 0.25f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(2.0f / 4.0f, 0.25f); glVertex3f(-1.0f, -1.0f,  1.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

*/