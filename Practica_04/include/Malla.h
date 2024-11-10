// Malla.h
#ifndef MALLA_H
#define MALLA_H

#include <vector>
#include "Punto3D.h"
#include "Triangulo.h"

using namespace std;

class Malla{
  public:
    
    // ///////// //
    // ATRIBUTOS // Diferenciaré entre los atributos añadidios para esta P4 y los que ya tenía
    // ///////// //

      // ========== //
      // PRÁCTICA 4 //
      // ========== //

    // 1) Añadir Materiales y textura a las mallas

    // Variables para almacenar las coordenadas de la luz para modificar el material
    GLfloat reflectividad_difusa[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat reflectividad_especular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat reflectividad_ambiente[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float e=0.0;

    // 2) Asignar una textura leída de un archivo a un objeto.

    // Identificador de la textura
    GLuint texId;

    // 4) Añadir coordenadas de textura a las mallas
    vector<pair<float,float>> coordenadasTextura;

    bool tieneTextura=false; // Será true si la Malla tiene una textura asociada y false en caso contrario

      // =============== //
      // OTROS ATRIBUTOS // 
      // =============== //

    vector<float> vertices_ply;  // Coordenadas de los vértices
    vector<int> caras_ply;       // Índices de los vértices (caras)

    vector<Punto3D> normales_caras;    // Normales de las caras
    vector<Punto3D> normales_vertices; // Normales de los vértices

    vector<Punto3D> vertices;    // Vértices como objetos Punto3D
    vector<Triangulo> caras;     // Caras como objetos Triangulo

    bool suave;  // True: sombreado suave, False: sombreado plano
  
// /////// //
// MÉTODOS // Diferenciaré entre los métodos desarrollador para esta P4 y los que ya tenía
// /////// //

    // ========== //
    // PRÁCTICA 4 //
    // ========== //

    // 1) Añadir Materiales y textura a las mallas

    void asignarReflectividadDifusa(GLfloat r, GLfloat g, GLfloat b, GLfloat alfa=1.0f);
    void asignarReflectividadEspecular(GLfloat r, GLfloat g, GLfloat b, GLfloat alfa=1.0f);
    void asignarReflectividadAmbiente(GLfloat r, GLfloat g, GLfloat b, GLfloat alfa=1.0f);
    void asignarExponenteEspecular(float exp=0.0);

    // Para que se aprecie bien la diferencia de materiales que le asignaré a las mallas que 
    // dibujo, he creado 3 configuraciones con combinaciones de reflectividades muy distintas:
    void configuracionMaterial1();
    void configuracionMaterial2();
    void configuracionMaterial3();

    // 2) Asignar una textura leída de un archivo a un objeto.

    void cargarTextura(const char *archivo);

    // 4) Añadir coordenadas de textura a las mallas mediante cálculo procedural
    Punto3D calcularCentro();
    void calcularCajaEnvolvente(Punto3D &min, Punto3D &max);

      // Implementaré los 3 métodos de cálculo de coordenadas de textura según las proyecciones:
    
    void calculoCoordenadasTexturaPlano();
    void calculoCoordenadasTexturaEsfera(); 
    void calculoCoordenadasTexturaCilindrica();

    // ============= //
    // OTROS MÉTODOS //
    // ============= //

    // Constructores

    /**
     * @brief Constructor sin parámetros. Por defecto se construye una malla que forma un cubo dibujado con sombreado plano.
     * @return Malla de un cubo que se dibuja con sombreado plano.
    */
    Malla();  // Constructor sin parámetros (cubo por defecto)
    
    /**
     * @brief Constructor con parámetros. Construye una malla a partir de un archivo y establece su tipo de sombreado
     * @param nombre_archivo Nombre del archivo que va a representar la malla
     * @param sombreadoSuave TRUE si queremos usar sombreado SMOOTH. FALSE si queremos usar sombreado FLAT
    */
    Malla(const char* nombre_archivo, bool sombreadoSuave); // Constructor con archivo

    // Resto de métodos

    /**
     * @brief Modifica el tipo de sombreado
     * @param s True si se usa sombreado Smooth. False si se usa sombreado Flat
    */
    void setSombreadoSuave(bool s);

    /**
     * @brief Función para calcular las normales de las caras.
     * @post El vector normales_caras contendrá todas las normales de las caras almacenadas en el vector caras
    */
    void calcular_normales_caras();

    /**
     * @brief Función para calcular las normales de los vértices.
     * @post El vector normales_vertices contendrá las normales de todos los vértices almacenados en vertices
    */    
    void calcular_normales_vertices();

    /**
     * @brief Función para dibujar en función del sombreado
     * (Podríamos tener las 3 funciones integradas en este método, pero así aumentamos el encapsulamiento)
    */
    void draw();

    /**
     * @brief Función para dibujar la malla en modo FLAT.
     * La iluminación de la cara se calcula con la normal que se le pasa a OpenGL antes del último vértice
     * de la cara. 
     * Por tanto, tenemos que dar la normal de cada cara con glNormal3f(...) antes de que se envíe el último
     * vértice de la cara. Es decir, el orden sería:
     * 
     * normalcara
     * vertice1
     * vertice2
     * vertice3
    */
    void drawFlat();

    /**
     * @brief Función para dibujar la malla en modo SMOOTH
     * Deberemos dar la normal de cada vértice justo antes de enviar el vértice. Es decir, el orden seŕia:
     * 
     * normalVertice1
     * vertice1
     * normalVertice2
     * vertice2
     * normalVertice3
     * vertice3
    */
    void drawSmooth();

};

#endif // MALLA_H