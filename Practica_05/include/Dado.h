// Dado.h
#ifndef DADO_H
#define DADO_H

#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include <vector>
#include "Malla.h"

class Dado : public Malla{

    private:
        /**
         * @brief Lado del dado
        */
        float lado;

        /**
         * @brief Mitad del lado del dado
        */
        float mitad;

        /**
         * 
        */
       int id;

    public:
        /**
         * @brief Constructor de un dado (cubo) a partir de un tamaño de lado dado
         * @param f Será la longitud del lado
        */
        Dado(float f,int id);

        /**
         * @brief Función "sobrecargada" de la clase Malla donde creo mi dado.
        */
        void draw();

        /**
         * @brief Función que simulará la acción de lanzar el dado
        */
       // void lanzar();
};

#endif // DADO_H