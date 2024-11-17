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

Imprime en la consola las instrucciones del programa

**/
void printHelp ()
{

  printf ("\n\n     Prácticas de Informática Gráfica	Curso 2023-2024");
  printf ("\n\n Dpto. Lenguajes y Sistemas Informaticos");
  printf ("\n E.T.S.I. Informatica		Univ. de Granada ");
  printf ("\n");
  printf ("\n Opciones: \n\n");
  printf ("z, Z: Imprime informacion de ayuda \n");
  printf ("PgUp, PgDn: avanza y retrocede la cámara \n\n");
  printf ("+,-: avanza y retrocede la cámara \n\n");
  printf ("Teclas de movimiento de cursor: giran la camara\n");
  // Anyade la informacion de las opciones que introduzcas aqui !!       
  
  // Ayuda otras teclas

  // Práctica 2
  printf ("p,P -> Modo de visualización :puntos");
  printf ("l,L -> Modo de visualización :alambre");
  printf ("f,F -> Modo de visualización :completo");
  printf ("i,I -> Altenar activación/desactivación de luz");

  // Práctica 3
  printf ("C   -> Subir el cilindro (base del taburete)");
  printf ("c   -> Bajar el cilindro (base del taburete)");
  printf ("V   -> Rotar el asiento hacia la derecha");
  printf ("v   -> Rotar el asiento hacia la izquierda");
  printf ("B   -> Inclinar el respaldo hacia atrás ");
  printf ("b   -> Inclinar el respaldo hacia delante");
  printf ("A,a -> Alternar activación/desactivación de la animación automática");
  printf ("T,t -> Aumentar la velocidad de giro del cilindro ");
  printf ("G,g -> Reducir la velocidad de giro del cilindro");
  printf ("Y,y -> Aumentar la velcocidad de giro del asiento");
  printf ("H,h -> Reducir la velocidad de giro del asiento");
  printf ("U,u -> Aumentar la velocidad de inclinación del respaldo");
  printf ("J,j -> Reducir la velocidad de inclinación del respaldo");

  // Práctica 4
  printf ("W,w -> Alternar entre las dos posiciones de luz activas");


  printf ("");
  printf ("\n Escape: Salir");
  printf ("\n\n\n");
}


/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)

Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra

Para anyadir nuevas ordenes de teclado coloca el correspondiente case.

Parametros de entrada:

k: codigo del caracter pulsado

x:

y:

**/

float rotxCamara = 30, rotyCamara = 45;
float dCamara = 10;


void letra (unsigned char k, int x, int y)
{
  switch (k)
    {
    case 'z':
    case 'Z':
      printHelp ();		// Z y z imprimen ayuda
      break;
    case '+':			// acerca la cámara
      dCamara -= 5.0;
      break;
    case '-':			// aleja la cámara
      dCamara += 5.0;
      break;
    case 27:			// Escape  Terminar
      exit (0);
    case 'p':
    case 'P':
      setModo(1);
      break;
    case 'l':
    case 'L':
      setModo(2);
      break;
    case 'f':
    case 'F':
      setModo(3);
      break;
    case 'i':
    case 'I':
      setIluminacion(); // Práctica 1
      break;
    case 'C': // A partir de aquí es práctica 3
      if(alturaCilindro<2.0f){
        alturaCilindro+=0.1f; // Subir el cilindro 
      }
      break;
    case 'c':
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
    case 'A':
    case 'a':
      animacionActiva = !animacionActiva; // Activar / desactivar la animación automática  
      break;
    case 'T':
    case 't':
      VEL_Cilindro+=0.01f; // Aumentar la velocidad de giro del cilindro
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
    case 'w':
    case 'W':
      establecerLuzActiva(); // Práctica 4
    default:
      return;
    }
  setCamara (rotxCamara, rotyCamara, 0.0, dCamara);
  glutPostRedisplay ();		// Algunas de las opciones cambian paramentros
}				// de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes

Parametros de entrada:

k: codigo del caracter pulsado (definido en glut mediante constantes).

x:

y:

**/
void especial (int k, int x, int y)
{

  switch (k)
    {
    case GLUT_KEY_UP:
      rotxCamara += 5.0;	// Cursor arriba + rotacion x
      if (rotxCamara > 360)
	rotxCamara -= 360;
      break;
    case GLUT_KEY_DOWN:
      rotxCamara -= 5.0;
      if (rotxCamara < 0)
	rotxCamara += 360;
      break;
    case GLUT_KEY_LEFT:
      rotyCamara += 5.0;
      if (rotyCamara > 360)
	rotyCamara -= 360;
      break;
    case GLUT_KEY_RIGHT:
      rotyCamara -= 5.0;
      if (rotyCamara < 0)
	rotyCamara += 360;
      break;
    case GLUT_KEY_PAGE_DOWN:	// acerca la cámara
      dCamara -= 5.0;
      break;
    case GLUT_KEY_PAGE_UP:	// aleja la cámara
      dCamara += 5.0;
      break;
    default:
      return;
    }
  setCamara (rotxCamara, rotyCamara, 0.0, dCamara);
  glutPostRedisplay ();		// Actualiza la imagen (ver proc. letra)
}
