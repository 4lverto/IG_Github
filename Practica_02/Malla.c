#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "include/practicasIG.h"

using namespace std;
// MÉTODOS

/**
 * @brief Constructor sin parámetros. Por defecto se construye una malla que forma un cubo dibujado con sombreado plano.
 * @return Malla de un cubo que se dibuja con sombreado plano.
*/
Malla::Malla(){
    this->suave=false;
    ply::read("plys/cubo.ply",vertices_ply,caras_ply);

    // Vuelco el vector de vértices_ply en otro vector en el que cada componente representa un Punto3D
    for(size_t i=0;i<vertices_ply.size();i+=3){
    Punto3D v(vertices_ply[i],vertices_ply[i+1],vertices_ply[i+2]);
    vertices.push_back(v);
    }

    // Vuelco el vector de caras_ply en otro vector en el que cada componente representa un trío de índices (cada índice representará un Punto3D)
    for(size_t i=0;i<caras_ply.size();i+=3){
    Triangulo t(caras_ply[i],caras_ply[i+1],caras_ply[i+2]);
    caras.push_back(t);
    }

    // Calculamos las normales directamente para tenerlas disponibles nada más construir el objeto
    calcular_normales_caras();
    calcular_normales_vertices();
}

/**
 * @brief Constructor con parámetros. Construye una malla a partir de un archivo y establece su tipo de sombreado
 * @param nombre_archivo Nombre del archivo que va a representar la malla
 * @param sombreadoSuave TRUE si queremos usar sombreado SMOOTH. FALSE si queremos usar sombreado FLAT
*/
Malla::Malla(const char *nombre_archivo,bool sombreadoSuave){
    this->suave=sombreadoSuave;
    ply::read(nombre_archivo,vertices_ply,caras_ply);
    
    // Vuelco el vector de vértices_ply en otro vector en el que cada componente representa un Punto3D
    for(size_t i=0;i<vertices_ply.size();i+=3){
    Punto3D v(vertices_ply[i],vertices_ply[i+1],vertices_ply[i+2]);
    vertices.push_back(v);
    }

    // Vuelco el vector de caras_ply en otro vector en el que cada componente representa un trío de índices (cada índice representará un Punto3D)
    for(size_t i=0;i<caras_ply.size();i+=3){
    Triangulo t(caras_ply[i],caras_ply[i+1],caras_ply[i+2]);
    caras.push_back(t);
    }

    // Calculamos las normales directamente para tenerlas disponibles nada más construir el objeto
    calcular_normales_caras();
    calcular_normales_vertices();
}

/**
 * @brief Modifica el tipo de sombreado
 * @param s True si se usa sombreado Smooth. False si se usa sombreado Flat
*/
void Malla::setSombreadoSuave(bool s){
    this->suave=s;
}

/**
 * @brief Función para calcular las normales de las caras.
 * @post El vector normales_caras contendrá todas las normales de las caras almacenadas en el vector caras
*/
void Malla::calcular_normales_caras(){
    
    // Limpio el vector<Triangulo> normales_caras
    this->normales_caras.clear();

    // Almaceno tantos puntos "vacíos" (0,0,0) como caras haya (cada punto representará la normal de esa cara)
    for(size_t i = 0;i<caras.size();i++){
    this->normales_caras.push_back(Punto3D());
    }

    // Calculo la normal de cada cara y la almaceno en vector<Punto3D> normales_caras
    for(size_t i = 0; i<caras.size(); i++){
    // Obtengo cada triángulo (cara)
    Triangulo t=caras[i];

    // Obtengo los 3 vértices del triángulo a partir de sus índices
    Punto3D P0=this->vertices[t.getI0()];
    Punto3D P1=this->vertices[t.getI1()];
    Punto3D P2=this->vertices[t.getI2()];
    
    // Calculo los vectores de los lados del triángulo
    Punto3D V1=(P1-P0);
    Punto3D V2=(P2-P0);

    // Calculo el producto vectorial (V1 x V2) para obtener la normal
    Punto3D normal = V1.productoVectorial(V2);

    // Normalizo la normal para que tenga longitud 1
    normal.normaliza();

    // Almacenamos la normal
    this->normales_caras[i]=normal;
    }
}

