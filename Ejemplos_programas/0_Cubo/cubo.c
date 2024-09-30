// BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float roty=30.0; // Variable que indica la rotación (en grados)
float plano_base=30.0;


// ///// //
// PLANO //
// ///// //

/**
 * @brief Construye un plano horizontal de tamano t x t
 * @param t Tamaño del plano
*/
void plano( float t ){
  
  /*En este bloque se especifica la normal (vector  perpendicular de módulo). 
    En este caso, como el plano es horizontal, la normal es el vector (0,1,0). 
    
    Finalmente, se indican los vértices del cuadrilátero, 
    que deberán estar en sentido antihorario cuando se ve el cuadrilátero por la cara delantera 
  */

  t=plano_base;

  glBegin( GL_QUADS ); // Comienza la definición de un cuadrado
    glNormal3f( 0.0, 1.0, 0.0 ); // Se establece la normal para el plano apuntando hacia arriba (en la dirección del Eje Y) 
    glVertex3f(  t, 0,  t ); // Se definen las coordenadas de los 4 vértices que componen el plano.
    glVertex3f(  t, 0, -t );
    glVertex3f( -t, 0, -t );
    glVertex3f( -t, 0,  t );
  glEnd(); // Finaliza la definición de un cuadrado.
}

// ////// //
// DIBUJA //
// ////// //
/**
 * @brief Función que renderiza la escena 3D, que consiste en un plano y un cubo morado que rota
 * @post Cada vez que se llama a Dibuja() se visualiza un nuevo frame
*/
void Dibuja( )
{
  float pos[4] = {5.0, 5.0, 10.0, 0.0 }; // Posición de la fuente de luz
  float morado[4]={0.8,0,1,1}, verde[4]={0,1,0,1};

  glClearColor(1,1,1,1); // Se define el color del fondo a blanco

  glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT ); // Se limpia el buffer de color y el de profundidad para preparar el siguiente fotograma
  glLoadIdentity(); // Reseteo de la matriz de modelado/vista
  glTranslatef(-0.5,-0.5,-100); // Se traslada la cámara para alejarla y ver la escena desde una posición más alejada
  glLightfv( GL_LIGHT0, GL_POSITION, pos ); // Se coloca la fuente de luz en la posición contenida en "pos[]" en el espacio de la cámara
  glRotatef( 20, 1.0, 0.0, 0.0 ); // Aplica una rotación de 20 grados alrededor del eje X para inclinar la vista
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde );// Se define el material del plano con color verde
  
  plano(30); // Se dibuja el plano de tamaño 30x30 (el suelo verde)
  
  glRotatef( roty, 0.0, 1.0, 0.0 ); // Rota la escena alrededor del eje Y por un ángulo almacenado en roty (30º).
  // Ese ángulo cambinará contínuamente debido a la función idle(), haciendo que el cubo rote.
  glTranslatef(0,5,0); // TRaslada el cubo hacia arriba del eje Y para que esté por encima del plano
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, morado ); // DEfine el material del cubo con color morado
  glutSolidCube(10); // Dibuja un cubo sólido de tamaño 10
  glutSwapBuffers(); // Cambia los buffers para mostrar el resultado en pantalla.
  // Esto último es necesario porque se usa GLUT_DOUBLE, lo que habilita el doble buffering para evitar el parpadeo
}


// /////// //
// VENTANA //
// /////// //

/**
 * @brief Indica en qué parte de la ventana debe dibujarse y cómo se proyecta el modelo en la pantalla
 * @param ancho
 * @param alto
 * @pre Se ejecuta cuando se cambia la ventana, recibe el ancho y alto de la ventana X
 * @post Ajusta el área de visualización y la proyección para que la escena 3D se vea correctamente
*/
void Ventana(GLsizei ancho,GLsizei alto){ 
    float D=ancho; if(D<alto) D=alto;
    glViewport(0,0,ancho,alto); // Define el área de dibujo (viewport) dentro de la ventana
    glMatrixMode(GL_PROJECTION); // Cambia el modo de la matriz a proyección para ajustar la perspectiva
    glLoadIdentity(); // Resetea la matriz de proyección
    glFrustum(-ancho/D,ancho/D,-alto/D,alto/D,5,250); // Define un frustum; 
    // Es decir, que los objetos más cercanos se ven más grandes que los lejanos, creando un efecto 3D
    glMatrixMode(GL_MODELVIEW); // Regresa al modo de modelado/vista para seguir manipulando la posición y rotación de los objetos
}

// //////////// //
// FUNCIÓN IDLE //
// //////////// //

/**
 * @brief Se ejecuta como función de fondo (siempre que no hay otra función que procesar.)
 * @brief Se llama contínuamente cuando la ventana no está siendo redibujada o no hay interacción del usuario
*/
void idle(){
  roty +=0.15; // Aumenta el ángulo de rotación 0,15 grados, lo que produce un efecto de rotación contínua
  glutPostRedisplay(); // Indica que es necesario generar un nuevo frame
}


// ////////////////// //
// PROGRAMA PRINCIPAL //
// ////////////////// //

// Punto de entrada del programa - Donde se inicializa GLUT y se configuran las funciones de callback
int main( int argc, char *argv[] ){

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