/*
=======================================================/
modulo visual.c
    Inicialización de ventana X
    Transformación de visualización
    Transformación de proyección
 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/practicasIG.h"




//================================================ VARIABLES  

/**

Angulos de rotacion de la camara.

**/

float view_rotx = 30, view_roty = 45,view_rotz = 0;


/**

Distancia de la cámara

**/

float D = 10;


/**

Tamaño de la ventana X

**/


float anchoVentana, altoVentana;




/** 	void setCamara()

Cambia los parámetros de la cámara en el modulo visual

**/
void setCamara (float ax, float ay, float az, float d)
{
  view_rotx = ax;
  view_roty = ay;
  view_rotz = az;
  D = d;
}


void getCamara (float &ax, float &ay, float &az, float &d)
{
  ax = view_rotx;
  ay = view_roty;
  az = view_rotz;
  d = D;
}

/** 	void transformacionVisualizacion()

Fija la transformacion de visualizacion en funcion de los angulos de rotacion view_rotx,
view_roty y el desplazamiento de la camara D.

La cámara mira al origen de coordenadas a una distancia D desde la posición angular view_rotx,
view_roty;

**/
void transformacionVisualizacion ()
{
  glTranslatef (0, 0, -D);

  glRotatef (view_rotx, 1.0, 0.0, 0.0);
  glRotatef (view_roty, 0.0, 1.0, 0.0);
  glRotatef (view_rotz, 0.0, 0.0, 1.0);
  // glTranslatef(-x_camara,-y_camara,-z_camara);
}

/**	void fijaProyeccion()

Fija la transformacion de proyeccion en funcion del tamaño de la ventana y del tipo de proyeccion

**/
void fijaProyeccion ()
{
  float calto;			// altura de la ventana corregida

  if (anchoVentana > 0)
    calto = altoVentana / anchoVentana;
  else
    calto = 1;

  glFrustum (-1, 1, -calto, calto, 1.5, 1500);

  glMatrixMode (GL_MODELVIEW);
// A partir de este momento las transformaciones son de modelado.       
  glLoadIdentity ();

}


/**	void inicializaVentana(GLsizei ancho,GLsizei alto)

Inicializa el viewport para que ocupe toda la ventana X, y llama a fijaProyeccion.

**/

void inicializaVentana (GLsizei ancho, GLsizei alto)
{
  altoVentana = alto;
  anchoVentana = ancho;

  glViewport (0, 0, ancho, alto);	// Establecemos el Viewport usando la nueva anchura y altura de la ventana X

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  fijaProyeccion ();		// Cargamos la transformacion de proyeccion

}
