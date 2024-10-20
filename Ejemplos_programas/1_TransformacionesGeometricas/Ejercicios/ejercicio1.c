#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"


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

// /////////////// //
// "SUBCLASE" CAJA //
// /////////////// //

void caja() {
    glBegin(GL_QUADS); // Iniciar el dibujo de un cuadrilátero

    // Cara frontal (Z = 2)
    glVertex3f(0.0f, 0.0f, 2.0f);  // Vértice inferior izquierdo
    glVertex3f(4.0f, 0.0f, 2.0f);  // Vértice inferior derecho
    glVertex3f(4.0f, 1.0f, 2.0f);  // Vértice superior derecho
    glVertex3f(0.0f, 1.0f, 2.0f);  // Vértice superior izquierdo

    // Cara trasera (Z = 0)
    glVertex3f(0.0f, 0.0f, 0.0f);  // Vértice inferior izquierdo
    glVertex3f(4.0f, 0.0f, 0.0f);  // Vértice inferior derecho
    glVertex3f(4.0f, 1.0f, 0.0f);  // Vértice superior derecho
    glVertex3f(0.0f, 1.0f, 0.0f);  // Vértice superior izquierdo

    // Cara izquierda (X = 0)
    glVertex3f(0.0f, 0.0f, 0.0f);  // Vértice inferior trasero
    glVertex3f(0.0f, 0.0f, 2.0f);  // Vértice inferior frontal
    glVertex3f(0.0f, 1.0f, 2.0f);  // Vértice superior frontal
    glVertex3f(0.0f, 1.0f, 0.0f);  // Vértice superior trasero

    // Cara derecha (X = 4)
    glVertex3f(4.0f, 0.0f, 0.0f);  // Vértice inferior trasero
    glVertex3f(4.0f, 0.0f, 2.0f);  // Vértice inferior frontal
    glVertex3f(4.0f, 1.0f, 2.0f);  // Vértice superior frontal
    glVertex3f(4.0f, 1.0f, 0.0f);  // Vértice superior trasero

    // Cara superior (Y = 1)
    glVertex3f(0.0f, 1.0f, 2.0f);  // Vértice frontal izquierdo
    glVertex3f(4.0f, 1.0f, 2.0f);  // Vértice frontal derecho
    glVertex3f(4.0f, 1.0f, 0.0f);  // Vértice trasero derecho
    glVertex3f(0.0f, 1.0f, 0.0f);  // Vértice trasero izquierdo

    // Cara inferior (Y = 0)
    glVertex3f(0.0f, 0.0f, 2.0f);  // Vértice frontal izquierdo
    glVertex3f(4.0f, 0.0f, 2.0f);  // Vértice frontal derecho
    glVertex3f(4.0f, 0.0f, 0.0f);  // Vértice trasero derecho
    glVertex3f(0.0f, 0.0f, 0.0f);  // Vértice trasero izquierdo

    glEnd(); // Finalizar el dibujo
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


  // DIBUJAMOS LA CAJA VERDE
  glPushMatrix();
  glTranslatef(0.0f,0.0f,-2.0f); // Echo la caja hacia atrás.
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,verde);
  caja();
  glPopMatrix(); // Desapila la transformacion geometrica


  // DIBUJAMOS LA CAJA AZUL

  glPushMatrix();
  glTranslatef(2.0f,1.0f,-2.0f);
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,azul);
  caja();
  glPopMatrix();

  // DIBUJAMOS LA CAJA NARANJA

  glPushMatrix();
  glRotatef(90.0,0.0f,1.0f,0.0f);
  glTranslatef(0.0f,1.0f,0.0f);
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,naranja);
  caja();
  glPopMatrix();

  // DIBUJAMOS LA CAJA AMARILLA
  glPushMatrix();
  glTranslatef(4.0f,0.0f,0.0f);
  glRotatef(90.0f,0.0f,1.0f,0.0f);
  glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,amarillo);
  caja();
  glPopMatrix();

  // Intercambia el buffer de dibujo y visualizacion
  glutSwapBuffers ();
}



void idle (int v){

  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}
