    // ///////// //
    // TRIÁNGULO //
    // ///////// //

#include <iostream>
#include "include/Triangulo.h"
#include <cmath>


/**
 * @brief Constructor sin parámetros. Construye un triángulo cuyos 3 índices de sus vértices son 0
 */
Triangulo::Triangulo(){
    this->v0=0;
    this->v1=0;
    this->v2=0;
}

/**
 * @brief Constructor con parámetros. Se establecen los 3 índices de los puntos que representarán cada vértice del triángulo
 * @param a Será el índice que corresponde al primer vértice
 * @param b Será el índice que corresponde al segundo vértice
 * @param c Será el índice que corresponde al tercer vértice
 * @return Triángulo compuesto por 3 índices de vértices determinados
 */
Triangulo::Triangulo(int a,int b,int c){
    this->v0=a;
    this->v1=b;
    this->v2=c;
}

/**
 * @brief Obtiene el índice del primer vértice
 * @return Índice del primer vértice
 */
int Triangulo::getI0(){
    return this->v0;
}

/**
 * @brief Obtiene el índice del segundo vértice
 * @return Índice del segundo vértice
 */
int Triangulo::getI1(){
    return this->v1;
}

/**
 * @brief Obtiene el índice del tercer vértice
 * @return Índice del tercer vértice
 */
int Triangulo::getI2(){
    return this->v2;
}