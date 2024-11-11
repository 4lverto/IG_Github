/*

	C.A.D. 						Curso 2000-2001
	
	Dpto. Lenguajes y Sistemas Informáticos
	E.T.S.I. Informática
	Univ. de Granada

	Entrada de Puntos 2D
		Programa ejemplo para read2Dpoint

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "read3Dpoint.h"

// Variable para almacenar el ángulo de giro del modelo
 static GLfloat angulo =0;
 static GLfloat view_rotx = 20.0, view_roty = -20.0, view_rotz = 0.0;
 static GLint gear1, gear2, gear3;
 static GLfloat angle = 0.0;
/**/ static float Dx=40,Dy=40;

static view_X=0.0, view_Y=0.0;
static Plane=0;		// Movimiento de ratón: 0 plano XY 1 Plano XZ


 static int		menu;     // Identificador del menu
 typedef enum{ PARAR, RAPIDO, LENTO, HORA, ANTIHORA,SALIR} opciones_menu;
 float Delta =1.0;

static void Dibuja( void )
{

  // Fija el color de fondo a negro
  glClearColor(0,0,0,1);
	
  // Inicializa el buffer de color y de profundidad
/**/  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



  glPushMatrix();


  glTranslatef(view_X,view_Y,-150);
/*  drawCursor();
	glColor3f( 0.0, 1.0,1.0);

glBegin(GL_LINES);
		glVertex3f( -500, 10,-10);
		glVertex3f( +500, 10,-10);
		glVertex3f( 10, -500,-10);
		glVertex3f( 10, +500,-10);
  	glEnd();

*/

  glRotatef(view_rotx, 1.0, 0.0, 0.0);
  glRotatef(view_roty, 0.0, 1.0, 0.0);
  glRotatef(view_rotz, 0.0, 0.0, 1.0);


	glPushMatrix();		// Apila la transformación geométrica actual

 // drawCursor3();


	glColor3f( 0, 0,0.3);

  // Planos
 	glBegin(GL_QUADS);
		glVertex3f(80,80,0);
		glVertex3f(0, 80,0);
		glVertex3f( 0, 0,0);
		glVertex3f( 80,0,0);
  	glEnd();

	glColor3f( 0., 0.3,0);

  // Planos
 	glBegin(GL_QUADS);
		glVertex3f(80,0,80);
		glVertex3f(0, 0,80);
		glVertex3f( 0,0, 0);
		glVertex3f( 80,0,0);
  	glEnd();
	glColor3f( 0.3, 0.,0.);

  // Planos
 	glBegin(GL_QUADS);
		glVertex3f(0,80,80);
		glVertex3f(0,0, 80);
		glVertex3f(0, 0,0);
		glVertex3f(0, 80,0);
  	glEnd();



// Giro del modelo
// glRotatef(angulo,0,0,1);

  // Fija el color de dibujo
//	glColor3f( 1.0, 0.6,0);

  drawCursor3();

  // Introduce la geometria
/* 	glBegin(GL_POLYGON);
		glVertex3f(-Dx,-Dy,-11);
		glVertex3f(-Dx, Dy,-11);
		glVertex3f( Dx, Dy,-11);
		glVertex3f( Dx,-Dy,-11);
  	glEnd();

  // Fija el color de dibujo
	glColor3f( 0.0, 1 ,0);

  // Introduce la geometria
 	glBegin(GL_POLYGON);
		glVertex3f(-40,-40,-30);
		glVertex3f(-40, 40,-30);
		glVertex3f( 40, 40,-30);
		glVertex3f( 40,-40,-30);
  	glEnd();
 */ 	  	
  	glPopMatrix(); // Desapila la transformación geométrica
 glPopMatrix();  	
    // Se intercambia el buffer de dibujo y el de pantalla
	glutSwapBuffers();


}
/* ------------------------------------------------------------------------- */

void Ventana(GLsizei ancho,GLsizei alto)
{
	float calto; 	// altura de la ventana corregida
  // Establecemos el Viewport usando la nueva anchura y altura de la ventana X
  	glViewport(0,0,ancho,alto);
	

 // Especificamos la transformación de visualización 	
  	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

  	if(ancho>0)
  		calto = 5*(GLfloat)alto/(GLfloat)ancho;
  	else
  		calto = 5;
  		

	notifyWindowSize3(5,calto,ancho,alto,8);

//  		glOrtho(-50,50,-calto, calto,0,1);
			glFrustum(-5,5,-calto,calto,8,250);
// Los planos trasero y delantero se ha desplazado para evitar el recorte

// A partir de este momento las transformaciones son de modelado  		
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}

