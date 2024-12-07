#include <iostream>
#include<cmath>
#include "include/practicasIG.h"

using namespace std;

float alturaCilindro=1.0f;
float rotacionAsiento=0.0f;
float inclinacionRespaldo=0.0f;

float gris[4]={0.5f,0.5f,0.5f,1.0f};
float marron[4]={0.65f,0.32f,0.17f,1.0f};

// Práctica 5
float especular[4]={0.1f,0.1f,0.1f,1.0f};
float brillo=10.f;

// Integro los dibujos de las diferentes partes que componen mi modelo Taburete
// siguiendo el grafo de escena diseñado.
 
void dibujaTaburete(int _id){

    if(getModoSeleccion()){
        colorSeleccion(_id);
    }
    // Dibujo el cilindro. Su grado de libertad de escalado se gestiona mediante 'C' y 'c'
    glPushMatrix();
        glScalef(1.0f,alturaCilindro,1.0f); // Ecalado del cilindro en el eje Y (manteniendo igual lo demás)
        glRotatef(-90,1.0f,0.0f,0.0f);
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,gris);
        dibujaCilindro();
    glPopMatrix();

    // Dibujo el asiento. Su grado de libertad de rotación(Y) se gestiona mediante 'V' y 'v'

    glPushMatrix();
        glTranslatef(0.0f,4.0f*alturaCilindro,0.0f);
        glRotatef(rotacionAsiento,0.0f,1.0f,0.0f); // Rotación del asiento y respaldo sobre su propio eje Y
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,marron);
        dibujaAsiento();

    // Dibujo el respaldo. Su grado de libertad de rotación (Z) se gestiona mediante 'B' y 'b'
        glPushMatrix();
            glTranslatef(0.0f,1.50f,-1.75f);
            glRotatef(90.0f,0.0f,1.0f,0.0f);
            glRotatef(inclinacionRespaldo,0.0f,0.0f,1.0f); // Inclinación (Rotación) del respaldo sobre su eje Z
            glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,marron);
            dibujaRespaldo();

        glPopMatrix(); // Fin del nodo repaldo
    glPopMatrix(); // Fin del nodo asiento
}