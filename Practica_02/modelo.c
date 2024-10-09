#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include <vector>

using namespace std;

/**
 * @brief Inicializa el modelo y de las variables globales
*/
void
initModel (){
}

                  // /////////////// //
                  // "SUBCLASE" EJES //
                  // /////////////// //

class Ejes:Objeto3D { 
  public: 
      float longitud = 30;
  // Dibuja el objeto
  void draw( ){
    glBegin (GL_LINES);
    {
      glColor3f (0, 1, 0);
      glVertex3f (0, 0, 0);
      glVertex3f (0, longitud, 0);

      glColor3f (1, 0, 0);
      glVertex3f (0, 0, 0);
      glVertex3f (longitud, 0, 0);

      glColor3f (0, 0, 1);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, longitud);
    }
    glEnd ();
  }
}; 

                // ////////// //
                // PRACTICA 2 //
                // ////////// //

// //////////////////////////////// //
// ESTRUCTURAS AUXILIARES DEFINIDAS //
// //////////////////////////////// //

    // /////// //
    // PUNTO3D //
    // /////// //

struct Punto3D{
  
  // ATRIBUTOS

  float x,y,z; // Representan las 3 coordenadas

  // MÉTODOS DEFINIDOS

  /**
   * @brief Constructor sin parámetros. Crea un Punto3D con todas las coordenadas a 0
  */
  Punto3D(){
    this->x=0;
    this->y=0;
    this->z=0;
  }

  /**
   * @brief Constructor con parámetros. 
   * @param _x Coordenada X
   * @param _y Coordenada Y
   * @param _z Coordenada Z
  */
  Punto3D(float _x, float _y, float _z){
    this->x=_x;
    this->y=_y;
    this->z=_z;
  }

  /**
   * @brief Sobrecarga del operador de suma. Suma cada coordenada con la coordenada correspondiente del Punto3D pasado como parámetro
   * @param p Es un Punto3D dado
   * @return El punto con las coordenadas actualizadas
  */
  Punto3D operator+(const Punto3D &p) const{
    Punto3D miPunto(this->x + p.x , this->y + p.y , this->z + p.z);
    return miPunto;
  }

  /**
   * @brief Sobrecarga del operador de resta. Resta cada coordenada con la coordenada correspondiente del Punto3D pasado como parámetro
   * @param p Es un Punto3D dado
   * @return El punto con las coordenadas actualizadas
  */
  Punto3D operator-(const Punto3D &p) const{
    Punto3D miPunto(this->x - p.x , this->y - p.y , this->z - p.z);
    return miPunto;
  }

  /**
   * @brief Sobrecarga del operador de división. Suma cada coordenada con la coordenada correspondiente del Punto3D pasado como parámetro
   * @param p Es un Punto3D dado
   * @return El punto con las coordenadas actualizadas
  */
  Punto3D operator/(float div) const{
    Punto3D miPunto(this->x/div , this->y/div , this->z/div);
    return miPunto;
  }

  /**
   * @brief Se realiza el producto vectorial entre los dos puntos (el actual y el pasado como parámetro)
   * @param p Punto con el que se hace el producto vectorial
   * @return Punto con las coordenadas actualizadas tras el producto vectorial
  */
  Punto3D productoVectorial(const Punto3D &p) const{
    Punto3D miPunto;
    miPunto.x = (this->y*p.z)-(this->z*p.y);
    miPunto.y = (this->z*p.x)-(this->x*p.z);
    miPunto.z = (this->x*p.y)-(this->y*p.x);

    return miPunto;
  }

  /**
   * @brief Función que calculará el módulo del Punto3D
   * @pre El módulo no debe ser 0
   * @return Módulo del Punto3D
  */
  float modulo() const{
    // Calculamos los "cuadrados" de las coordenadas
    float equis=this->x * this->x;
    float igriega=this->y * this->y;
    float ceta=this->z * this->z;

    float modulo=sqrt(equis+igriega+ceta);

    if(modulo==0){
      cout << "\n OJO!! El módulo es 0, luego no se va a dividir bien \n";
    }
    
    return modulo;
  }

  // Función que finalmente normaliza el Punto3D dividiendo cada coordenada entre el módulo
  void normaliza(){
    float modulo=this->modulo();

    if(modulo!=0){
      this->x = this->x/modulo;
      this->y = this->y/modulo;
      this->z = this->z/modulo;
    }
  }
};

    // ///////// //
    // TRIÁNGULO //
    // ///////// //

