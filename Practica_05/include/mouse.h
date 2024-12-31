#ifndef __mouseH__ // Para evitar doble inclusion
#define __mouseH__

/**
 * @brief
*/
void clickRaton( int boton, int estado, int x, int y );

/**
 * @brief
*/
void RatonMovido( int x, int y );

// ////////// //
// PRÁCTICA 5 //
// ////////// //

/**
 * @brief
*/
int pick(int x,int y, int *id);

#endif