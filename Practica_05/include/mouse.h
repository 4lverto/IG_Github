#ifndef __mouseH__ // Para evitar doble inclusion
#define __mouseH__


void clickRaton( int boton, int estado, int x, int y );
void RatonMovido( int x, int y );

// ////////// //
// PRÁCTICA 5 //
// ////////// //

int pick(int x,int y, int *id);

#endif