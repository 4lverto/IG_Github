/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel ();

/**
 * Función que controla el tipo de Modo
*/
void setModo(int M);

/**
 * Función que controla la iluminación
*/
void setIluminacion();

class Objeto3D { 
public: 

virtual void draw( ) = 0; // Dibuja el objeto
} ; 
