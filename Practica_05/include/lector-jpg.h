// *********************************************************************
// **
// ** Lector de archivos JPG (declaraciones)
// **
// *********************************************************************

#ifndef LECTOR_IMAGEN_JPEG_HPP
#define LECTOR_IMAGEN_JPEG_HPP

#include <string>
#include <cstdlib>
#include <iostream>
#include <jpeglib.h>

//----------------------------------------------------------------------
// Función de lectura de una imagen
//
// * Devuelve un puntero a los pixels (tres bytes por pixel, por filas)
// * Escribe en los parámetros de salida 'ancho' y 'alto' el número de columnas
//   y filas de la imagen, respectivamente.
// * El nombre del archivo debe ir con el 'path' (relativo o absoluto)
//   no está se busca en 'archivos-alumno'
//
// código adaptado a C++11 a partir de:
// https://github.com/Tinker-S/libjpeg-sample/blob/master/jpeg_sample.c

unsigned char * LeerArchivoJPEG( const char *nombre_arch, unsigned &ancho, unsigned &alto );



#endif
