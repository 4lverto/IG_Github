#include <iostream>
#include<cmath>
#include <GL/glut.h>
#include "include/Cilindro.h"

using namespace std;

void dibujaCilindro(){
    GLUquadric *c = gluNewQuadric();
    gluCylinder(c,0.5f,0.5f,4.0f,32,32);
    gluDeleteQuadric(c);
}