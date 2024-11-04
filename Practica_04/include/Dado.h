// Dado.h
#ifndef DADO_H
#define DADO_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include <vector>
#include "practicasIG.h"


class Dado:Objeto3D{
    private:
        GLuint texId;

    public:
        
        Dado();
        Dado(GLuint texId);
        void cargarTextura(const char *archivo);
        void draw();
};

#endif // DADO_H