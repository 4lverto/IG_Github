#include <iostream>
#include<cmath>
#include <GL/glut.h>
#include "include/Cilindro.h"

using namespace std;

// Utilizo la primitiva de glu para dibujar un cilindro de radio 0.5 y 4 de altura.
void dibujaCilindro(){
    GLUquadric *c = gluNewQuadric();
    gluCylinder(c,0.5f,0.5f,4.0f,32,32);
    gluDeleteQuadric(c);
}