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
// "SUBCLASE" CUBO //
// /////////////// //
class Cubo:Objeto3D { 
  public: 
    float lado = 30;

    Cubo(float l){
      this->lado=l;
    }

  // Dibuja el Cubo usando primitivas

  /*
  void draw(){
    glBegin(GL_QUADS);
    {
      glutSolidCube(this->lado);
    }
    glEnd();
    
  }*/

  // Dibuja el cubo manualmente

  void draw(){
    
    float mitad = this->lado / 2;
    glBegin( GL_QUADS ); // Comienza la definición de un cuadrado
    {
      // Cara superior
      glNormal3f( 0.0, 1.0, 0.0 );
      glVertex3f( -mitad, mitad, mitad ); 
      glVertex3f( mitad, mitad, mitad );
      glVertex3f( mitad, mitad, -mitad );
      glVertex3f( -mitad, mitad, -mitad );
      
      // Cara inferior
      glNormal3f( 0.0, -1.0, 0.0 ); 
      glVertex3f( -mitad, -mitad, -mitad );
      glVertex3f( mitad, -mitad, -mitad );
      glVertex3f( mitad, -mitad, mitad );
      glVertex3f( -mitad, -mitad, mitad );

      // Cara derecha
      glNormal3f( 1.0, 0.0, 0.0 ); 
      glVertex3f( mitad, mitad, mitad );
      glVertex3f( mitad, mitad, -mitad );
      glVertex3f( mitad, -mitad, -mitad );
      glVertex3f( mitad, -mitad, mitad );

      // Cara izquierda
      glNormal3f( -1.0, 0.0, 0.0 ); 
      glVertex3f( -mitad, mitad, mitad );
      glVertex3f( -mitad, mitad, -mitad );
      glVertex3f( -mitad, -mitad, -mitad );
      glVertex3f( -mitad, -mitad, mitad );

      // Cara frontal
      glNormal3f( 0.0, 0.0, 1.0 ); 
      glVertex3f( -mitad, mitad, mitad );
      glVertex3f( -mitad, -mitad, mitad );
      glVertex3f( mitad, -mitad, mitad );
      glVertex3f( mitad, mitad, mitad );
      
      // Cara trasera
      glNormal3f( 0.0, 0.0, -1.0 ); 
      glVertex3f( -mitad, -mitad, -mitad );
      glVertex3f( mitad, -mitad, -mitad );
      glVertex3f( mitad, mitad, -mitad );
      glVertex3f( -mitad, mitad, -mitad );
    }
    glEnd();
  }

};

// /////////////////// //
// "SUBCLASE" PIRÁMIDE //
// /////////////////// //
class Piramide:Objeto3D { 
  public: 
    float lado = 2;
    float alto = 4;

    Piramide(float l,float a){
      this->lado=l;
      this->alto=a;
    }

  // Dibuja la Pirámide (Primitiva GLUT)
  /*
  void draw() {
      glutSolidCone(lado,alto,4,1);
  }*/

  // Dibuja la Pirámide (manualmente)
  void draw(){

    float mitad=lado/2;

    // Coordenadas del vértice superior de la pirámide
    float vx = 0;
    float vy = alto;
    float vz = 0;

    // Dibujamos la base de la pirámide
    glBegin(GL_QUADS);{
      glNormal3f(0,-1,0);
      glVertex3f(-mitad,0,-mitad);
      glVertex3f(mitad,0,-mitad);
      glVertex3f(mitad,0,mitad);
      glVertex3f(-mitad,0,mitad);
    }
    glEnd();

    glBegin(GL_TRIANGLES);{

      // Cara frontal
      glNormal3f(0,0.5,0.5);
      glVertex3f(-mitad,0,mitad);
      glVertex3f(mitad,0,mitad);
      glVertex3f(vx,vy,vz); // "Punta" 
    
      // Cara derecha
      glNormal3f(0.5,0.5,0);
      glVertex3f(mitad,0,mitad);
      glVertex3f(-mitad,0,-mitad);
      glVertex3f(vx,vy,vz); // "Punta"

      // Cara trasera
      glNormal3f(0,0.5,-0.5);
      glVertex3f(mitad,0,-mitad);
      glVertex3f(-mitad,0,-mitad);
      glVertex3f(vx,vy,vz); // "Punta"

      // Cara izquierda
      glNormal3f(-0.5,0.5,0);
      glVertex3f(-mitad,0,-mitad);
      glVertex3f(-mitad,0,mitad);
      glVertex3f(vx,vy,vz); // "Punta"
    }
    glEnd();


  }

} ;

Ejes ejesCoordenadas;
Cubo miCubo(3);
Piramide miPiramide(2,4);

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

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  float morado[4]={0.8,0,1,1};
  float verde[4]={0,1,0,1};
  float rojo[4]={1,0,0,1};
  float azul[4]={0,0,1,1};
  float negro[4]={0,0,0,1};
  float blanco[4]={1,1,1,1};

  float  color[4] = { 0.8, 0.0, 1, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  glDisable(GL_LIGHTING);
  ejesCoordenadas.draw();			// Dibuja los ejes
  if(iluminacionActivada){    // Usamos la variable iluminacionActivada para que el color de los ejes no se vea afectado al alterar la iluminación
    glEnable(GL_LIGHTING);
  }

  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)    

  // DIBUJO EL CUBO
  float  color2[4] = { 1.0, 1.0, 0.0}; // amarillo
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,color2);
  glTranslatef(5,1,2);

  miCubo.draw();


  // DIBUJO LA PIRÁMIDE
  float  color3[4] = { 0.0, 4.0, 0.0}; // verde
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,color3);
  glTranslatef(5,-1,1);
  //glRotatef(-90,1,0,0);
  miPiramide.draw();
  
  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{

  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}
