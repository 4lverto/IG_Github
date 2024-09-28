#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // Cabecera de la librería 'glut' (no es necesario incluir OpenGL ya que glut.h ya lo incluye)

float roty=30.0;  // Variable que se va a usar para indicar la rotación en grados que se le va a aplicar al cubo

/*
Función que crea un cuadrado de tamaño t x t, centrado en el origen de coordenadas en el plano y=0
Para crear el cuadrado se le indica a OpenGL que se le van a pasar cuadriláteros (GL_QUADS)

La información de las primitivas se pasa entre una llamada a glBegin y una llamada a glEnd. 
*/

void plano( float t )
//Construye un plano horizontal de tamano t x t
{
  
  /*En este bloque se especifica la normal (vector  perpendicular de módulo). En este caso, como el plano
    es horizontal, la normal es el vector (0,1,0). Finalmente, se indican los vértices del cuadrilátero, que
    deberán estar en sentido antihorario cuando se ve el cuadrilátero por la cara delantera 
  */
  glBegin( GL_QUADS ); 
    glNormal3f( 0.0, 1.0, 0.0 );     
    glVertex3f(  t, 0,  t );
    glVertex3f(  t, 0, -t );
    glVertex3f( -t, 0, -t );
    glVertex3f( -t, 0,  t );
  glEnd();
}

// Cada vez que se llama a Dibuja() se visualiza un nuevo frame. P
void Dibuja( )
{
  float pos[4] = {5.0, 5.0, 10.0, 0.0 };
  float morado[4]={0.8,0,1,1}, verde[4]={0,1,0,1};
  glClearColor(1,1,1,1); // Fondo blanco
  glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  glTranslatef(-0.5,-0.5,-100);
  glLightfv( GL_LIGHT0, GL_POSITION, pos );
  glRotatef( 20, 1.0, 0.0, 0.0 );
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde );
  
  plano(30);
  
  glRotatef( roty, 0.0, 1.0, 0.0 );
  glTranslatef(0,5,0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, morado );
  glutSolidCube(10);
  glutSwapBuffers();
}
/* ------------------------------------------------------------------------- */

// La función Ventana indica en qué parte de la ventana debe dibujarse y cómo se proyecta el modelo en la pantalla
void Ventana(GLsizei ancho,GLsizei alto)
{ // Se ejecuta cuando se cambia la ventana, recibe el ancho y alto de la ventana X
    float D=ancho; if(D<alto) D=alto;
    glViewport(0,0,ancho,alto); //fija el area de dibujo en la ventana 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ancho/D,ancho/D,-alto/D,alto/D,5,250);
    glMatrixMode(GL_MODELVIEW);
}

// Se ejecuta como función de fondo (siempre que no hay otra función que procesar.)

void idle()
{
  roty +=0.15; // Aumenta el ángulo de rotación
  glutPostRedisplay(); // Indica que es necesario generar un nuevo frame
}

// ////////////////// //
// PROGRAMA PRINCIPAL //
// ////////////////// //

// Crea la ventana de dibujo usando las funciones de glut, declara las funciones que deben responder a 
// los distintos eventos y establece algunos parámetros de OpenGL.

int main( int argc, char *argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutCreateWindow("IG: cubo");
  glutDisplayFunc( Dibuja );
  glutReshapeFunc( Ventana );
  glutIdleFunc(idle);
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}

// COMPILAR --> gcc cubo.c -lglut -lGLU -lGL -o cubo