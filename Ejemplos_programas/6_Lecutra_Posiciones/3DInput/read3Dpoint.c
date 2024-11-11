/*

	C.A.D. 						Curso 2001-2002
	
	Dpto. Lenguajes y Sistemas Informáticos
	E.T.S.I. Informática
	Univ. de Granada

        Rutina de entrada de puntos 3D.

*/

#include "read3Dpoint.h"
static float cursorx,cursory,cursorz;    // coordenadas normalizadas
static int drawingcursor=0;
static float WAncho=300, WAlto=300, Deep;
static int VAlto=100, VAncho=100;	
				// ancho y alto de la ventana y Viewport
static int showCursorPosition=1;		
static char buffer[18];
int i, firstmove;
static float lastx, lasty, lastz, lastplane;
static int softCursorEnabled=1; // Poner a uno para dibujar el cursor en el progrma

void notifyWindowSize3(float wx,float wy,int vx,int vy,float deep)
{
WAncho=wx;
WAlto=wy;
VAncho=vx;
VAlto=vy;
Deep=deep;
}

void enableDrawCursor3()
{
drawingcursor=1;
if(softCursorEnabled)
	glutSetCursor(GLUT_CURSOR_NONE);		
else
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);	
cursorx = WAncho;
cursory = WAlto;
cursorz = (cursorx+cursory)/2;
lastx = 0;
lasty = 0;
lastz = 0;
firstmove =1;
	
}

void disableDrawCursor3()
{
drawingcursor=0;
glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);

}
void enableCursor3Position()
{
showCursorPosition=1;
}

void disableCursor3Position()
{
showCursorPosition=0;
}

void getCursor3(float *xc, float *yc, float *zc)
{
*xc = cursorx;
*yc = cursory;
*zc = cursorz;
}
void drawCursor3()
{
if(drawingcursor)
	{
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f( 1.0, 1.0,1.0);

	 glLineWidth(3);
//printf("%6.1f %6.1f %6.1f %6.1f %6.1f\n",cursorx,cursory,WAncho,WAlto,Deep);

	if(softCursorEnabled) {
		glBegin(GL_LINES);
			glVertex3f( cursorx, cursory, cursorz);
			glVertex3f( cursorx, cursory,0);

			glVertex3f( 0, cursory, cursorz);
			glVertex3f( cursorx, cursory, cursorz);
			glVertex3f( cursorx, 0, cursorz);
			glVertex3f( cursorx, cursory, cursorz);
	  	glEnd();
    	}
/*	glBegin(GL_LINES);
		glVertex3f( cursorx-5, cursory, -82);
		glVertex3f(cursorx+5, cursory, -82);
		glVertex3f( cursorx, cursory-5, -82);
		glVertex3f(cursorx, cursory+5, -82);
  	glEnd();*/
  glDisable(GL_DEPTH_TEST);
	if(showCursorPosition){
		sprintf(buffer,"%5.1f %5.1f %5.1f",cursorx, cursory, cursorz);
		glRasterPos3f(WAncho*0.5, -WAlto*0.5,-Deep-1+10);
	    for(i=0;i<17;++i) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (int) buffer[i]);
            }
	}
	glEnable(GL_DEPTH_TEST);

	glPopAttrib();

	}
}



/* ------------------------------------------------------------------------- */

void cursor3Movido( int x, int yz, int plane )
{
	if(drawingcursor) {
			if(firstmove){
				firstmove = 0;
				lastx = x;
				if(plane) { lastz = yz;
						 	lasty = 0;}
				else {lasty = yz;
					  lastz = 0;}
				lastplane=plane;
				}
  			cursorx += x-lastx;
            lastx = x;
			if (plane) {
				if(plane!=lastplane)   lastz=yz;
	  			cursorz += yz-lastz;
				lastz = yz;
				}
			else {
				if(plane!=lastplane)   lasty=yz;
	  			cursory -= yz-lasty;
				lasty = yz;
				}
		
//		cursorx = 2.0*((1.0*x) / VAncho -0.5);
//   		cursory = - 2.0*((1.0*y) / VAlto - 0.5);
//	   	glutPostRedisplay();
		}
	lastplane = plane;
}


