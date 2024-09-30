#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> 

float roty=30.0; 

// ///// //
// PLANO //
// ///// //

void plano( float t ){
  glBegin( GL_QUADS ); 
    glNormal3f( 0.0, 1.0, 0.0 );     
    glVertex3f(  t, 0,  t );
    glVertex3f(  t, 0, -t );
    glVertex3f( -t, 0, -t );
    glVertex3f( -t, 0,  t );
  glEnd();
}


// ////// //
// DIBUJA //
// ////// //

void Dibuja( ){
  
  // luz[4] = {x,y,z,w}
  float luz[4] = {5.0, 5.0, 10.0, 0.0 };
  float sin_luz[4] = {0.0, 0.0, 0.0, 0.0 }; 
  float luz_arriba[4] = {0.0, 10.0, 0.0, 0.0 };
  float luz_abajo[4] = {0.0, -10.0, 0.0, 0.0 };
  float luz_derecha[4] = {10.0, 0.0, 0.0, 0.0 }; 
  float luz_izquierda[4] = {-10.0, 0.0, 0.0, 0.0 };
  float luz_cercana[4] = {0.0, 0.0, 10.0, 0.0 }; 
  float luz_lejana[4] = {0.0, 0.0, -10.0, 0.0 };

  // Colores
  float morado[4]={0.8,0,1,1};
  float verde[4]={0,1,0,1};
  float rojo[4]={1,0,0,1};
  float azul[4]={0,0,1,1};
  float negro[4]={0,0,0,1};
  float blanco[4]={1,1,1,1};

  glClearColor(1,1,1,1); // Color de fondo (blanco)

  glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  glTranslatef(-0.5,-0.5,-150);
  glLightfv( GL_LIGHT0, GL_POSITION, luz );
  glRotatef( 20, 1.0, 0.0, 0.0 );
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo );
  
  plano(30); // EL suelo rojo
  
  glRotatef( roty, 0.0, 1.0, 0.0 );
  glTranslatef(0,5,0);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, azul );
  glutSolidCube(10);
  glutSwapBuffers();
}

// /////// //
// VENTANA //
// /////// //

void Ventana(GLsizei ancho,GLsizei alto){

    float D=ancho;
    
    if(D<alto){
        D=alto;
    }

    glViewport(0,0,ancho,alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ancho/D,ancho/D,-alto/D,alto/D,5,250);
    glMatrixMode(GL_MODELVIEW);
}

// //////////// //
// FUNCIÓN IDLE //
// //////////// //

void idle(){

  roty +=0.15; 
  glutPostRedisplay(); 
}

// ////////////////// //
// PROGRAMA PRINCIPAL //
// ////////////////// //

int main( int argc, char *argv[] ){

  glutInit( &argc, argv );

  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutCreateWindow("IG: cubo rotando");

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