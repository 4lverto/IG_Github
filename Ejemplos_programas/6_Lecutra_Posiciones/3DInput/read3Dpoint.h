/*

	C.A.D. 						Curso 2001-2002
	
	Dpto. Lenguajes y Sistemas Informáticos
	E.T.S.I. Informática
	Univ. de Granada

        Rutina de entrada de puntos 3D.

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

// Variable para almacenar el ángulo de giro del modelo
// static float cursorx,cursory;    // coordenadas normalizadas
// static int WAncho=300,WAlto=300;			// ancho y alto de la ventana
// static int drawingcursor=0;


void enableDrawCursor3();

void disableDrawCursor3();

void getCursor3(float *xc, float *yc, float *zc);

void drawCursor3();

void cursor3Movido( int x, int y, int plane );

void notifyWindowSize3(float wx,float wy,int vx,int vy, float deep);
