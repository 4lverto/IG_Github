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
        this->texId=0;
    }


    Dado::Dado(GLuint t){
        this->texId=t;
    }


    void Dado::cargarTextura(const char *archivo){
        unsigned ancho,alto;
        unsigned char *imagen = LeerArchivoJPEG(archivo,ancho,alto);
        
        if(!imagen){
            cerr << "\nERROR --> No se pudo cargar la imagen de textura\n";
        }

        glGenTextures(1,&texId);
        glBindTexture(GL_TEXTURE_2D,texId);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,ancho,alto,0,GL_RGB,GL_UNSIGNED_BYTE,imagen);

        delete[] imagen;
    }


    void Dado::draw() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    glBegin(GL_QUADS);

    // Cara frontal (1 punto)
    glTexCoord2f(0.0f, 0.5f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(0.33f, 0.5f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(0.33f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);

    // Cara trasera (2 puntos)
    glTexCoord2f(0.33f, 0.5f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.66f, 0.5f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.66f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.33f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

    // Cara izquierda (3 puntos)
    glTexCoord2f(0.66f, 0.5f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.5f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.66f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

    // Cara derecha (4 puntos)
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.33f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(0.33f, 0.5f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.5f); glVertex3f( 1.0f,  1.0f, -1.0f);

    // Cara superior (5 puntos)
    glTexCoord2f(0.33f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.66f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.66f, 0.5f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.33f, 0.5f); glVertex3f(-1.0f,  1.0f,  1.0f);

    // Cara inferior (6 puntos)
    glTexCoord2f(0.66f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.5f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(0.66f, 0.5f); glVertex3f(-1.0f, -1.0f,  1.0f);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}