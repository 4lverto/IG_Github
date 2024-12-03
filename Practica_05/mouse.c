/*
=======================================================

	 mouse.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "include/practicasIG.h"


#define __mouse__ 
#include "include/mouse.h"

int MOUSE_LEFT_DOWN=0;
int MOUSE_MIDDLE_DOWN=0;
int MOUSE_RIGHT_DOWN=0;
int MOUSE_X, MOUSE_Y;



int ISINTERACTING;

/**

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void clickRaton( int boton, int estado, int x, int y ){
	ISINTERACTING=1;
	
	if(boton==GLUT_LEFT_BUTTON && estado==GLUT_DOWN) {
		int id=-1;

		if(pick(x,y,&id)){
			objetoSeleccionado=id;
			printf("Objeto seleccionado: %d\n",id);
			setModoSeleccion(true);
		}else{
			objetoSeleccionado=-1;
			setModoSeleccion(false);
		}
	}
	else if(boton==GLUT_MIDDLE_BUTTON && estado==GLUT_DOWN) {
		MOUSE_MIDDLE_DOWN=1;
		MOUSE_X=x;
		MOUSE_Y=y;
	}
	else if(boton==GLUT_RIGHT_BUTTON && estado==GLUT_DOWN) {
		MOUSE_RIGHT_DOWN=1;
		MOUSE_X=x;
		MOUSE_Y=y;
	}
	else {	
		MOUSE_LEFT_DOWN=0;
		MOUSE_MIDDLE_DOWN=0;
		MOUSE_RIGHT_DOWN=0;
		ISINTERACTING=0;
	}
	glutPostRedisplay();
}


/**

Procedimiento para gestionar los eventos de movimiento del raton.

Argumentos:

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void RatonMovido( int x, int y )
{
char texto[30];
float ax,ay,az,d;
getCamara (ax, ay, az, d);
	if(MOUSE_LEFT_DOWN) {
		if(x!=MOUSE_X) ay+=x-MOUSE_X;
		if(y!=MOUSE_Y) ax+=y-MOUSE_Y;
		setCamara (ax, ay, az,  d);
		}
	else if(MOUSE_RIGHT_DOWN) {
	//   if(x!=MOUSE_X) z_camara=10.0*(anchoVentana/2-MOUSE_X)/(x+1.0);
	if(y!=MOUSE_Y) {
		d+=100.0*(y-MOUSE_Y)/200; //escalar el zoom
		setCamara (ax,  ay,  az,  d);
		}
	 }
	else if(MOUSE_MIDDLE_DOWN) {
		if(x!=MOUSE_X) az+=x-MOUSE_X;
		if(y!=MOUSE_Y) ax+=y-MOUSE_Y;
		setCamara ( ax,  ay,  az,  d);
		}
	MOUSE_X=x;
	MOUSE_Y=y;
glutPostRedisplay();
}

// ////////// //
// PRÁCTICA 5 //
// ////////// //

int pick(int x, int y, int *id){
	GLint viewport[4];
	unsigned char data[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	dibujaEscena();

	glFlush();
	glFinish();

	glReadPixels(x, viewport[3]-y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glEnable(GL_LIGHTING);
	glEnable(GL_DITHER);
	glEnable(GL_TEXTURE_2D);

	printf("Color del pixel: %d,%d,%d: ",data[0],data[1],data[2]);

	*id=data[0];

	glutPostRedisplay();
	
	return *id;
}