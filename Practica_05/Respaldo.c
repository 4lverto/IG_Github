#include <iostream>
#include<cmath>
#include "include/Respaldo.h"

using namespace std;

// Creo el Respaldo a partir de la primitiva que dibuja un cubo de 1x1
// y lo escalo de forma que ya tiene la forma deseada.
void dibujaRespaldo(){
    glPushMatrix();
        glScalef(0.5f,3.0f,3.0f);
        glutSolidCube(1.0f);
    glPopMatrix();
}