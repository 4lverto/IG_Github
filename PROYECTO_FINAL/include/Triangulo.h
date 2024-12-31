// Triangulo.h
#ifndef TRIANGULO_H
#define TRIANGULO_H

/**
 * @brief Estructura que representa un triángulo mediante los índices de sus 3 vértices
*/
struct Triangulo {

    /**
     * @brief Índices del primer vértice del triángulo
    */
    int v0, v1, v2;

    /**
     * @brief Constructor sin parámetros (por defecto). Inicializa los índices de los vértices a 0
    */
    Triangulo();

    /**
     * @brief Constructor con parámetros. Inicializa los índices de los vértices
     * @param a Índice del primer vértice
     * @param b Índice del segundo vértice
     * @param c Índice del tercer vértice
    */
    Triangulo(int a, int b, int c);

    /**
     * @brief Obtiene el índice del primer vértice del triángulo
     * @return Índice del primer vértice
    */
    int getI0();

    /**
     * @brief Obtiene el índice del segundo vértice del triángulo
     * @return Índice del segundo vértice
    */
    int getI1();

    /**
     * @brief Obtiene el índice del tercer vértice del triángulo
     * @return Índice del tercer vértice
    */
    int getI2();
};

#endif // TRIANGULO_H