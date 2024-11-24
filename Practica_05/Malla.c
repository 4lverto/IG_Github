#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <utility>
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

void Malla::configuracionMaterial1(){
    asignarReflectividadAmbiente(0.25f,0.25f,0.25f,1.0f);
    asignarReflectividadDifusa(0.6f,0.6f,0.6f,1.0f);
    asignarReflectividadEspecular(0.9f,0.9f,0.9f,1.0f);
    asignarExponenteEspecular(100.0f);
}

void Malla::configuracionMaterial2(){
    asignarReflectividadAmbiente(0.2f,0.2f,0.2f,1.0f);
    asignarReflectividadDifusa(0.4f,0.4f,0.4f,1.0f);
    asignarReflectividadEspecular(0.1f,0.1f,0.1f,0.1f);
    asignarExponenteEspecular(10.0f);
}

void Malla::configuracionMaterial3(){
    asignarReflectividadAmbiente(0.15f,0.15f,0.15f,1.0f);
    asignarReflectividadDifusa(0.7f,0.7f,0.7f,1.0f);
    asignarReflectividadEspecular(0.5f,0.5f,0.5f,0.5f);
    asignarExponenteEspecular(50.0f);
}

// 2) 

void Malla::cargarTextura(const char *archivo){
    // Serán unsigned porque son los tipos de datos usados en lector-jpg.cpp
    unsigned width,height;
    unsigned char *imagen = LeerArchivoJPEG(archivo,width,height);

    if(!imagen){
        cout << "\nNo se ha cargado la imagen de textura \n";
        tieneTextura=false;
    }else{
        cout << "\nImagen para textura leida con éxito \n- " << archivo << "\n- Altura: " << height << "\n-Anchura: " << width << "\n\n";
    }

    glGenTextures(1,&texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imagen);

    delete[] imagen; // Liberamos la memoria usada

    tieneTextura=true; 
}

// 4) 

