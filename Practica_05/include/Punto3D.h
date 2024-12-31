// Punto3D.h
#ifndef PUNTO3D_H
#define PUNTO3D_H

/**
 * @brief Estrutura que representa un punto o vector en un espacio tridimensional
*/
struct Punto3D {
    /**
     * @brief Coordenadas del punto o vector
    */
    float x, y, z;

    /**
     * @brief Constructor sin parámetros (por defecto). Inicializa el punto en (0,0,0)
    */
    Punto3D();
    
    /**
     * @brief Constructor con parámetros
     * @param _x Coordenada X del punto
     * @param _y Coordenada Y del punto
     * @param _z Coordenada Z del punto
     * 
    */
    Punto3D(float _x, float _y, float _z);

    /**
     * @brief Sobrecarga de operador +
     * @param p Punto o vector a sumar
     * @return Punto3D Resultado de la suma
    */
    Punto3D operator+(const Punto3D &p) const;

    /**
     * @brief Sobrecarga de operador -
     * @param p Punto o vector a restar
     * @return Punto3D Resultado de la resta
    */
    Punto3D operator-(const Punto3D &p) const;
    
    /**
     * @brief Sobrecarga de operador /
     * @param div Punto o vector a dividir
     * @return Punto3D Resultado de la división
    */
    Punto3D operator/(float div) const;

    /**
     * @brief Producto vectorial entre 2 vectores
     * @param p Vector con el que se calcula el producto vectorial
     * @return Punto3D Resultado del producto vectorial
    */
    Punto3D productoVectorial(const Punto3D &p) const;

    /**
     * @brief Módulo de un vector
     * @return Módulo del vector
    */
    float modulo() const;

    /**
     * @brief Normaliza el vector ajustando el módulo a 1
    */
    void normaliza();
};

#endif // PUNTO3D_H