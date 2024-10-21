#include <iostream>
#include<cmath>
#include "include/Respaldo.h"

using namespace std;

void dibujaRespaldo(){
    glPushMatrix();
        glScalef(3.0f,5.0f,0.5f);
        glutSolidCube(1.0f);
    glPopMatrix();
}