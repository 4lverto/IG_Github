/*	Prácticas de Informática Gráfica
	practicasIG.h
*/
#include  "modelo.h"
#include  "mouse.h"
#include  "entradaTeclado.h"
#include  "visual.h"
#include  "file_ply_stl.h"

/**
 * @brief Indica si la iluminación está activada
*/
extern bool iluminacionActivada;

// PRÁCTICA 2
#include "Punto3D.h"
#include "Triangulo.h"
#include "Malla.h"

// PRÁCTICA 3
#include  "Taburete.h"

// PRÁCTICA 4
#include "lector-jpg.h"
#include "Dado.h"

// PRÁCTICA 5

#define ID_TABURETE1 1  ////< Identificador del primer taburete
#define ID_TABURETE2 2  ////< Identificador del segundo taburete
#define ID_TABURETE3 3  ////< Identificador del tercer taburete
#define ID_DADO 4       ////< Identificador del dado

// PROYECTO FINAL

/**
 * @brief Estructura que almacena la configuración de la posición de una cámara
*/
struct PosicionCamara{
  float eyeX, eyeY, eyeZ;           ////< Coordenadas del punto de vista de la cámara
  float centerX, centerY, centerZ;  ////< Coordenadas del punto dentral al que la cámara apunta
  float upX,upY,upZ;                ////< Componentes (coordenadas) del vector "arriba"
};

/**
 * @brief Actualiza la configuración de la cámara activa
*/
void actualizarCamara();

/**
 * @brief Índice de la cámara actualmente activa
*/
extern int camaraActual;

/**
 * @brief Coordenadas actuales de la posición de la cámara
*/
extern float camX,camY,camZ; 

/**
 * @brief Coordenadas del punto de enfoque actual de la cámara
*/
extern float lookX,lookY,lookZ;

/**
 * @brief Componentes (coordenadas) del vector "arriba"
*/
extern float upX,upY,upZ;

/**
 * @brief Coordenadas de la posición del ojo (POV) de la cámara
*/
extern float eyeX,eyeY,eyeZ;

/**
 * @brief Array que contiene las configuraciones de las 3 cámaras definidas
*/
extern PosicionCamara camaras[];