// Punto3D.h
#ifndef PUNTO3D_H
#define PUNTO3D_H

struct Punto3D {
    /**
     * @brief 
    */
    float x, y, z; // Representan las 3 coordenadas

    /**
     * @brief Constructor sin parámetros
    */
    Punto3D();
    
    /**
     * @brief Constructor con parámetros
    */
    Punto3D(float _x, float _y, float _z);

    // Sobrecarga de operadores
    Punto3D operator+(const Punto3D &p) const;
    Punto3D operator-(const Punto3D &p) const;
    Punto3D operator/(float div) const;

    // Producto vectorial
    Punto3D productoVectorial(const Punto3D &p) const;

    // Módulo de un vector
    float modulo() const;

    // Normalización
    void normaliza();
};

#endif // PUNTO3D_H