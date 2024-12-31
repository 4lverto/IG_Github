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

float D = 40;


/**

Tamaño de la ventana X

**/
float anchoVentana, altoVentana;

// Al declrar las siguientes variables como "extern" en practicasIG.h podemos redefinirlas

int camaraActual=2;

float camX=0.0f,camY=10.0f,camZ=0.0f;
float lookX=0.0f,lookY=0.0f,lookZ=0.0f;
float upX=0.0f,upY=1.0f,upZ=0.0f;

float eyeX = -D * sin(view_roty * M_PI / 180.0) * cos(view_rotx * M_PI /180);
float eyeY = D * sin(view_rotx * M_PI / 180.0);
float eyeZ = D * cos(view_roty * M_PI / 180.0) * cos(view_rotx * M_PI / 180.0);

PosicionCamara camaras[]={
  {0.0f,10.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,-10.0f},
  {-10.0f,7.0f,0.0f,0.0f,6.5f,0.0f,0.0f,1.0f,0.0f},
  {eyeX,eyeY,eyeZ,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f}
};

//================================================ MÉTODOS Y FUNCIONES  

void actualizarCamara(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camX,camY,camZ,lookX,lookY,lookZ,upX,upY,upZ);
}

void setCamara (float ax, float ay, float az, float d){
  
  if(ax!=view_rotx) view_rotx = ax;
  if(ay!=view_roty) view_roty = ay;
  if(az!=view_rotz)view_rotz = az;
  if(d!=D) D = d;
}

void getCamara (float &ax, float &ay, float &az, float &d){
  ax = view_rotx;
  ay = view_roty;
  az = view_rotz;
  d = D;
}


void transformacionVisualizacion (){
 
  if(camaraActual==2){
    glTranslatef (0, 0, -D);

    glRotatef (view_rotx, 1.0, 0.0, 0.0);
    glRotatef (view_roty, 0.0, 1.0, 0.0);
    glRotatef (view_rotz, 0.0, 0.0, 1.0);
  }else{
    actualizarCamara();
  }
}

void fijaProyeccion (){
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

void inicializaVentana (GLsizei ancho, GLsizei alto){
  altoVentana = alto;
  anchoVentana = ancho;

  glViewport (0, 0, ancho, alto);	// Establecemos el Viewport usando la nueva anchura y altura de la ventana X

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();

  fijaProyeccion ();		// Cargamos la transformacion de proyeccion
}