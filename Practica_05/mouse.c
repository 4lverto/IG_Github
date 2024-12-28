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
			// printf("Objeto seleccionado: %d\n",id);
			setModoSeleccion(true);
		
			switch(id){
				case ID_TABURETE1:
					printf("\n(IZQ) Has seleccionado el Primer Taburete");
					break;
				case ID_TABURETE2:
					printf("\n(IZQ) Has seleccionado el Segundo Taburete");
					break;
				case ID_TABURETE3:
					printf("\n(IZQ) Has seleccionado el Tercer Taburete");
					break;
				case ID_BEETHOVEN1:
					printf("\n(IZQ) Has seleccionado al Primer Beethoven");
					seleccionarMalla(ID_BEETHOVEN1);
					break;
				case ID_BEETHOVEN2:
					printf("\n(IZQ) Has seleccionado al Segundo Beethoven");
					seleccionarMalla(ID_BEETHOVEN2);
					break;
				case ID_BEETHOVEN3:
					printf("\n(IZQ) Has seleccionado al Tercer Beethoven");
					seleccionarMalla(ID_BEETHOVEN3);
					break;
				case ID_DADO:
					printf("\n(IZQ) Has seleccionado el Dado\n");
					if(!getDadoEnAnimacion()){
						setDadoEnAnimacion(true);
						setAlturaDado(0.0f);
						setRotacionDadoX(0.0f);
						setRotacionDadoY(0.0f);
						setRotacionDadoZ(0.0f);

						int nuevaCara = rand() % 6;
						cambiarCaraVisible(nuevaCara);
						printf("\nNUEVA CARA -> %d",nuevaCara+1);
					}
					break;
				default:
					printf("\n(IZQ) No estás haciendo click izquierdo sobre ningún objeto\n");
					break;
			}
		}else{
			printf("\nNo estás haciendo click izquierdo sobre ningún objeto\n");
			setModoSeleccion(false);
		}
	
	}else if(boton==GLUT_MIDDLE_BUTTON && estado==GLUT_DOWN) {

		int id=-1;

		if(pick(x,y,&id)){
			// printf("Objeto seleccionado: %d\n",id);
			setModoSeleccion(true);
		
			switch(id){
				case ID_TABURETE1:
					printf("\n(CENTRO) Has seleccionado el Primer Taburete\n");
					girar(1);
					break;
				case ID_TABURETE2:
					printf("\n(CENTRO) Has seleccionado el Segundo Taburete\n");
					girar(2);
					break;
				case ID_TABURETE3:
					printf("\n(CENTRO) Has seleccionado el Tercer Taburete\n");
					girar(3);
					break;
				case ID_BEETHOVEN1:
					printf("\n(CENTRO) Has seleccionado al Primer Beethoven");
					break;
				case ID_BEETHOVEN2:
					printf("\n(CENTRO) Has seleccionado al Segundo Beethoven");
					break;
				case ID_BEETHOVEN3:
					printf("\n(CENTRO) Has seleccionado al Tercer Beethoven");
					break;
				case ID_DADO:
					printf("\n(CENTRO) Has seleccionado el Dado\n");
					break;
				default:
					printf("\nNo estás haciendo click central sobre ningún objeto\n");
					break;
			}
		}else{
			printf("\nNo estás haciendo click central sobre ningún objeto");
			setModoSeleccion(false);
		}
	}
	else if(boton==GLUT_RIGHT_BUTTON && estado==GLUT_DOWN) {
		int id=-1;

		if(pick(x,y,&id)){
			// printf("Objeto seleccionado: %d\n",id);
			setModoSeleccion(true);
		
			switch(id){
				case ID_TABURETE1:
					printf("\n(DCHA) Has seleccionado el Primer Taburete\n");
					break;
				case ID_TABURETE2:
					printf("\n(DCHA) Has seleccionado el Segundo Taburete\n");
					break;
				case ID_TABURETE3:
					printf("\n(DCHA) Has seleccionado el Tercer Taburete\n");
					break;
				case ID_BEETHOVEN1:
					printf("\n(DCHA) Has seleccionado al Primer Beethoven");
					break;
				case ID_BEETHOVEN2:
					printf("\n(DCHA) Has seleccionado al Segundo Beethoven");
					break;
				case ID_BEETHOVEN3:
					printf("\n(DCHA) Has seleccionado al Tercer Beethoven");
					break;
				case ID_DADO:
					printf("\n(DCHA) Has seleccionado el Dado\n");
					break;
				default:
					printf("\nNo estás haciendo click derecho sobre ningún objeto\n");
					break;
			}
		}else{
			printf("\nNo estás haciendo click derecho sobre ningún objeto");
			setModoSeleccion(false);
		}
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

	glDisable(GL_LIGHTING);
	glDisable(GL_DITHER);
	glDisable(GL_TEXTURE_2D);

	setModoSeleccion(true);

	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	dibujaEscena();

	setModoSeleccion(false);

	glEnable(GL_LIGHTING);
	glEnable(GL_DITHER);
	glEnable(GL_TEXTURE_2D);

	glFlush();
	glFinish();

	glReadPixels(x, viewport[3]-y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	*id=data[0] | (data[1] << 11);

	printf("\nID devuelto por pick: %d\n", *id);

	glutPostRedisplay();

	return *id;
}