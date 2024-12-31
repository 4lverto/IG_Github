#include <iostream>
#include<cmath>
#include "include/practicasIG.h"

using namespace std;

// Creo el Asiento a partir de la primitiva que dibuja un cubo de 1x1
// y lo escalo de forma que ya tiene la forma deseada.
void dibujaAsiento(){
    glPushMatrix();
        glScalef(3.0f,0.5f,3.0f);
        glutSolidCube(1.0f);
    glPopMatrix();
}