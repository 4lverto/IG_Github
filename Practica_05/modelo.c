#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "include/practicasIG.h"
#include <vector>
#include <stdbool.h>

using namespace std;

// PRÁCTICA 2 - Mallas con PLYs

Malla beethoven("plys/beethoven.ply",true,ID_BEETHOVEN);
Malla big_dodge("plys/big_dodge.ply",false,ID_BIG_DODGE);

// PRÁCTICA 3 - Componentes de mi modelo jerárquico articulado

bool animacionActiva=false; // Se gestiona con A y a
float VEL_Cilindro=0.01f;   // Se gestiona con T y G
float VEL_Asiento=0.5f;     // Se gestiona con Y y H
float VEL_Respaldo=0.1f;    // Se gestiona con U y J

// PRÁCTICA 4 - Mallas a dibujar y Dado

Dado dado(4.0f); // Dado "hereda" de Malla
Malla coche1("plys/big_dodge.ply",false,ID_COCHE1); // Reflectividad difusa
Malla coche2("plys/big_dodge.ply",false,ID_COCHE2); // Reflectividad ambiente
Malla coche3("plys/big_dodge.ply",false,ID_COCHE3); // Reflectividad especular

// PRÁCTICA 4 - Dos focos de luz distintos

GLfloat posLuz1[4] = {5.0,5.0,10.0,0.0}; // Será el foco de luz por defecto (la que hemos tenido hasta ahora)
GLfloat posLuz2[4] = {-5.0,10.0,-5.0,1.0};

bool luzActiva=true;

/**
 * @brief Inicializa el modelo y de las variables globales
*/
void
initModel (){

  // ////////// //
  // Práctica 2 //
  // ////////// //
  beethoven.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  beethoven.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  beethoven.asignarExponenteEspecular(49.0f);

  big_dodge.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  big_dodge.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  big_dodge.asignarExponenteEspecular(49.0f);

  // ////////// //
  // Práctica 4 //
  // ////////// //

  dado.cargarTextura("JPEG/dado.jpg");
  dado.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  dado.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  dado.asignarExponenteEspecular(49.0f);
  dado.setSombreadoSuave(true);

  coche1.cargarTextura("JPEG/texturaMarmol.jpg");
  coche1.calculoCoordenadasTexturaCilindrica();
  coche1.configuracionMaterial1();
  coche1.setSombreadoSuave(true);

  coche2.cargarTextura("JPEG/texturaMarmol.jpg");
  coche2.calculoCoordenadasTexturaCilindrica();
  coche2.configuracionMaterial2();
  coche2.setSombreadoSuave(true);

  coche3.configuracionMaterial3();
  coche3.setSombreadoSuave(true);
}

                  // /////////////// //
                  // "SUBCLASE" EJES //
                  // /////////////// //

class Ejes:Objeto3D { 
  public: 
      float longitud = 30;
  // Dibuja el objeto
  void draw( ){
    glBegin (GL_LINES);
    {
      glColor3f (0, 1, 0);
      glVertex3f (0, 0, 0);
      glVertex3f (0, longitud, 0);

      glColor3f (1, 0, 0);
      glVertex3f (0, 0, 0);
      glVertex3f (longitud, 0, 0);

      glColor3f (0, 0, 1);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, longitud);
    }
    glEnd ();
  }
}; 

                    // ////////////////// //
                    // PROGRAMA PRINCIPAL //
                    // ////////////////// //

Ejes ejesCoordenadas;
int modo=GL_FILL;
bool iluminacionActivada=true;

/**
 *  @brief Función para gestionar el Modo de visualización de las figuras
*/
void setModo(int M){
  if(M==1){
    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
  }else if(M==2){
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  }else if(M==3){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  }
}

/**
 *  @brief Función para gestionar la iluminación de las figuras
*/
void setIluminacion(){
  iluminacionActivada = !iluminacionActivada;
  
  if(iluminacionActivada){
    glEnable(GL_LIGHTING);
  }else{
    glDisable(GL_LIGHTING);
  }
}