struct Triangulo{
  int v0,v1,v2;
  /**
   * @brief Constructor sin parámetros. Construye un triángulo cuyos 3 índices de sus vértices son 0
  */
  Triangulo(){
    this->v0=0;
    this->v1=0;
    this->v2=0;
  }

  /**
   * @brief Constructor con parámetros. Se establecen los 3 índices de los puntos que representarán cada vértice del triángulo
   * @param a Será el índice que corresponde al primer vértice
   * @param b Será el índice que corresponde al segundo vértice
   * @param c Será el índice que corresponde al tercer vértice
   * @return Triángulo compuesto por 3 índices de vértices determinados
  */
  Triangulo(int a,int b,int c){
    this->v0=a;
    this->v1=b;
    this->v2=c;
  }

  /**
   * @brief Obtiene el índice del primer vértice
   * @return Índice del primer vértice
  */
  int getI0(){
    return this->v0;
  }

  /**
   * @brief Obtiene el índice del segundo vértice
   * @return Índice del segundo vértice
  */
  int getI1(){
    return this->v1;
  }

  /**
   * @brief Obtiene el índice del tercer vértice
   * @return Índice del tercer vértice
  */
  int getI2(){
    return this->v2;
  }
};

// //////////////// //
// "SUBCLASE" MALLA //
// //////////////// //

class Malla:Objeto3D{
  public:
    // ATRIBUTOS

    vector<float> vertices_ply; // Coordenadas de los vértices --> {0,1,3 , 5,-2,6, , 4,1,2 , ...} --> Cada "trío" de números representan las coordenadas de un vértice
    vector<int> caras_ply;  // Índices de los vértices --> caras_ply[0],caras_ply[1],caras_ply[2] representa el primer triángulo
    
    vector<Punto3D> normales_caras; // Normales de las caras
    vector<Punto3D> normales_vertices;// Normales de los vértices

    vector<Punto3D> vertices; // Contenedor de Punto3D. Contendrá todos los vértices
    vector<Triangulo> caras; // Contenedor de Triangulos. Cada Triángulo contendrá los 3 indices (posición en el vector vertices) correspondientes a sus 3 vértices

    // OPCIONAL - Eliminar este atributo y simplemente llamar a glShadeModel("tipo") en la función Dibuja
    bool suave; // Será TRUE cuando la Malla se tenga que dibujar con sombreado SMOOTH y FALSE cuando la malla tenga un sombreado FLAT

    // MÉTODOS

    /**
     * @brief Constructor sin parámetros. Por defecto se construye una malla que forma un cubo dibuja con sombreado plano.
     * @return Malla de un cubo que se dibuja con sombreado plano.
    */
    Malla(){
      this->suave=false;
      ply::read("plys/cubo.ply",vertices_ply,caras_ply);

      // Convierto el vector de vértices_ply en otro vector en el que cada componente representa un Punto3D
      for(size_t i=0;i<vertices_ply.size();i+=3){
        Punto3D v(vertices_ply[i],vertices_ply[i+1],vertices_ply[i+2]);
        vertices.push_back(v);
      }

      // Convierto el vector de caras_ply en otro vector en el que cada componente representa un trío de índices (cada índice representará un Punto3D)
      for(size_t i=0;i<caras_ply.size();i+=3){
        Triangulo t(caras_ply[i],caras_ply[i+1],caras_ply[i+2]);
        caras.push_back(t);
      }

      // Calculamos las normales directamente para tenerlas disponibles nada más construir el objeto
      calcular_normales_caras();
      calcular_normales_vertices();

    }

    /**
     * @brief Constructor con parámetros. Construye una malla a partir de un archivo y establece su tipo de sombreado
     * @param nombre_archivo Nombre del archivo que va a representar la malla
     * @param sombreadoSuave TRUE si queremos usar sombreado SMOOTH. FALSE si queremos usar sombreado FLAT
    */
    Malla(const char *nombre_archivo,bool sombreadoSuave){
      this->suave=sombreadoSuave;
      ply::read(nombre_archivo,vertices_ply,caras_ply);
      
      // Convierto el vector de vértices_ply en otro vector en el que cada componente representa un Punto3D
      for(size_t i=0;i<vertices_ply.size();i+=3){
        Punto3D v(vertices_ply[i],vertices_ply[i+1],vertices_ply[i+2]);
        vertices.push_back(v);
      }

      // Convierto el vector de caras_ply en otro vector en el que cada componente representa un trío de índices (cada índice representará un Punto3D)
      for(size_t i=0;i<caras_ply.size();i+=3){
        Triangulo t(caras_ply[i],caras_ply[i+1],caras_ply[i+2]);
        caras.push_back(t);
      }

      // Calculamos las normales directamente para tenerlas disponibles nada más construir el objeto
      calcular_normales_caras();
      calcular_normales_vertices();
    }

