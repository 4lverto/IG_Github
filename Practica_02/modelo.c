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
                // PRACTICA 1 //
                // ////////// //
/*
                    // /////////////// //
                    // "SUBCLASE" CUBO //
                    // /////////////// //
class Cubo:Objeto3D { 
  public: 
    float lado = 30;

    Cubo(float l){
      this->lado=l;
    }

  // Dibuja el Cubo usando primitivas

  // void draw(){
  //   glBegin(GL_QUADS);{
  //    glutSolidCube(this->lado);
  //   }
  //   glEnd();    
  // }

  // Dibuja el cubo manualmente

  void draw(){
    
    float mitad = this->lado / 2;
    glBegin( GL_QUADS ); // Comienza la definición de un cuadrado
    {
      // Cara superior
      glNormal3f( 0.0, 1.0, 0.0 );
      glVertex3f( -mitad, mitad, mitad ); 
      glVertex3f( mitad, mitad, mitad );
      glVertex3f( mitad, mitad, -mitad );
      glVertex3f( -mitad, mitad, -mitad );
      
      // Cara inferior
      glNormal3f( 0.0, -1.0, 0.0 ); 
      glVertex3f( -mitad, -mitad, -mitad );
      glVertex3f( mitad, -mitad, -mitad );
      glVertex3f( mitad, -mitad, mitad );
      glVertex3f( -mitad, -mitad, mitad );

      // Cara derecha
      glNormal3f( 1.0, 0.0, 0.0 ); 
      glVertex3f( mitad, mitad, mitad );
      glVertex3f( mitad, mitad, -mitad );
      glVertex3f( mitad, -mitad, -mitad );
      glVertex3f( mitad, -mitad, mitad );

      // Cara izquierda
      glNormal3f( -1.0, 0.0, 0.0 ); 
      glVertex3f( -mitad, mitad, mitad );
      glVertex3f( -mitad, mitad, -mitad );
      glVertex3f( -mitad, -mitad, -mitad );
      glVertex3f( -mitad, -mitad, mitad );

      // Cara frontal
      glNormal3f( 0.0, 0.0, 1.0 ); 
      glVertex3f( -mitad, mitad, mitad );
      glVertex3f( -mitad, -mitad, mitad );
      glVertex3f( mitad, -mitad, mitad );
      glVertex3f( mitad, mitad, mitad );
      
      // Cara trasera
      glNormal3f( 0.0, 0.0, -1.0 ); 
      glVertex3f( -mitad, -mitad, -mitad );
      glVertex3f( mitad, -mitad, -mitad );
      glVertex3f( mitad, mitad, -mitad );
      glVertex3f( -mitad, mitad, -mitad );
    }
    glEnd();
  }

};

                      // /////////////////// //
                      // "SUBCLASE" PIRÁMIDE //
                      // /////////////////// //
class Piramide:Objeto3D { 
  public: 
    float lado = 2;
    float alto = 4;

    Piramide(float l,float a){
      this->lado=l;
      this->alto=a;
    }

  // Dibuja la Pirámide (Primitiva GLUT)
  
  // void draw() {
  //     glutSolidCone(lado,alto,4,1);
  // }

  // Dibuja la Pirámide (manualmente)
  void draw(){

    float mitad=lado/2;

    // Coordenadas del vértice superior de la pirámide
    float vx = 0;
    float vy = alto;
    float vz = 0;

    // Dibujamos la base de la pirámide
    glBegin(GL_QUADS);{
      glNormal3f(0,-1,0);
      glVertex3f(-mitad,0,-mitad);
      glVertex3f(mitad,0,-mitad);
      glVertex3f(mitad,0,mitad);
      glVertex3f(-mitad,0,mitad);
    }
    glEnd();

    glBegin(GL_TRIANGLES);{

      // Cara frontal
      glNormal3f(0,0.5,0.5);
      glVertex3f(-mitad,0,mitad);
      glVertex3f(mitad,0,mitad);
      glVertex3f(vx,vy,vz); // "Punta" 
    
      // Cara derecha
      glNormal3f(0.5,0.5,0);
      glVertex3f(mitad,0,mitad);
      glVertex3f(-mitad,0,-mitad);
      glVertex3f(vx,vy,vz); // "Punta"

      // Cara trasera
      glNormal3f(0,0.5,-0.5);
      glVertex3f(mitad,0,-mitad);
      glVertex3f(-mitad,0,-mitad);
      glVertex3f(vx,vy,vz); // "Punta"

      // Cara izquierda
      glNormal3f(-0.5,0.5,0);
      glVertex3f(-mitad,0,-mitad);
      glVertex3f(-mitad,0,mitad);
      glVertex3f(vx,vy,vz); // "Punta"
    }
    glEnd();


  }

} ;
*/


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
  int getV0(){
    return this->v0;
  }

  /**
   * @brief Obtiene el índice del segundo vértice
   * @return Índice del segundo vértice
  */
  int getV1(){
    return this->v1;
  }

  /**
   * @brief Obtiene el índice del tercer vértice
   * @return Índice del tercer vértice
  */
  int getV2(){
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
    vector<Triangulo> caras; // Contenedor de Triangulos. Contendrá todos los índices de los triángulos

    bool suave; // Será TRUE cuando la Malla se tenga que dibujar con sombreado SMOOTH y FALSE cuando la malla tenga un sombreado FLAT

    /**
     * @brief Constructor con parámetros. Construye un
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
      this->normales_caras.resize(this->caras.size());
/*
      this->normales_caras.clear();

      for(size_t i = 0;i<caras.size();i++){
        this->normales_caras.push_back(Punto3D());
      }*/

      for(size_t i = 0; i<caras.size(); i++){
        Triangulo t=caras[i];
        Punto3D P0=this->vertices[t.getV0()];
        Punto3D P1=this->vertices[t.getV1()];
        Punto3D P2=this->vertices[t.getV2()];
        
        Punto3D V1=(P1-P0);
        Punto3D V2=(P2-P0);

        Punto3D normal = V1.productoVectorial(V2);
        normal.normaliza();

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

      for(size_t i=0;i<this->caras.size();++i){
        Triangulo t = this->caras[i];
        Punto3D normal= this->normales_caras[i];

        this->normales_vertices[t.getV0()] = this->normales_vertices[t.getV0()] + normal;
        this->normales_vertices[t.getV1()] = this->normales_vertices[t.getV1()] + normal;
        this->normales_vertices[t.getV2()] = this->normales_vertices[t.getV2()] + normal;
      }

      for(size_t i=0; i<this->normales_vertices.size(); i++){
        this->normales_vertices[i].normaliza();
      }
    }

    /**
     * @brief Función para dibujar en función del sombreado
    */
    void draw(){
      if(this->suave){
        this->drawSmooth();
      }else{
        this->drawFlat();
      }
    }
    /**
     * @brief Función para dibujar la malla en modo SMOOTH
    */
    void drawSmooth(){

      glBegin(GL_TRIANGLES);
      for(size_t i=0; i<this->caras.size();++i){
        Triangulo t = this->caras[i];

        for(int j=0;j<3;++j){
          int indice;

          if(j==0){
            indice=t.getV0();
          }else if(j==1){
            indice=t.getV1();
          }else{
            indice=t.getV2();
          }

          glNormal3f(this->normales_vertices[indice].x , this->normales_vertices[indice].y , this->normales_vertices[indice].z);
          glVertex3f(this->vertices[indice].x , this->vertices[indice].y , this->vertices[indice].z);
        }
      }
      glEnd();
    }

    /**
     * @brief Función para dibujar la malla en modo SMOOTH
    */
    void drawFlat(){
      glBegin(GL_TRIANGLES);
      for(size_t i=0; i<this->caras.size();++i){
        Triangulo t = this->caras[i];

        glNormal3f(this->normales_vertices[i].x , this->normales_vertices[i].y , this->normales_vertices[i].z);
        for(int j=0;j<3;++j){
          int indice;

          if(j==0){
            indice=t.getV0();
          }else if(j==1){
            indice=t.getV1();
          }else{
            indice=t.getV2();
          }

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

// PRÁCTICA 1

/*
Cubo miCubo(3);
Piramide miPiramide(2,4);
*/

// PRÁCTICA 2

Malla beethoven("plys/beethoven.ply",false);
Malla big_dodge("plys/big_dodge.ply",true);


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

  ejesCoordenadas.draw();			// Dibuja los ejes

  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

                              // ////////// //
                              // PRACTICA 1 //
                              // ////////// //
  
  /*
  // DIBUJO EL CUBO

  float  color2[4] = { 1.0, 1.0, 0.0}; // amarillo
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,color2);
  glTranslatef(5,1,2);

  miCubo.draw();

  // DIBUJO LA PIRÁMIDE

  float  color3[4] = { 0.0, 4.0, 0.0}; // verde
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,color3);
  glTranslatef(5,-1,1);
  //glRotatef(-90,1,0,0);

  miPiramide.draw();

                              // FIN PRÁCTICA 1
  */

                              // ////////// //
                              // PRACTICA 2 //
                              // ////////// //

  // Dibujo la estatua de Beethoven
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,verde);
  glTranslatef(-10,0,4);
  glShadeModel(GL_SMOOTH);
  beethoven.draw();

  // Dibujo el coche
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,rojo);
  glTranslatef(20,0,4);
  glShadeModel(GL_FLAT);
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