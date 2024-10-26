#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "include/practicasIG.h"
#include <vector>
#include <stdbool.h>

using namespace std;

float VEL_Cilindro=0.01f;
float VEL_Asiento=0.5f;
float VEL_Respaldo=0.1f;

/**
 * @brief Inicializa el modelo y de las variables globales
*/
void
initModel (){
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

                    // ////////////////////////////////////////// //
                    // FUNCIONES DE GESTIÓN DE ILUMINACIÓN Y MODO //
                    // ////////////////////////////////////////// // 

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

                    // ////////////////// //
                    // PROGRAMA PRINCIPAL //
                    // ////////////////// //

// PRÁCTICA 3 - Componentes de mi silla
bool animacionActiva=false;
// ///////////////////////////////////////////////

/**
 * @brief Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
*/
void Dibuja (void){
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  float morado[4]={0.8,0,1,1};
  float verde[4]={0,1,0,1};
  float rojo[4]={1,0,0,1};
  float azul[4]={0,0,1,1};
  float negro[4]={0,0,0,1};
  float blanco[4]={1,1,1,1};
  float naranja[4]={1.0f,0.5f,0.0f,1.0f};
  float amarillo[4]={1.0f,1.0f,0.0f,1.0f};

  float  color[4] = { 0.8, 0.0, 1, 1 };

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  glLoadIdentity();
  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  // Gestión de ejes
  glDisable(GL_LIGHTING);

  ejesCoordenadas.draw();			// Dibuja los ejes
  
  if(iluminacionActivada){    // Usamos la variable iluminacionActivada para que el color de los ejes no se vea afectado al alterar la iluminación
    glEnable(GL_LIGHTING);
  }

  dibujaTaburete();

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