    /**
     * @brief Modifica el tipo de sombreado
     * @param s True si se usa sombreado Smooth. False si se usa sombreado Flat
    */
    void setSombreadoSuave(bool s){
      this->suave=s;
    }

    /**
     * @brief Función para calcular las normales de las caras.
    */
    void calcular_normales_caras(){
      
      // Limpio el vector<Triangulo> normales_caras
      this->normales_caras.clear();

      // Almaceno tantos puntos "vacíos" (0,0,0) como caras jhaya (cada punto representará la normal de esa cara)
      for(size_t i = 0;i<caras.size();i++){
        this->normales_caras.push_back(Punto3D());
      }

      // Calculo la normal de cada cara y la almaceno en vector<Punto3D> normales_caras
      for(size_t i = 0; i<caras.size(); i++){
        // Obtengo cada triángulo (cara)
        Triangulo t=caras[i];

        // Obtengo los vértices del triángulo
        Punto3D P0=this->vertices[t.getI0()];
        Punto3D P1=this->vertices[t.getI1()];
        Punto3D P2=this->vertices[t.getI2()];
        
        // Calculo los vectores de los lados del triángulo
        Punto3D V1=(P1-P0);
        Punto3D V2=(P2-P0);

        // Calculo el producto vectorial (V1 x V2) para obtener la normal
        Punto3D normal = V1.productoVectorial(V2);

        // Normalizo la normal para que tenga longitud 1
        normal.normaliza();

        // Almacenamos la normal
        this->normales_caras[i]=normal;
      }
    }

    /**
     * @brief Función para calcular las normales de los vértices.
    */
    void calcular_normales_vertices(){

      // Vaciamos el vector de normales de vértices
      this->normales_vertices.clear();

      // Añadimos puntos vacíos (que representarán las normales)
      for(size_t i = 0;i<this->vertices.size();i++){
        this->normales_vertices.push_back(Punto3D());
      }

      // Calculamos cada normal de cada vértice iterando sobre las caras, por lo que por cada iteración
      // actualizamos la normal de 3 vértices. Cuando el bucle finalice, significará que todos los componentes
      // de vector<Punto3D> normales_vertices tiene sumadas todas las normales de las caras que compone
      for(size_t i=0;i<this->caras.size();++i){

        // Para cada triángulo, obtengo su normal (la normal de la cara)
        Triangulo t = this->caras[i]; // Ejemplo: t(0,1,2) significará que t.v0=0, t.v1=1, t.v2=2
        
        // Obtengo la normal de la cara actual que estamos procesando (ya se calcularon anteriormente)
        Punto3D normal_triangulo= this->normales_caras[i];

        // La normal de esa cara se sumará a las normales de los 3 vértices que componen el triángulo que estamos procesando
        this->normales_vertices[t.getI0()] = this->normales_vertices[t.getI0()] + normal_triangulo;
        this->normales_vertices[t.getI1()] = this->normales_vertices[t.getI1()] + normal_triangulo;
        this->normales_vertices[t.getI2()] = this->normales_vertices[t.getI2()] + normal_triangulo;
      }

      // Normaliza todas las normales de los vértices para que tengan longitud 1
      for(size_t i=0; i<this->normales_vertices.size(); i++){
        this->normales_vertices[i].normaliza();
      }
    }

    /**
     * @brief Función para dibujar en función del sombreado
     * (Podríamos tener las 3 funciones integradas en este método, pero así aumentamos el encapsulamiento)
    */
    void draw(){
      if(this->suave){ // Si el atributo suave==TRUE, se dibujará con sombreado suave
        glShadeModel(GL_SMOOTH);
        this->drawSmooth();
      }else{ // Si el atributo suave==FALSE, se dibujará con sombreado plano
        glShadeModel(GL_FLAT);
        this->drawFlat();
      }
    }

