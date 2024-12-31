/*	Prácticas de Informática Gráfica
	practicasIG.h
*/
#include  "modelo.h"
#include  "mouse.h"
#include  "entradaTeclado.h"
#include  "visual.h"
#include  "file_ply_stl.h"

/**
 * @brief
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

#define ID_TABURETE1 1
#define ID_TABURETE2 2
#define ID_TABURETE3 3
#define ID_DADO 4

// PROYECTO FINAL

/**
 * @brief
*/
struct PosicionCamara{
  float eyeX, eyeY, eyeZ;
  float centerX, centerY, centerZ;
  float upX,upY,upZ;
};

/**
 * @brief
*/
void actualizarCamara();

/**
 * @brief
*/
extern int camaraActual;

/**
 * @brief
*/
extern float camX,camY,camZ; // Posición de la cámara
extern float lookX,lookY,lookZ; // Punto de enfoque actual
extern float upX,upY,upZ; // Vector "arriba" actual


/**
 * @brief
*/
extern float eyeX;
extern float eyeY;
extern float eyeZ;

/**
 * @brief
*/
extern PosicionCamara camaras[];