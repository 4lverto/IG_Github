#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"



float morado[4]={0.8,0,1,1};
float verde[4]={0,1,0,1};
float rojo[4]={1,0,0,1};
float azul[4]={0,0,1,1};
float negro[4]={0,0,0,1};
float blanco[4]={1,1,1,1};
float naranja[4]={1.0f,0.5f,0.0f,1.0f};
float amarillo[4]={1.0f,1.0f,0.0f,1.0f};

/**	void initModel()

Inicializa el modelo y de las variables globales

**/
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
} ; 

// //////////////// //
// DIBUJAR UNA CAJA //
// //////////////// //

void Base(){
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
  glPushMatrix();
    glTranslatef(0.0f,2.5f,0.0f);
    glutSolidCube(5);
  glPopMatrix();
}

void Tapa(){
  glPushMatrix();
    glTranslatef(1.25f,0.25f,0.0f);
    glScalef(0.5f,0.1f,1.0f);
    glutSolidCube(5);
  glPopMatrix();
}

void Caja(){
  Base();
  glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE, azul);
    glTranslatef(-2.5f,5.0f,0.0f);
    glRotatef(30.0f,0.0f,0.0f,1.0f);
    Tapa();
  glPopMatrix();
  Tapa();
  glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,rojo);
    glTranslatef(2.5f,5.0f,0.0f);
    glRotatef(-40.0f,0.0f,0.0f,1.0f);
    glTranslatef(-2.5f,0.0f,0.0f);
    Tapa();
  glPopMatrix();
}
// //////////////////// //
// FUNCIONES AUXILIARES //
// //////////////////// //

Ejes ejesCoordenadas;

int modo=GL_FILL;
bool iluminacionActivada=true;

// Implementación de la función setModo(int M);
void setModo(int M){
  if(M==1){
    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
  }else if(M==2){
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  }else if(M==3){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  }
}


void setIluminacion(){
  iluminacionActivada = !iluminacionActivada;
  
  if(iluminacionActivada){
    glEnable(GL_LIGHTING);
  }else{
    glDisable(GL_LIGHTING);
  }
}

// //////////////////// //
// FUNCIÓN PARA DIBUJAR //
// //////////////////// //

void Dibuja (void){

  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz
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


  // DIBUJAMOS LA CAJA
  Caja();

  
  // Intercambia el buffer de dibujo y visualizacion
  glutSwapBuffers ();
}




void idle (int v){

  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}
