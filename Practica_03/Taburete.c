#include <iostream>
#include<cmath>
#include "include/Taburete.h"

using namespace std;

float alturaCilindro=0.0f;
float rotacionAsiento=0.0f;
float inclinacionRespaldo=0.0f;

float morado[4]={0.8,0,1,1};
float verde[4]={0,1,0,1};
float rojo[4]={1,0,0,1};
float azul[4]={0,0,1,1};
float negro[4]={0,0,0,1};
float blanco[4]={1,1,1,1};
float naranja[4]={1.0f,0.5f,0.0f,1.0f};
float amarillo[4]={1.0f,1.0f,0.0f,1.0f};

void dibujaTaburete(){

    // Dibujo el cilindro
    
    glPushMatrix();
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        glTranslatef(0.0f,alturaCilindro,0.0f);
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,verde);
        dibujaCilindro();
    glPopMatrix();

    // Dibujo el asiento
    
    glPushMatrix();
        glTranslatef(0.0f,2.75f,0.0f);
        glRotatef(90.0f,0.0f,0.0f,1.0f);
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,azul);
        glRotatef(rotacionAsiento,1.0f,0.0f,0.0f);
        glTranslatef(alturaCilindro,0.0f,0.0f);
        dibujaAsiento();
    glPopMatrix();

    // Dibujo el respaldo
    glPushMatrix();
        glTranslatef(0.0f,4.5f,-1.75f);  
        glRotatef(90.0f,0.0f,1.0f,0.0f);
        glRotatef(rotacionAsiento,0.0,1.0f,0.0f);
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,rojo);
        glTranslatef(0.0f,alturaCilindro,0.0f);
        dibujaRespaldo();
    glPopMatrix();
}
