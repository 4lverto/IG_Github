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
         * @brief Identificador de color del dado
        */
       int id;

       /**
        * @brief Cara actual resultante de lanzar el dado
       */
      int caraVisible;

    public:
        /**
         * @brief Constructor de un dado (cubo) a partir de un tamaño de lado dado
         * @param f Será la longitud del lado
         * @param id
         * @param c
        */
        Dado(float f,int id,int c);

        /**
         * @brief Función "sobrecargada" de la clase Malla donde creo mi dado.
        */
        void draw();


        /**
         * @brief Obtiene la cara resultante del dado actual
        */
        int getCaraVisible();

        /**
         * @brief Establece el resultado de lanzar el dado
         * @param c Nuevo resultado del dado
        */
       void setCaraVisible(int c);
};

#endif // DADO_H