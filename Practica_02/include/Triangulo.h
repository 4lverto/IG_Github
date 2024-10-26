// Triangulo.h
#ifndef TRIANGULO_H
#define TRIANGULO_H

struct Triangulo {
    int v0, v1, v2; // Índices de los vértices

    // Constructor sin parámetros
    Triangulo();

    // Constructor con parámetros
    Triangulo(int a, int b, int c);

    // Getters para los índices de los vértices
    int getI0();
    int getI1();
    int getI2();
};

#endif // TRIANGULO_H