/*	Prácticas de Informática Gráfica
	entradaTeclado.h
*/

/**	
	Funcion de captura de eventos pulsacion de tecla correspondiente a caracter alfanumerico
	K: codigo ascii del caracter
	x: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
	y: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
**/
void letra (unsigned char k, int x, int y);

/**
	Funcion de captura de eventos pulsacion de caracteres especiales y de control
	K: codigo del control pulsado (se definen como constantes en glut.h)
	x: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
	y: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
**/
void especial (int k, int x, int y);

// ////////// //
// PRÁCTICA 5 //
// ////////// //