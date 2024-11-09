// Dado.h
#ifndef DADO_H
#define DADO_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include <vector>
#include "Malla.h"

class Dado : public Malla{

    private:
        float lado;
        float mitad;

    public:
        
        Dado(float f);
        void draw();
};

#endif // DADO_H