// //////////
// PRÁCTICA 4 - Alternar entre los focos de luz definidos. Tecla W
// //////////

void establecerLuzActiva(){

  luzActiva = !luzActiva;

  if(luzActiva){
    glLightfv(GL_LIGHT0,GL_POSITION,posLuz1);
  }else{
    glLightfv(GL_LIGHT0,GL_POSITION,posLuz2);
  }

  glutPostRedisplay();
}

                                // ////////// //
                                // PRÁCTICA 5 //
                                // ////////// //

int objetoSeleccionado=-1;
bool modoSeleccion=false;

bool getModoSeleccion(){
  return modoSeleccion;
}

void setModoSeleccion(bool s){
  modoSeleccion=s;
}

// Implemento colorSeleccion //
// ///////////////////////// //

void colorSeleccion(int id/*, int componente*/){
  unsigned char r = id & 0xFF;
  unsigned char g = (id >> 8) & 0xFF;
  glColor3ub(r,g,0);
}

// Creo dibujoEscena() a partir de lo que contenía Dibuja() //
// //////////////////////////////////////////////////////// //

void dibujaEscena() {

    float morado[4]={0.8,0,1,1};
    float verde[4]={0,1,0,1};
    float rojo[4]={1,0,0,1};

    glPushMatrix();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // Configura la transformación de visualización
    transformacionVisualizacion();

    // Dibujar los ejes (sin iluminación)
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING);
    ejesCoordenadas.draw();
    glPopAttrib();

    // Práctica 4 y 5
    glPushMatrix();
    if(getModoSeleccion()){
      colorSeleccion(ID_DADO);
    }
    dado.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.0,0.0,-10.0);
    if(getModoSeleccion()){
      colorSeleccion(ID_COCHE1);
    }
    coche1.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.0,0.0,0.0);
    if(getModoSeleccion()){
      colorSeleccion(ID_COCHE2);
    }
    coche2.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.0,0.0,10.0);
    if(getModoSeleccion()){
      colorSeleccion(ID_COCHE3);
    }
    coche3.draw();
    glPopMatrix();

    // Práctica 3
    glPushMatrix();
    glTranslatef(-5.0,0.0,-10.0);
    dibujaTaburete();
    glPopMatrix();
    // Práctica 2

    glPushMatrix();
    glTranslatef(-10.0,0.0,0.-5.0);
    if(getModoSeleccion()){
      colorSeleccion(ID_BEETHOVEN);
    }else{
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,verde);
    }
    beethoven.draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.0,0.0,5.0);
    if(getModoSeleccion()){
      colorSeleccion(ID_BIG_DODGE);
    }else{
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,morado);
    }
    big_dodge.draw();
    glPopMatrix();

    glPopMatrix();
}


/**
 * @brief Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
*/
void Dibuja (void){
  dibujaEscena();
  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**
 * @brief Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
*/
void idle (int v){

  // Actualización de la velocidad de escalado de altura del cilindro
  if(animacionActiva){
    if(alturaCilindro>=2.0f || alturaCilindro<=0.5f){
      VEL_Cilindro = -VEL_Cilindro;
    }

    alturaCilindro += VEL_Cilindro;

    // Actualización de la velocidad de rotación del asiento

    rotacionAsiento += VEL_Asiento;

    if(rotacionAsiento >= 360.0f || rotacionAsiento <= -360.0f){
      rotacionAsiento=0.0f;  
    }

    // Actualización de la velocidad de rotación (inclinación) del respaldo
    
    if(inclinacionRespaldo >= 0.0f || inclinacionRespaldo <= -25.0f){
      VEL_Respaldo = -VEL_Respaldo;
    }

    inclinacionRespaldo += VEL_Respaldo; 
  }
  
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}