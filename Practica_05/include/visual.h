/*	Prácticas de Informática Gráfica
	visual.h
*/

#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include <GL/gl.h>

//======================== visual.c

/**
 * @brief Cambia los parámetros de la cámara en el módulo visual
 * @param ax Ángulo de rotación en el eje X
 * @param ay Ángulo de rotación en el eje Y
 * @param az Ángulo de rotación en el eje Z
 * @param d Distancia de la cámara al objeto
*/
void setCamara (float ax, float ay, float az, float d);

/**
 * @brief Obtiene los parámetros actuales de la cámara
 * @param ax Referencia para almacenar el ángulo de rotación en el eje X
 * @param ay Referencia para almacenar el ángulo de rotación en el eje Y
 * @param az Referencia para almacenar el ángulo de rotación en el eje Z
 * @param d Referencia para almacenar la distancia de la cámara al objeto
*/
void getCamara (float &ax, float &ay, float &az, float &d);

/**
 * @brief Fija la transformación de visualización en función de los ángulos de rotación
 * (view_rotx,view_roty,view_rotz) y el desplazamiento de la cámara d
*/
void transformacionVisualizacion ();

/**
 * @brief Fija la transformación de proyección en función del tamaño de la ventana y el tipo de proyección
*/
void fijaProyeccion ();

/**
 * @brief Inicializa el viewport para que ocupe toda la ventana X y llama a fijarProyección
 * @param ancho Anchura de la ventana
 * @param alto Altura de la ventana
*/
void inicializaVentana (GLsizei ancho, GLsizei alto);