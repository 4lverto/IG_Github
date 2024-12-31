
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

// PRÁCTICA 4

/**
 * @brief Función para altenar entre los focos de luz 
*/
void establecerLuzActiva();

// ////////// //
// PRÁCTICA 5 //
// ////////// //

/**
 * @brief Función para asignar colores únicos a objetos seleccionables
 * @param id ID del objeto 
*/
void colorSeleccion(int id);

/**
 * @brief Función para dibujar la escena
*/
void dibujaEscena();

/**
 * @brief Devuelve si se está seleccionando algún objeto o no
 * @return TRUE si se está seleccionando algún objeto y FALSE en caso contrario
*/
bool getModoSeleccion();

/**
 * @brief Actualiza el estado del modo selección de dibujado de algún objeto
 * @param s TRUE si se está seleccionando el objeto FALSE en caso contrario
*/
void setModoSeleccion(bool s);


// DIBUJAR LAS MESAS

/**
 * @brief Función que dibuja una mesa larga marrón
*/
void dibujaMesa();

/**
 * @brief Función que dibuja la tarima que simula ser el suelo
*/
void dibujarSuelo();

// MOVIMIENTO DE LOS TABURETES

/**
 * @brief Hace que el taburete pasado como parámetro gire
 * @param ntaburete ID del taburete que hay que girar
*/
void girar(int ntaburete);

/**
 * @brief Hace que un taburete determinado se mueva una cantidad de unidades
 * @param ntaburete ID del taburete que se va a mover
 * @param coordenada Coordenada (x o z) en la que se va a mover el taburete
 * @param cantidad Número de unidades que se va a mover el taburete
*/
void moverse(int ntaburete,char coordenada,float cantidad);

/**
 * @brief Comprueba si el taburete que se intenta mover ha llegado a los límites definidos en X
 * @param ntaburete ID del taburete a mover
 * @param cantidad Cantidad de unidades que se va a mover el taburete
 * @return TRUE si el taburete aún no ha llegado al límite y FALSE en caso contrario
*/
bool comprobarTopeX(int ntaburete,float cantidad);

/**
 * @brief Comprueba si el taburete que se intenta mover ha llegado a los límites definidos en Z
 * @param ntaburete ID del taburete a mover
 * @param cantidad Cantidad de unidades que se va a mover el taburete
 * @return TRUE si el taburete aún no ha llegado al límite y FALSE en caso contrario
*/
bool comprobarTopeZ(int ntaburete,float cantidad);

// ANIMACIÓN DEL DADO

/**
 * @brief Devuelve si el dado está haciendo la animación o no
 * @return TRUE si se está ejecutando la animación y FALSE en caso contrario
*/
bool getDadoEnAnimacion();

/**
 * @brief Establece si el dado va a hacer la animación o no
 * @param b TRUE si va a empezar la animación y FALSE si la ha terminado
*/
void setDadoEnAnimacion(bool b);

/**
 * @brief Actualiza la altura del dado para simular el lanzamiento
 * @param a Nueva altura del dado
*/
void setAlturaDado(float a);

/**
 * @brief Actualiza la cantidad de grados de rotación del dado en el eje X
 * @param r Grados de rortación en el eje X
*/
void setRotacionDadoX(float r);

/**
 * @brief Actualiza la cantidad de grados de rotación del dado en el eje Y
 * @param r Grados de rortación en el eje Y
*/
void setRotacionDadoY(float r);

/**
 * @brief Actualiza la cantidad de grados de rotación del dado en el eje Z
 * @param r Grados de rortación en el eje Z
*/
void setRotacionDadoZ(float r);

/**
 * @brief Cambia la nueva cara del dado resultante del lanzamiento
 * @param c Nueva cara del dado
*/
void cambiarCaraVisible(int c);

// TEXTO

/**
 * @brief Función que dibuja texto en la escena
 * @param text
 * @param length
 * @param x
 * @param y
*/
void dibujaTexto(const char *text, int length, int x, int y);

// PELOTA

/**
 * @brief Actualiza el estado de animación de la pelota
 * @param b TRUE Si va a realizar la animación y FALSE si la ha terminado
*/
void setPelotaEnAnimacion(bool p);

/**
 * @brief Devuelve si la pelota está haciendo la animación o no
 * @return TRUE si la pelota se encuentra durante la animación y FALSE en caso contrario
*/
bool getPelotaEnAnimacion();

class Objeto3D{ 
	public: 

	virtual void draw( ) = 0; // Dibuja el objeto
};