    /**
     * @brief Función para dibujar la malla en modo FLAT.
     * 
     * La iluminación de la cara se calcula con la normal que se le pasa a OpenGL antes del último vértice
     * de la cara. 
     * Por tanto, tenemos que dar la normal de cada cara con glNormal3f(...) antes de que se envíe el último
     * vértice de la cara
    */
    void drawFlat(){
      glBegin(GL_TRIANGLES);
      for(size_t i=0; i<this->caras.size();++i){ // Recorro todas las caras
        // Selecciono cada una de las caras
        Triangulo t = this->caras[i];

        // Doy la normal de la cara actual antes de enviar los vértices
        glNormal3f(this->normales_caras[i].x , this->normales_caras[i].y , this->normales_caras[i].z);
        
        // Envío los 3 vértices (podría hacerlo usando glVertex3f(...) 3 veces)
        for(int j=0;j<3;++j){
          int indice;

          if(j==0){
            indice=t.getI0();
          }else if(j==1){
            indice=t.getI1();
          }else{
            indice=t.getI2();
          }

          // Doy un vértice en cada iteración hasta pasar los 3 Punto3D(x,y,z)
          glVertex3f(this->vertices[indice].x , this->vertices[indice].y , this->vertices[indice].z);
        }
      }
      glEnd();
    }

    /**
     * @brief Función para dibujar la malla en modo SMOOTH
     * Deberemos dar la normal de cada vértice justo antes de enviar el vértice
    */
    void drawSmooth(){

      glBegin(GL_TRIANGLES);
      for(size_t i=0; i<this->caras.size();++i){ // Recorro todas las caras
        Triangulo t = this->caras[i]; // Selecciono cada una de las caras.

        // Mando a dibujar los 3 vértices de cada triángulo a partir de los 3 índices del triángulo actual
        for(int j=0;j<3;++j){
          int indice;

          if(j==0){
            indice=t.getI0();
          }else if(j==1){
            indice=t.getI1();
          }else{
            indice=t.getI2();
          }
          
          // Antes de enviar cada vértice a dibujar, deberemos dar su normal (la del vértice)
          glNormal3f(this->normales_vertices[indice].x , this->normales_vertices[indice].y , this->normales_vertices[indice].z);
          glVertex3f(this->vertices[indice].x , this->vertices[indice].y , this->vertices[indice].z);
        }
      }
      glEnd();
    }
    
};

                    // ////////////////// //
                    // PROGRAMA PRINCIPAL //
                    // ////////////////// //

Ejes ejesCoordenadas;
int modo=GL_FILL;
bool iluminacionActivada=true;

/**
 *  @brief Función para gestionar el Modo de visualización de las figuras
*/
void setModo(int M){
  if(M==1){
    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
  }else if(M==2){
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  }else if(M==3){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  }
}

/**
 *  @brief Función para gestionar la iluminación de las figuras
*/
void setIluminacion(){
  iluminacionActivada = !iluminacionActivada;
  
  if(iluminacionActivada){
    glEnable(GL_LIGHTING);
  }else{
    glDisable(GL_LIGHTING);
  }
}

// PRÁCTICA 2 - Mallas a dibujar

Malla beethoven("plys/beethoven.ply",true);
Malla big_dodge("plys/big_dodge.ply",false);
Malla cubo; // Malla por defecto

// ///////////////////////////////////////////////

/**
 * @brief Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
*/
void Dibuja (void){

  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  float morado[4]={0.8,0,1,1};
  float verde[4]={0,1,0,1};
  float rojo[4]={1,0,0,1};
  float azul[4]={0,0,1,1};
  float negro[4]={0,0,0,1};
  float blanco[4]={1,1,1,1};

  float  color[4] = { 0.8, 0.0, 1, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual
  
  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer
  transformacionVisualizacion ();	// Carga transformacion de visualizacion
  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena
  glDisable(GL_LIGHTING);
  ejesCoordenadas.draw();			// Dibuja los ejes
  if(iluminacionActivada){    // Usamos la variable iluminacionActivada para que el color de los ejes no se vea afectado al alterar la iluminación
    glEnable(GL_LIGHTING);
  }
  
  // glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color); // ¿?¿?¿?¿?¿?¿?

                              // ////////// //
                              // PRACTICA 2 //
                              // ////////// //

  // Dibujo la estatua de Beethoven

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,verde);
  glTranslatef(-10,0,4);
  // beethoven.setSombreadoSuave(false); // Comentar o descomentar esta línea para cambiar el tipo de sombreado
  beethoven.draw();

  // Dibujo un cubo morado

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,morado);
  glTranslatef(10,0,0);
  // cubo.setSombreadoSuave(true); // Comentar o descomentar esta línea para cambiar el tipo de sombreado
  cubo.draw();

  // Dibujo el coche
  
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,rojo);
  glTranslatef(10,0,0);
  // big_dodge.setSombreadoSuave(true); // Comentar o descomentar esta línea para cambiar el tipo de sombreado
  big_dodge.draw();
  
                              // FIN PRÁCTICA 2 

  glPopMatrix ();		// Desapila la transformacion geometrica

  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**
 * @brief Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
*/
void idle (int v){
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}