
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


// PRÁCTICA 5

/**
 * @brief Función para asignar colores únicos a objetos seleccionables
 * @param id
 * @param componente
*/
void colorSeleccion(int id/*, int componente*/);

/**
 * @brief
 * @param seleccion
*/
void dibujaEscena(/*bool seleccion*/);

/**
 * @brief 
*/
bool getModoSeleccion();

/**
 * @brief 
*/
void setModoSeleccion(bool s);

// DIBUJAR LAS MESAS

void dibujaMesa();

void dibujaMesaPequenia();

// MOVIMIENTO DE LOS TABURETES

void girar(int ntaburete);

void moverse(int ntaburete,char coordenada,float cantidad);

bool comprobarTopeX(int ntaburete,float cantidad);

bool comprobarTopeZ(int ntaburete,float cantidad);

// ANIMACIÓN DEL DADO

bool getDadoEnAnimacion();

void setDadoEnAnimacion(bool b);

void setAlturaDado(float a);

void setRotacionDadoX(float r);

void setRotacionDadoY(float r);

void setRotacionDadoZ(float r);

void cambiarCaraVisible(int c);

void seleccionarMalla(int n);

bool mallaSeleccionada(int n);

void drawText(const char *text, int length, int x, int y);

class Objeto3D{ 
	public: 

	virtual void draw( ) = 0; // Dibuja el objeto
};