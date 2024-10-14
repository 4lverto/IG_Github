    // /////// //
    // PUNTO3D //
    // /////// //

#include <iostream>
#include<cmath>
#include "include/Punto3D.h"

using namespace std;

// MÉTODOS DEFINIDOS

/**
 * @brief Constructor sin parámetros. Crea un Punto3D con todas las coordenadas a 0
 */

Punto3D::Punto3D(){
    this->x=0;
    this->y=0;
    this->z=0;
}

/**
 * @brief Constructor con parámetros. 
 * @param _x Coordenada X
 * @param _y Coordenada Y
 * @param _z Coordenada Z
 */
Punto3D::Punto3D(float _x, float _y, float _z){
    this->x=_x;
    this->y=_y;
    this->z=_z;
}

/**
 * @brief Sobrecarga del operador de suma. Suma cada coordenada con la coordenada correspondiente del Punto3D pasado como parámetro
 * @param p Es un Punto3D dado
 * @return El punto con las coordenadas actualizadas
 */
Punto3D Punto3D::operator+(const Punto3D &p) const{
    Punto3D miPunto(this->x + p.x , this->y + p.y , this->z + p.z);
    return miPunto;
}

/**
 * @brief Sobrecarga del operador de resta. Resta cada coordenada con la coordenada correspondiente del Punto3D pasado como parámetro
 * @param p Es un Punto3D dado
 * @return El punto con las coordenadas actualizadas
 */
Punto3D Punto3D::operator-(const Punto3D &p) const{
    Punto3D miPunto(this->x - p.x , this->y - p.y , this->z - p.z);
    return miPunto;
}

/**
 * @brief Sobrecarga del operador de división. Suma cada coordenada con la coordenada correspondiente del Punto3D pasado como parámetro
 * @param p Es un Punto3D dado
 * @return El punto con las coordenadas actualizadas
 */
Punto3D Punto3D::operator/(float div) const{
    Punto3D miPunto(this->x/div , this->y/div , this->z/div);
    return miPunto;
}

/**
 * @brief Se realiza el producto vectorial entre los dos puntos (el actual y el pasado como parámetro)
 * @param p Punto con el que se hace el producto vectorial
 * @return Punto con las coordenadas actualizadas tras el producto vectorial
 */
Punto3D Punto3D::productoVectorial(const Punto3D &p) const{
    Punto3D miPunto;
    miPunto.x = (this->y*p.z)-(this->z*p.y);
    miPunto.y = (this->z*p.x)-(this->x*p.z);
    miPunto.z = (this->x*p.y)-(this->y*p.x);

    return miPunto;
}

/**
 * @brief Función que calculará el módulo del Punto3D
 * @pre El módulo no debe ser 0
 * @return Módulo del Punto3D
 */
float Punto3D::modulo() const{
    // Calculamos los "cuadrados" de las coordenadas
    float equis=this->x * this->x;
    float igriega=this->y * this->y;
    float ceta=this->z * this->z;

    float modulo=sqrt(equis+igriega+ceta);

    if(modulo==0){
        cout << "\n OJO!! El módulo es 0, luego no se va a dividir bien \n";
    }

    return modulo;
    }

/**
 * @brief Función que finalmente normaliza el Punto3D dividiendo cada coordenada entre el módulo
 */
void Punto3D::normaliza(){
float modulo=this->modulo();

    if(modulo!=0){
        this->x = this->x/modulo;
        this->y = this->y/modulo;
        this->z = this->z/modulo;
    }
}
