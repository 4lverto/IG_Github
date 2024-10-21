#include <iostream>
#include<cmath>
#include "include/Cilindro.h"

using namespace std;

void dibujaCilindro(){
    glPushMatrix();
        gluCylinder(gluNewQuadric(),0.5f,0.5f,3.0f+alturaCilindro,30,30+alturaCilindro);
    glPopMatrix();
}