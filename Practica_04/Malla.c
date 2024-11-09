#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <utility>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "include/practicasIG.h"

using namespace std;
// MÉTODOS

// ////////// //
// PRÁCTICA 4 //
// ////////// //

// 1)
void Malla::asignarReflectividadDifusa(GLfloat r, GLfloat g, GLfloat b, GLfloat alfa){
    reflectividad_difusa[0]=r;
    reflectividad_difusa[1]=g;
    reflectividad_difusa[2]=b;
    reflectividad_difusa[3]=alfa;

    // Hacemos que la reflectividad ambiente sea igual que la difusa
    // a menos de que la reflectividad_ambiente sea establecida, en 
    // cuyo caso se sobreescribirán estos valores.
    reflectividad_ambiente[0]=reflectividad_difusa[0];
    reflectividad_ambiente[1]=reflectividad_difusa[1];
    reflectividad_ambiente[2]=reflectividad_difusa[2];
    reflectividad_ambiente[3]=reflectividad_difusa[3];
}

void Malla::asignarReflectividadEspecular(GLfloat r, GLfloat g, GLfloat b, GLfloat alfa){
    reflectividad_especular[0]=r;
    reflectividad_especular[1]=g;
    reflectividad_especular[2]=b;
    reflectividad_especular[3]=alfa;
}

void Malla::asignarReflectividadAmbiente(GLfloat r, GLfloat g, GLfloat b, GLfloat alfa){
    reflectividad_ambiente[0]=r;
    reflectividad_ambiente[1]=g;
    reflectividad_ambiente[2]=b;
    reflectividad_ambiente[3]=alfa;
}


void Malla::asignarExponenteEspecular(float exp){
    e=exp;
}

// 2) 

void Malla::cargarTextura(const char *archivo){
    // Serán unsigned porque son los tipos de datos usados en lector-jpg.cpp
    unsigned width,height;
    unsigned char *imagen = LeerArchivoJPEG(archivo,width,height);

    if(!imagen){
        cerr << "\nError: No se ha cargado la imagen de textura \n";
        return;
    }else{
        cout << "\nImagen para textura leida con éxito \n-Altura: " << height << "\n-Anchura: " << width << "\n\n";
    }

    glGenTextures(1,&texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen);

    delete[] imagen; // Liberamos la memoria RAM usada
}

// 4) 

Punto3D Malla::calcularCentro(){
    Punto3D centro;
    
    for(int i=0;i<vertices.size();i++){
        Punto3D v=vertices[i];

        centro.x += v.x;
        centro.y += v.y;
        centro.z += v.z;
    }

    centro.x = centro.x/vertices.size();
    centro.y = centro.y/vertices.size();
    centro.z = centro.z/vertices.size();

    return centro;
}


void Malla::calcularCajaEnvolvente(Punto3D& min, Punto3D& max){

    if(vertices.empty()){
        cout << "\nERROR CCE -> No hay vertices\n";
        return;
    }

    min=vertices[0];
    max=vertices[0];

    for(int i=1;i<vertices.size();i++){
        if(vertices[i].x < min.x){
            min.x=vertices[i].x;
        }

        if(vertices[i].x > max.x){
            max.x=vertices[i].x;
        }

        if(vertices[i].y < min.y){
            min.y=vertices[i].y;
        }

        if(vertices[i].y > max.y){
            max.y=vertices[i].y;
        }

        if(vertices[i].z < min.z){
            min.z=vertices[i].z;
        }

        if(vertices[i].z > max.z){
            max.z=vertices[i].z;
        }
    }
}

// Con los siguientes métodos calcularemos las coordenadas de textura usando diferentes proyecciones



void Malla::calculoCoordenadasTexturaCilindrica(){
    coordenadasTextura.clear();
    
    Punto3D centro=calcularCentro();
    Punto3D min,max;
    calcularCajaEnvolvente(min,max);
    
    float altura=max.y - min.y;

    for(size_t i=0; i<vertices.size(); ++i){
        float dx = vertices[i].x - centro.x;
        float dz = vertices[i].z - centro.z;

        float distanciaXZ = sqrt(dx*dx + dz*dz);

        float u = 0.5f + (dx/distanciaXZ) * 0.5f;
        float v = (vertices[i].y - min.y)/altura;

        pair<float,float> ct(u,v);
        coordenadasTextura.push_back(ct);
    }
}

// //////////////// //
// RESTO DE MÉTODOS //
// //////////////// //

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
    
    glEnable(GL_LIGHTING);
    
    // 3)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    // 1) 
    glMaterialfv(GL_FRONT, GL_AMBIENT, reflectividad_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, reflectividad_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, reflectividad_especular);
    glMaterialf(GL_FRONT, GL_SHININESS,e);

    if(this->suave){ // Si el atributo suave==TRUE, se dibujará con sombreado suave
        glShadeModel(GL_SMOOTH);
        this->drawSmooth();
    }else{ // Si el atributo suave==FALSE, se dibujará con sombreado plano
        glShadeModel(GL_FLAT);
        this->drawFlat();
    }
    
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
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
        
        // Práctica 4 - Asigno las coordenadas de textura
        glTexCoord2f(coordenadasTextura[t.getI0()].first, coordenadasTextura[t.getI0()].second);
        glVertex3f(this->vertices[t.getI0()].x , this->vertices[t.getI0()].y , this->vertices[t.getI0()].z);
        
        glTexCoord2f(coordenadasTextura[t.getI1()].first, coordenadasTextura[t.getI1()].second);
        glVertex3f(this->vertices[t.getI1()].x , this->vertices[t.getI1()].y , this->vertices[t.getI1()].z);
        
        glTexCoord2f(coordenadasTextura[t.getI2()].first, coordenadasTextura[t.getI2()].second);
        glVertex3f(this->vertices[t.getI2()].x , this->vertices[t.getI2()].y , this->vertices[t.getI2()].z);
        
        // Práctica 2 
        /*
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
        }*/
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
        
        // Práctica 4 - Asigno las coordenadas de textura
        glTexCoord2f(coordenadasTextura[t.getI0()].first, coordenadasTextura[t.getI0()].second);
        glNormal3f(this->normales_vertices[t.getI0()].x , this->normales_vertices[t.getI0()].y , this->normales_vertices[t.getI0()].z);
        glVertex3f(this->vertices[t.getI0()].x , this->vertices[t.getI0()].y , this->vertices[t.getI0()].z);
        
        glTexCoord2f(coordenadasTextura[t.getI1()].first, coordenadasTextura[t.getI1()].second);
        glNormal3f(this->normales_vertices[t.getI1()].x , this->normales_vertices[t.getI1()].y , this->normales_vertices[t.getI1()].z);
        glVertex3f(this->vertices[t.getI1()].x , this->vertices[t.getI1()].y , this->vertices[t.getI1()].z);
        
        glTexCoord2f(coordenadasTextura[t.getI2()].first, coordenadasTextura[t.getI2()].second);
        glNormal3f(this->normales_vertices[t.getI2()].x , this->normales_vertices[t.getI2()].y , this->normales_vertices[t.getI2()].z);
        glVertex3f(this->vertices[t.getI2()].x , this->vertices[t.getI2()].y , this->vertices[t.getI2()].z);


        // Práctica 2
        /*
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
        }*/
    }
    glEnd();
}