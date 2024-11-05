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


    Dado::Dado(float l){
        this->lado=l;
        this->halflado=this->lado/2;
    }


void Dado::draw() {
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_QUADS);

    // Cara frontal (1 punto)
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1/2.0f, 1/1.0f); glVertex3f(-halflado, 0.0f, halflado);  // Vértice inferior izquierdo
    glTexCoord2f(3/4.0f, 1/1.0f); glVertex3f(halflado, 0.0f, halflado);  // Vértice inferior derecho
    glTexCoord2f(3/4.0f, 3/4.0f); glVertex3f(halflado, lado, halflado);  // Vértice superior derecho
    glTexCoord2f(1/2.0f, 3/4.0f); glVertex3f(-halflado,  lado, halflado);  // Vértice superior izquierdo

    // Cara trasera (2 puntos)
    glNormal3f(0.0f,0.0f,-1.0f);
    glTexCoord2f(0.75f, 0.5f); glVertex3f(halflado, lado, -halflado);
    glTexCoord2f(0.5f, 0.5f); glVertex3f( halflado, 0.0f, -halflado);
    glTexCoord2f(0.5f, 0.25f); glVertex3f( -halflado,  0.0f, -halflado);
    glTexCoord2f(0.75f, 0.25f); glVertex3f(-halflado, lado, -halflado);

    // Cara izquierda (3 puntos)
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.25f, 0.5f); glVertex3f(-halflado, 0.0f, -halflado);
    glTexCoord2f(0.25f, 0.75f); glVertex3f(-halflado, 0.0f,  halflado);
    glTexCoord2f(0.5f, 0.75f); glVertex3f(-halflado,  lado,  halflado);
    glTexCoord2f(0.5f, 0.5f); glVertex3f(-halflado, lado, -halflado);

    // Cara derecha (4 puntos)
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.5f); glVertex3f( halflado, 0.0f, -halflado);
    glTexCoord2f(0.75, 0.5f); glVertex3f( halflado, lado, -halflado);
    glTexCoord2f(0.75f, 0.75f); glVertex3f( halflado, lado, halflado);
    glTexCoord2f(1.0f, 0.75f); glVertex3f( halflado,  0.0f, halflado);

    // Cara superior (5 puntos)
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.75f, 0.5f); glVertex3f(halflado,  lado, -halflado);
    glTexCoord2f(0.5f, 0.5f); glVertex3f( -halflado, lado, -halflado);
    glTexCoord2f(0.5f, 0.75f); glVertex3f( -halflado, lado, halflado);
    glTexCoord2f(0.75f, 0.75f); glVertex3f(halflado, lado, halflado);

    // Cara inferior (6 puntos)
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.25f, 0.5f); glVertex3f(-halflado, 0.0f, -halflado);
    glTexCoord2f(0.0f, 0.5f); glVertex3f( halflado, 0.0f, -halflado);
    glTexCoord2f(0.0f, 0.75f); glVertex3f( halflado, 0.0f, halflado);
    glTexCoord2f(0.25f, 0.75f); glVertex3f(-halflado, 0.0f, halflado);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}