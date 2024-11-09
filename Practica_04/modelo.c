#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "include/practicasIG.h"
#include <vector>

using namespace std;

// PRÁCTICA 4 - Mallas a dibujar

Dado dado(4.0f); // Dado "hereda" de Malla
Malla beeth1("plys/beethoven.ply",false); // Reflectividad difusa
Malla beeth2("plys/beethoven.ply",false); // Reflectividad ambiente
Malla beeth3("plys/beethoven.ply",false); // Reflectividad especular

/**
 * @brief Inicializa el modelo y de las variables globales
*/
void
initModel (){
  // Práctica 4
  dado.cargarTextura("JPEG/dado.jpg");

  dado.asignarReflectividadDifusa(1.0f,1.0f,1.0f,1.0f);  
  dado.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  dado.asignarReflectividadAmbiente(0.8f,0.8f,0.8f,1.0f);
  dado.asignarExponenteEspecular(100.0f);
  dado.setSombreadoSuave(true);

  beeth1.cargarTextura("JPEG/texturaMarmol.jpg");
  beeth1.calculoCoordenadasTexturaCilindrica();
  beeth1.asignarReflectividadDifusa(1.0f,1.0f,1.0f,1.0f);
  beeth1.asignarExponenteEspecular(100.0f);
  beeth1.setSombreadoSuave(true);

  beeth2.cargarTextura("JPEG/texturaMarmol.jpg");
  beeth2.calculoCoordenadasTexturaCilindrica();
  beeth2.asignarReflectividadAmbiente(0.8f,0.8f,0.8f,1.0f);
  beeth2.asignarExponenteEspecular(100.0f);
  beeth2.setSombreadoSuave(true);

  beeth3.cargarTextura("JPEG/texturaMarmol.jpg");
  beeth3.calculoCoordenadasTexturaCilindrica();
  beeth3.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  beeth3.asignarExponenteEspecular(100.0f);
  beeth3.setSombreadoSuave(true);
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

// ///////////////////////////////////////////////

/**
 * @brief Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
*/
void Dibuja (void){

  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  glPushMatrix ();		// Apila la transformacion geometrica actual
  
  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro
  
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer
  
  transformacionVisualizacion ();	// Carga transformacion de visualizacion
  
  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena
  
  // glDisable(GL_CULL_FACE);

  // Dibujamos los ejes de coordenadas de forma que no se vean afectados por la iluminación
  glDisable(GL_LIGHTING);
  ejesCoordenadas.draw();			// Dibuja los ejes
  if(iluminacionActivada){    // Usamos la variable iluminacionActivada para que el color de los ejes no se vea afectado al alterar la iluminación
    glEnable(GL_LIGHTING);
  }

                              // ////////// //
                              // PRACTICA 4 //
                              // ////////// //

  dado.draw();

  glTranslatef(10.0,0.0,0.0);
  beeth1.draw();
  
  glTranslatef(0.0,0.0,10.0);
  beeth2.draw();

  glTranslatef(0.0,0.0,10.0);
  beeth3.draw();

                              // FIN PRÁCTICA 2 

  glPopMatrix ();		// Desapila la transformacion geometrica

  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**
 * @brief Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
*/
void idle (int v){
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}