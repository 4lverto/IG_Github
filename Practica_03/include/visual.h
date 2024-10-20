// visual.h


#include <GL/gl.h>

//======================== visual.c


/** 	void setCamara()

Cambia los parámetros de la cámara en el modulo visual

**/
void setCamara (float ax, float ay, float az, float d);

void getCamara (float &ax, float &ay, float &az, float &d);

/** 	void transformacionVisualizacion()

Fija la transformacion de visualizacion en funcion de los angulos de rotacion view_rotx,
view_roty y view_rotz y el desplazamiento de la camara d.

**/
void transformacionVisualizacion ();

/**	void fijaProyeccion()

Fija la transformacion de proyeccion en funcion del tamaño de la ventana y del tipo de proyeccion

**/
void fijaProyeccion ();


/**	void inicializaVentana(GLsizei ancho,GLsizei alto)

Inicializa el viewport para que ocupe toda la ventana X, y llama a fijaProyeccion.

**/

void inicializaVentana (GLsizei ancho, GLsizei alto);
