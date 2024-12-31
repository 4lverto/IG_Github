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

    /**
     * @brief Altura actual del cilindro (base del taburete)
    */
    extern float alturaCilindro;

    /**
     * @brief Ángulo de rotación actual del asiento
    */
    extern float rotacionAsiento;

    /**
     * @brief Ángulo de inclinación actual del respaldo
    */
    extern float inclinacionRespaldo;

    /**
     * @brief Indica si la animación automática está activa
    */
    extern bool animacionActiva;

    /**
     * @brief Velocidad de movimiento del cilindro (base del taburete)
    */
    extern float VEL_Cilindro;

    /**
     * @brief Velocidad de rotación del asiento
    */
    extern float VEL_Asiento;

    /**
     * @brief Velocidad de inclinación del respaldo
    */
    extern float VEL_Respaldo;

    /**
     * @brief Dibuja un taburete en la escena
     * @param id Identificador del taburete a dibujar
    */
    void dibujaTaburete(int id);

#endif // TABURETE_H