/**
 * @brief Función para calcular las normales de los vértices.
 * @post El vector normales_vertices contendrá las normales de todos los vértices almacenados en vertices
*/
void Malla::calcular_normales_vertices(){

    // Vaciamos el vector de normales de vértices
    this->normales_vertices.clear();

    // Añadimos puntos vacíos (que representarán las normales)
    for(size_t i = 0;i<this->vertices.size();i++){
    this->normales_vertices.push_back(Punto3D());
    }

    // Calculamos cada normal de cada vértice iterando sobre las caras, por lo que por cada iteración
    // actualizamos la normal de 3 vértices. Cuando el bucle finalice, significará que todos los componentes
    // de vector<Punto3D> normales_vertices tiene sumadas todas las normales de las caras que compone
    for(size_t i=0;i<this->caras.size();++i){

    // Para cada triángulo, obtengo su normal (la normal de la cara)
    Triangulo t = this->caras[i]; // Ejemplo: t(0,1,2) significará que t.i0=0, t.i1=1, t.i2=2
    
    // Obtengo la normal de la cara actual que estamos procesando (ya se calcularon anteriormente)
    Punto3D normal_triangulo= this->normales_caras[i];

    // La normal de esa cara se sumará a las normales de los 3 vértices que componen el triángulo que estamos procesando
    this->normales_vertices[t.getI0()] = this->normales_vertices[t.getI0()] + normal_triangulo;
    this->normales_vertices[t.getI1()] = this->normales_vertices[t.getI1()] + normal_triangulo;
    this->normales_vertices[t.getI2()] = this->normales_vertices[t.getI2()] + normal_triangulo;
    }

    // Normaliza todas las normales de los vértices para que tengan longitud 1
    for(size_t i=0; i<this->normales_vertices.size(); i++){
    this->normales_vertices[i].normaliza();
    }
}

/**
 * @brief Función para dibujar en función del sombreado
 * (Podríamos tener las 3 funciones integradas en este método, pero así aumentamos el encapsulamiento)
*/
void Malla::draw(){
    if(this->suave){ // Si el atributo suave==TRUE, se dibujará con sombreado suave
    glShadeModel(GL_SMOOTH);
    this->drawSmooth();
    }else{ // Si el atributo suave==FALSE, se dibujará con sombreado plano
    glShadeModel(GL_FLAT);
    this->drawFlat();
    }
}

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
void Malla::drawFlat(){
    glBegin(GL_TRIANGLES);
    for(size_t i=0; i<this->caras.size();++i){ // Recorro todas las caras
    // Selecciono cada una de las caras
    Triangulo t = this->caras[i];

    // Doy la normal de la cara actual antes de enviar los vértices
    glNormal3f(this->normales_caras[i].x , this->normales_caras[i].y , this->normales_caras[i].z);
    
    // Envío los 3 vértices (podría hacerlo usando glVertex3f(...) 3 veces)
    for(int j=0;j<3;++j){
        int indice;

        if(j==0){
        indice=t.getI0();
        }else if(j==1){
        indice=t.getI1();
        }else{
        indice=t.getI2();
        }

        // Doy un vértice en cada iteración hasta pasar los 3 Punto3D(x,y,z)
        glVertex3f(this->vertices[indice].x , this->vertices[indice].y , this->vertices[indice].z);
    }
    }
    glEnd();
}

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
void Malla::drawSmooth(){

    glBegin(GL_TRIANGLES);
    for(size_t i=0; i<this->caras.size();++i){ // Recorro todas las caras
    Triangulo t = this->caras[i]; // Selecciono cada una de las caras.

    // Mando a dibujar los 3 vértices de cada triángulo a partir de los 3 índices del triángulo actual
    for(int j=0;j<3;++j){
        int indice;

        if(j==0){
        indice=t.getI0();
        }else if(j==1){
        indice=t.getI1();
        }else{
        indice=t.getI2();
        }
        
        // Antes de enviar cada vértice a dibujar, deberemos dar su normal (la del vértice)
        glNormal3f(this->normales_vertices[indice].x , this->normales_vertices[indice].y , this->normales_vertices[indice].z);
        glVertex3f(this->vertices[indice].x , this->vertices[indice].y , this->vertices[indice].z);
    }
    }
    glEnd();
}