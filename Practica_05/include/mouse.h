#ifndef __mouseH__ // Para evitar doble inclusion
#define __mouseH__

/**
 * @brief Función que maneja los eventos de click de ratón
 * @param boton Código del botón presionado (izquierda, derecha, arriba...)
 * @param estado Estado del botón (presionado o no)
 * @param x Posición X del cursor en la pantalla al momento del clic
 * @param y Posición Y del cursor en la pantalla al momento del clic
*/
void clickRaton( int boton, int estado, int x, int y );

/**
 * @brief Maneja los eventos de movimiento del ratón
 * @param x Nueva posición X del cursor en la pantalla
 * @param y Nueva posición Y del cursor en la pantalla
*/
void RatonMovido( int x, int y );

// ////////// //
// PRÁCTICA 5 //
// ////////// //

/**
 * @brief Determina el objeto seleccionado en función de las coordenadas del clic
 * @param x Posición X del clic en coordenadas de pantalla
 * @param y Posición Y del clic en coordenadas de pantalla
 * @param id Referencia al identificador del objeto seleccionado
 * @return 1 si se seleccionó un objeto válido y 0 en caso contrario
*/
int pick(int x,int y, int *id);

#endif