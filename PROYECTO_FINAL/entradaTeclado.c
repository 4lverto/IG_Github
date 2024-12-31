/*
=======================================================/
modulo entradaTeclado.c
	Gestion de eventos de teclado
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "include/practicasIG.h"

/**
 * @brief Imprime por consola las instrucciones del programa
*/
void printHelp (){

  printf ("\n\n     Prácticas de Informática Gráfica	Curso 2023-2024");
  printf ("\n\n Dpto. Lenguajes y Sistemas Informaticos");
  printf ("\n E.T.S.I. Informatica		Univ. de Granada ");
  printf ("\n");
  printf ("\n Opciones: \n\n");
  printf ("z, Z: Imprime informacion de ayuda \n");
  printf ("PgUp, PgDn: avanza y retrocede la cámara \n\n");
  printf ("+,-: avanza y retrocede la cámara \n\n");
  printf ("Teclas de movimiento de cursor: giran la camara\n");
  // Añade la informacion de las opciones que introduzcas aqui !!       
  
  // Ayuda otras teclas

  // Práctica 2
  printf ("\n\np,P -> Modo de visualización :puntos\n");
  printf ("l,L -> Modo de visualización :alambre\n");
  printf ("f,F -> Modo de visualización :completo\n");
  printf ("i,I -> Altenar activación/desactivación de luz\n");

  // Práctica 3
  printf ("\nN   -> Subir los cilindros (base del taburete)\n");
  printf ("n   -> Bajar los cilindro (base del taburete)\n");
  printf ("V   -> Rotar los asiento hacia la derecha\n");
  printf ("v   -> Rotar los asiento hacia la izquierda\n");
  printf ("B   -> Inclinar el respaldo hacia atrás\n");
  printf ("b   -> Inclinar el respaldo hacia delante");
  printf ("M,m -> Alternar activación/desactivación de la animación automática\n");
  printf ("T,t -> Aumentar la velocidad de giro del cilindro\n");
  printf ("G,g -> Reducir la velocidad de giro del cilindro\n");
  printf ("Y,y -> Aumentar la velcocidad de giro del asiento\n");
  printf ("H,h -> Reducir la velocidad de giro del asiento\n");
  printf ("U,u -> Aumentar la velocidad de inclinación del respaldo\n");
  printf ("J,j -> Reducir la velocidad de inclinación del respaldo\n");

  // Práctica 4
  printf ("\nW,w -> Alternar entre las dos posiciones de luz activas\n");

  printf ("\n Escape: Salir");
  printf ("\n\n\n");
}


/* @teclado ---------------------------------------------------------------- */

float rotxCamara = 30, rotyCamara = 45;
float dCamara = 40;

