#include <iostream>
#include<cmath>
#include "include/Respaldo.h"

using namespace std;

void dibujaRespaldo(){
    glPushMatrix();
        glScalef(0.5f,3.0f,3.0f);
        glutSolidCube(1.0f);
    glPopMatrix();
}