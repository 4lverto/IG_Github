// Malla.h
#ifndef MALLA_H
#define MALLA_H

#include <vector>
#include "Punto3D.h"
#include "Triangulo.h"

using namespace std;

class Malla {
  public:
    // Atributos
    vector<float> vertices_ply;  // Coordenadas de los vértices
    vector<int> caras_ply;       // Índices de los vértices (caras)

    vector<Punto3D> normales_caras;    // Normales de las caras
    vector<Punto3D> normales_vertices; // Normales de los vértices

    vector<Punto3D> vertices;    // Vértices como objetos Punto3D
    vector<Triangulo> caras;     // Caras como objetos Triangulo

    bool suave;  // True: sombreado suave, False: sombreado plano

    // PRÁCTICA 4
    // Variables para almacenar las coordenadas de la luz

    // Variables para los materiales
    GLfloat reflectividad_difusa[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat reflectividad_especular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat reflectividad_ambiente[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

    void asignarReflectividadDifusa(GLfloat r, GLfloat g, GLfloat b, GLfloat alfa=1.0f);
    void asignarReflectividadEspecular(GLfloat r, GLfloat g, GLfloat b, GLfloat alfa=1.0f);
    void asignarReflectividadAmbiente(GLfloat r, GLfloat g, GLfloat b, GLfloat alfa=1.0f);
    
    // Constructores
    Malla();  // Constructor sin parámetros (cubo por defecto)
    Malla(const char* nombre_archivo, bool sombreadoSuave); // Constructor con archivo

    // Métodos
    void setSombreadoSuave(bool s);
    void calcular_normales_caras();
    void calcular_normales_vertices();
    void draw();
    void drawFlat();
    void drawSmooth();
};

#endif // MALLA_H