/* ==========================================================================*/

 static void FuncFondo()
{
  angulo += Delta; // Velocidad controlada por el menú
  glutPostRedisplay(); // Redibuja el modelo

}


 static void letra (unsigned char k, int x, int y)
{
  switch (k) {
  case 'h':
  case 'H':
  	printf("\n C.A.D. 						Curso 2000-2001");
  	printf("\n Dpto. Lenguajes y Sistemas Informáticos");
  	printf("\n E.T.S.I. Informática		Univ. de Granada ");
  	printf("\n Demostración 2_i2");
  	printf("\n");
  	printf("\n Cursor: Rotar escena respecto a los ejes X e Y");
  	printf("\n z,Z:    Rotar escena respecto a los ejes X e Y");
  	printf("\n Pulsando el boton derecho del ratón se despliega el menú");
  	printf("\n Los botones derecho y central cambian a giro horario y antihorario");
  	printf("\n Moviendo el ratón se modifica el tamaño del cuadrado");
  	printf("\n El cuadrado verde colocado detras sirve de referencia para la orientación.");
  	printf("\n Escape: Salir");
  	printf("\n\n\n");
  	break;
  case 'z':
    view_rotz += 5.0;
    break;
  case 'Z':
    view_rotz -= 5.0;
    break;

  case '4':
    view_X -= 5.0;
    break;
  case '2':
    view_Y -= 5.0;
    break;
  case '6':
    view_X += 5.0;
    break;
  case '8':
    view_Y += 5.0;
    break;

  case 27:  /* Escape */
    exit(0);
    break;
  default:
    return;
  }
  glutPostRedisplay();
}


 static void especial(int k, int x, int y)
{
  switch (k) {
  case GLUT_KEY_UP:
    view_rotx += 5.0;
    break;
  case GLUT_KEY_DOWN:
    view_rotx -= 5.0;
    break;
  case GLUT_KEY_LEFT:
    view_roty += 5.0;
    break;
  case GLUT_KEY_RIGHT:
    view_roty -= 5.0;
    break;
  default:
    return;
  }
  glutPostRedisplay();
}

 void seleccionMenu( int opcion )
{
   switch ( opcion )
   {
   case PARAR:
      Delta = 0;
      break;
   case RAPIDO:
      if(Delta==0) Delta = 2;
      Delta = Delta *2;
      break;
   case LENTO:
      Delta = Delta/2;
      break;
   case HORA:
      if(Delta>0) Delta = -Delta;
      if(Delta==0) Delta = -1;
      break;
   case ANTIHORA:
      if(Delta<0) Delta = -Delta;
      if(Delta==0) Delta = 1;
      break;
   case SALIR:
   	  exit(0);
   }
}

static left_down=0, right_down=0;

 void clickRaton( int boton, int estado, int x, int y )
{
	float xc,yc,zc;

  switch ( boton )
   {
   case GLUT_LEFT_BUTTON:
      if ( estado == GLUT_DOWN ) {
	  left_down =1;
	  Plane = 0;	// XY
	   if(!right_down) enableDrawCursor3();
	  cursor3Movido(x,y,0);
	  }
	  else  {
	  	left_down=0;
	    if(!right_down) {
			cursor3Movido(x,y,0);
	 		disableDrawCursor3();
	  		getCursor3(&xc,&yc,&zc);
      		printf("\n %6.3f, %6.3f, %6.3f \n",xc,yc,zc);
			}
      }
      break;
   case GLUT_MIDDLE_BUTTON:
      if ( estado == GLUT_DOWN ) {
	  right_down=1;
	  Plane = 1;	// XZ
	  if(!left_down) enableDrawCursor3();
	  cursor3Movido(x,y,1);
	  }
	  else  {
	  	right_down=0;
	  	if(!left_down) {
	  		cursor3Movido(x,y,1);
	  		disableDrawCursor3();
	  		getCursor3(&xc,&yc,&zc);
      		printf("\n %6.3f, %6.3f, %6.3f \n",xc,yc,zc);
			}
      }
      break;

   }
}


 void CreaMenu()
{

   menu = glutCreateMenu( seleccionMenu );

   glutAddMenuEntry( "Parar", PARAR );
   glutAddMenuEntry( "Rapido", RAPIDO );
   glutAddMenuEntry( "Lento", LENTO );
   glutAddMenuEntry( "Horario", HORA );
   glutAddMenuEntry( "Antihorario", ANTIHORA );
   glutAddMenuEntry( "Salir", SALIR );



//   glutAttachMenu( GLUT_RIGHT_BUTTON );
   glutMouseFunc( clickRaton );
}

static void RatonMovido(int x, int y)
{

cursor3Movido(x,y,Plane);
}

/* ------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------- */

int main( int argc, char *argv[] )
{
// Inicializa glu y Mesa
   glutInit( &argc, argv );

// Crea una ventana X para la salida gráfica
   glutInitWindowPosition( 0, 0 );
   glutInitWindowSize( 300, 300 );
// El doble buffer se debe activar en la inicialización
/**/   glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE |GLUT_DEPTH );
   glutCreateWindow("IG. 3Dinput");

 CreaMenu();
/**/     glEnable(GL_DEPTH_TEST);
// Inicializa las funciones de dibujo y cambio de tamaño de la ventana X
   glutDisplayFunc( Dibuja );
   glutReshapeFunc( Ventana );
   glutIdleFunc( FuncFondo );

   glutKeyboardFunc(letra);
   glutSpecialFunc(especial);

/**/ //  glutPassiveMotionFunc( RatonMovido );
	   glutMotionFunc( RatonMovido );


   glutMainLoop();
   return 0;
}
