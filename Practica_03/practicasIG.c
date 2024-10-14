#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "include/practicasIG.h"
//#include "hiply.h"




/*=================================================*/

int main (int argc, char *argv[])
{
// Inicializa glu y openGL
  glutInit (&argc, argv);

// Crea una ventana X para la salida grafica en la posicion 0,0 con tamaño 800x800, con colores RGB-alfa, con doble buffer, y 
// buffer de profundidad

  glutInitWindowPosition (0, 0);
  glutInitWindowSize (800, 800);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow ("IG. Curso 2024/25. Autor: ALBERTO ORTEGA VILCHEZ");

// Inicializa las variables del modelo
  initModel ();

// Inicializa las funciones de dibujo y cambio de tamanyo de la ventana X
  glutDisplayFunc (Dibuja);
  glutReshapeFunc (inicializaVentana);

// FUNCIONES DE INTERACCION
  glutKeyboardFunc (letra);
  glutSpecialFunc (especial);

  glutMouseFunc (clickRaton);
  glutMotionFunc (RatonMovido);

// Funcion de fondo
  glutTimerFunc (30, idle, 0);

// Inicializa parametros de openGL
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_CULL_FACE);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);


// Lanza el gestor de eventos de glut
  glutMainLoop ();
  return 0;
}