// Se definirá un punto de referencia desde el que se calculará la orientación de cada
// vértice en el espacio. Esencial para proyecciones cilíndricas y esféricas.
Punto3D Malla::calcularCentro(){
    Punto3D centro;
    
    // Sumo cada coordenada de cada vértice de mi malla y defino el centro haciendo
    // un promedio de cada una de estas coordenadas.
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

// Permite normalizar las coordenadas de los vértices de cada eje, de forma que todas
// las coordenadas de textrura (u,v) etarán en el rango [0,1]
void Malla::calcularCajaEnvolvente(Punto3D& min, Punto3D& max){

    if(vertices.empty()){
        cout << "\nERROR CCE -> No hay vertices\n";
        return;
    }

    // Establezco min y max al primer vértice de la malla
    // (podría ser cualquiera en realidad pero facilitira la iteración)
    min=vertices[0];
    max=vertices[0];

    // Recorro todos los vértices para encontrar la coordenada más alta y más baja,
    // que serán asignadas respectivamente a cada coordenada de min y max
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

    // En este momento, min y max representarán las "esquinas" de la caja envolvente
}

// Con los siguientes métodos calcularemos las coordenadas de textura usando diferentes proyecciones

void Malla::calculoCoordenadasTexturaCilindrica(){
    coordenadasTextura.clear();
    
    Punto3D centro=calcularCentro(); // Calculamos el centro geométrico
    
    Punto3D min,max;
    // Calculamos la caja envolvente para definir los límites del obejto en cada eje, facilitando 
    // la normalización de las coordenadas en el eje Y
    calcularCajaEnvolvente(min,max);
    
    float altura=max.y - min.y;

    for(size_t i=0; i<vertices.size(); ++i){

        // Calculo la distancia de las coordenadas X y Z de cada vértice respecto al centro calculado
        float dx = vertices[i].x - centro.x;
        float dz = vertices[i].z - centro.z;
        
        float distanciaXZ = sqrt(dx*dx + dz*dz);
        
        // Coordenada u -> Representa un ángulo aproximado en todno al eje Y de la malla
        float u = 0.5f + (dx/distanciaXZ) * 0.5f;

        // Coordenada v -> Se obtiene a partir de la posición Y de cada vértice, normalizada
        // dentro de la altura de la caja envolvente. Esto permite distribuir "v" en [0,1]
        float v = (vertices[i].y - min.y)/altura;
        
        // Almacenamos u,v como un par de valores
        pair<float,float> ct(u,v);
        coordenadasTextura.push_back(ct);
    }
}

void Malla::calculoCoordenadasTexturaPlano(){
    Punto3D min,max;
    calcularCajaEnvolvente(min,max);

    float ancho = max.x - min.x;
    float profundidad = max.z - min.z;

    for(int i=0;i<vertices.size();i++){
        float u=(vertices[i].x - min.x)/ancho;
        float v=(vertices[i].z - min.z)/profundidad;
    
        pair<float,float> ct(u,v);
        coordenadasTextura.push_back(ct);
    }   
}

void Malla::calculoCoordenadasTexturaEsfera(){
    Punto3D centro=calcularCentro();

    Punto3D min,max;

    calcularCajaEnvolvente(min,max);

    float altura=max.y - min.y;
    float radioMax = sqrt((max.x-centro.x) * (max.x-centro.x)) + ((max.y-centro.y)*(max.y-centro.y)) + ((max.z-centro.z)*(max.z-centro.z));

    for(int i=0;i<vertices.size();i++){
        float dx = vertices[i].x - centro.x;
        float dz = vertices[i].z - centro.z;
        float u = 0.5f + (dx/radioMax);

        float dy = vertices[i].y - centro.y;
        float distanciaV = sqrt(dx*dx + dy*dy + dz*dz);
        float v = 0.5f - (dy/distanciaV) * 0.5f;

        pair<float,float> ct(u,v);

        coordenadasTextura.push_back(ct);
    }
}

    // ============= //
    // OTROS MÉTODOS //
    // ============= //

// Constructores

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


void Malla::setSombreadoSuave(bool s){
    this->suave=s;
}


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


void Malla::draw(){
    
    /*
    if(iluminacionActivada){
        glEnable(GL_LIGHTING);
    }else{
        glDisable(GL_LIGHTING);
    }*/

    glEnable(GL_NORMALIZE);
    /*
    if(this->tieneTextura){
        // 3)
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId);

        // 1) 
        glMaterialfv(GL_FRONT, GL_AMBIENT, reflectividad_ambiente);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, reflectividad_difusa);
        glMaterialfv(GL_FRONT, GL_SPECULAR, reflectividad_especular);
        glMaterialf(GL_FRONT, GL_SHININESS, e);
    }*/

    if(this->suave){ // Si el atributo suave==TRUE, se dibujará con sombreado suave
        glShadeModel(GL_SMOOTH);
        this->drawSmooth();
    }else{ // Si el atributo suave==FALSE, se dibujará con sombreado plano
        glShadeModel(GL_FLAT);
        this->drawFlat();
    }
    /*
    if(this->tieneTextura){
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
    }*/
}


void Malla::drawFlat(){
    glBegin(GL_TRIANGLES);
    for(size_t i=0; i<this->caras.size();++i){ // Recorro todas las caras
        // Selecciono cada una de las caras
        Triangulo t = this->caras[i];

        // Doy la normal de la cara actual antes de enviar los vértices
        glNormal3f(this->normales_caras[i].x , this->normales_caras[i].y , this->normales_caras[i].z);
        
        // Práctica 4 - Asigno las coordenadas de textura
        if(tieneTextura){glTexCoord2f(coordenadasTextura[t.getI0()].first, coordenadasTextura[t.getI0()].second);};
        glVertex3f(this->vertices[t.getI0()].x , this->vertices[t.getI0()].y , this->vertices[t.getI0()].z);
        
        if(tieneTextura){glTexCoord2f(coordenadasTextura[t.getI1()].first, coordenadasTextura[t.getI1()].second);};
        glVertex3f(this->vertices[t.getI1()].x , this->vertices[t.getI1()].y , this->vertices[t.getI1()].z);
        
        if(tieneTextura){glTexCoord2f(coordenadasTextura[t.getI2()].first, coordenadasTextura[t.getI2()].second);};
        glVertex3f(this->vertices[t.getI2()].x , this->vertices[t.getI2()].y , this->vertices[t.getI2()].z);
    }

    glEnd();
}


void Malla::drawSmooth(){

    glBegin(GL_TRIANGLES);
    for(size_t i=0; i<this->caras.size();++i){ // Recorro todas las caras
        Triangulo t = this->caras[i]; // Selecciono cada una de las caras.
        
        // Práctica 4 - Asigno las coordenadas de textura
        if(tieneTextura){glTexCoord2f(coordenadasTextura[t.getI0()].first, coordenadasTextura[t.getI0()].second);};
        glNormal3f(this->normales_vertices[t.getI0()].x , this->normales_vertices[t.getI0()].y , this->normales_vertices[t.getI0()].z);
        glVertex3f(this->vertices[t.getI0()].x , this->vertices[t.getI0()].y , this->vertices[t.getI0()].z);
        
        if(tieneTextura){glTexCoord2f(coordenadasTextura[t.getI1()].first, coordenadasTextura[t.getI1()].second);};
        glNormal3f(this->normales_vertices[t.getI1()].x , this->normales_vertices[t.getI1()].y , this->normales_vertices[t.getI1()].z);
        glVertex3f(this->vertices[t.getI1()].x , this->vertices[t.getI1()].y , this->vertices[t.getI1()].z);
        
        if(tieneTextura){glTexCoord2f(coordenadasTextura[t.getI2()].first, coordenadasTextura[t.getI2()].second);};
        glNormal3f(this->normales_vertices[t.getI2()].x , this->normales_vertices[t.getI2()].y , this->normales_vertices[t.getI2()].z);
        glVertex3f(this->vertices[t.getI2()].x , this->vertices[t.getI2()].y , this->vertices[t.getI2()].z);
    }
    glEnd();
}