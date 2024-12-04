#ifndef TABURETE_H
#define TABURETE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "Asiento.h"
#include "Cilindro.h"
#include "Respaldo.h"

using namespace std;

// Variables globales para controlar las transformaciones:

    extern float alturaCilindro;
    extern float rotacionAsiento;
    extern float inclinacionRespaldo;

    extern bool animacionActiva;
    extern float VEL_Cilindro;
    extern float VEL_Asiento;
    extern float VEL_Respaldo;

    void dibujaTaburete(int id);

#endif // TABURETE_H