void letra (unsigned char k, int x, int y)
{

  3.0f;
  switch (k)
    {
    case '<':
    case '>':
      printHelp ();		// < y > imprimen ayuda
      break;
    case '+':			// acerca la cámara
      if(camaraActual==0){camY -= 3.0f;}
      if(camaraActual==1){camY -= 3.0f;}
      if(camaraActual==2){
        dCamara-=5.0;
      }
      break;
    case '-':			// aleja la cámara
      if(camaraActual==0){camY += 3.0f;}
      if(camaraActual==1){camY += 3.0f;}
      if(camaraActual==2){
        dCamara+=5.0;
      }
      break;
    case 27:			// Escape  Terminar
      exit (0);
    case 'p':
    case 'P':
      setModo(1); // Modo de visualización en lineas
      break;
    case 'l':
    case 'L':
      setModo(2); // Modo de visualización con puntos
      break;
    case 'f':
    case 'F':
      setModo(3); // Modo de visualización objetos rellenos
      break;
    case 'i':
    case 'I':
      setIluminacion(); // Alterna entre iluminación activada y desactivada
      break;
    case 'M':
    case 'm':
      animacionActiva = !animacionActiva; // Activar / desactivar la animación automática  
      break;
    case 'N': 
      if(alturaCilindro<2.0f){
        alturaCilindro+=0.1f; // Subir el cilindro 
      }
      break;
    case 'n':
      if(alturaCilindro>0.5f){
        alturaCilindro-=0.1f; // Bajar el cilindro 
      }
      break;
    case 'V':
      rotacionAsiento-=1.0f; // Rotar asiento a la izquierda
      break;
    case 'v':
      rotacionAsiento+=2.0f; // Rotar asiento a la derecha
      break;
    case 'B':
      if(inclinacionRespaldo>-25.0f){
        inclinacionRespaldo-=0.5f; // Inclinar respaldo hacia la izquierda
      }
      break;
    case 'b':
      if(inclinacionRespaldo<0.0f){
        inclinacionRespaldo+=0.5f; // Inclinar respaldo hacia delante
      }
      break;
    case 'T':
    case 't':
      VEL_Cilindro+=0.01f; // Aumentar la velocidad de subida y bajada del cilindro
      break;
    case 'G':
    case 'g':
      if(VEL_Cilindro > 0.01f){ // Reducir la velocidad de giro del cilindro
        VEL_Cilindro-=0.01f;
      }
      break;
    case 'Y':
    case 'y':
      VEL_Asiento+=0.1f; // Aumentar la velocidad de giro del asiento
      break;
    case 'H':
    case 'h':
      if(VEL_Asiento > 0.1f){ // Reducir la velocidad de giro del asiento
        VEL_Asiento-=0.1f;
      }
      break;
    case 'U':
    case 'u':
      VEL_Respaldo+=0.1f; // Aumentar la velocidad de inclinación del respaldo
      break;
    case 'J':
    case 'j':
      if(VEL_Respaldo > 0.1f){ // Reducir la velocidad de inclinación del respaldo
        VEL_Respaldo-=0.1f;
      }
      break;
    case 'q':
    case 'Q':
      establecerLuzActiva(); // Alterna los focos de luz
      break;
    case 'A':
      moverse(1,'x',5); // Mueve el taburete 1 en el eje X 5 unidades
      break;
    case 'a':
      moverse(1,'x',-5); // Mueve el taburete 1 en el eje X -5 unidades
      break;
    case 'S':
      moverse(2,'x',5); // Mueve el taburete 2 en el eje X 5 unidades
      break;
    case 's':
      moverse(2,'x',-5); // Mueve el taburete 2 en el eje X -5 unidades
      break;
    case 'D':
      moverse(3,'x',5); // Mueve el taburete 3 en el eje X 5 unidades
      break;
    case 'd':
      moverse(3,'x',-5); // Mueve el taburete 4 en el eje X -5 unidades
      break;
    case 'Z':
      moverse(1,'z',5); // Mueve el taburete 1 en el eje Z 5 unidades
      break;
    case 'z':
      moverse(1,'z',-5); // Mueve el taburete 1 en el eje Z -5 unidades
      break;
    case 'X':
      moverse(2,'z',5); // Mueve el taburete 2 en el eje Z 5 unidades
      break;
    case 'x':
      moverse(2,'z',-5); // Mueve el taburete 2 en el eje Z -5 unidades
      break;
    case 'C':
      moverse(3,'z',5); // Mueve el taburete 3 en el eje Z 5 unidades
      break;
    case 'c':
      moverse(3,'z',-5); // Mueve el taburete 3 en el eje Z -5 unidades
      break;
    case '1':
      girar(1); // Gira el taburete 1 90º
      break;
    case '2':
      girar(2); // Gira el taburete 1 90º
      break;
    case '3':
      girar(3); // Gira el taburete 1 90º
      break;
    case ' ':
      setPelotaEnAnimacion(true); // Inicia la animación de la pelota (rebote)
      break;
    default:
      printf("\nNo has pulsado una tecla identificada\n");
      return;
    }
  
  // En caso de estar en la cámara 2 (original), se gestiona de la manera por defecto
  if(camaraActual==2){
    setCamara (rotxCamara, rotyCamara, 0.0, dCamara);
  }

  if(camaraActual==0 || camaraActual==1){
    actualizarCamara();
  }

  glutPostRedisplay ();		// Algunas de las opciones cambian paramentros
}

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes
**/
void especial (int k, int x, int y){

  switch (k){
    case GLUT_KEY_UP:
      if(camaraActual==0){camZ -= 3.0f;}
      if(camaraActual==1){camX += 3.0f;}
      if(camaraActual==2){
        rotxCamara += 5.0;	// Cursor arriba + rotacion x
        if (rotxCamara > 360) rotxCamara -= 360;
      }

      break;
    case GLUT_KEY_DOWN:
      if(camaraActual==0){camZ += 3.0f;}
      if(camaraActual==1){camX -= 3.0f;}
      if(camaraActual==2){
        rotxCamara -= 5.0;
        if (rotxCamara < 0) rotxCamara += 360;
      }

      break;
    case GLUT_KEY_LEFT:
      if(camaraActual==0){camX -= 3.0f;}
      if(camaraActual==1){camZ -= 3.0f;}
      if(camaraActual==2){
        rotyCamara += 5.0;
        if (rotyCamara > 360) rotyCamara -= 360;
      }

      break;
    case GLUT_KEY_RIGHT:
      if(camaraActual==0){camX += 3.0f;}
      if(camaraActual==1){camZ += 3.0f;}
      if(camaraActual==2){
        rotyCamara -= 5.0;
        if (rotyCamara < 0) rotyCamara += 360;
      }
      break;
    case GLUT_KEY_PAGE_DOWN:	// acerca la cámara
      if(camaraActual==0){camY -= 3.0f;}
      if(camaraActual==1){camY -= 3.0f;}
      if(camaraActual==2){
        dCamara -= 5.0;
      }

      break;
    case GLUT_KEY_PAGE_UP:	// aleja la cámara
      if(camaraActual==0){camY += 3.0f;}
      if(camaraActual==1){camY += 3.0f;}
      if(camaraActual==2){
        dCamara += 5.0;
      }
      break;
    default:
      return;
  }

  if(camaraActual==2){
    setCamara (rotxCamara, rotyCamara, 0.0, dCamara);
  }

  if(camaraActual==0 || camaraActual==1){
    actualizarCamara();
  }

  glutPostRedisplay ();		// Actualiza la imagen (ver proc. letra)
}