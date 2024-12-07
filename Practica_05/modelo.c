#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "include/practicasIG.h"
#include <vector>
#include <stdbool.h>

using namespace std;

// PRÁCTICA 2 - Mallas con PLYs

// Malla beethoven("plys/beethoven.ply",true,ID_BEETHOVEN);
// Malla big_dodge("plys/big_dodge.ply",false,ID_BIG_DODGE);

// PRÁCTICA 3 - Componentes de mi modelo jerárquico articulado

bool animacionActiva=false; // Se gestiona con A y a
float VEL_Cilindro=0.01f;   // Se gestiona con T y G
float VEL_Asiento=0.5f;     // Se gestiona con Y y H
float VEL_Respaldo=0.1f;    // Se gestiona con U y J

float posTaburete1[3] = {0.0f,0.0f,0.0f};
float posTaburete2[3] = {-5.0f,0.0f,-5.0f};
float posTaburete3[3] = {3.0f,0.0f,10.0f};

float angulo1=0.0f;
float angulo2=0.0f;
float angulo3=0.0f;

void girar(int ntaburete){
  switch(ntaburete){
    case 1:
      angulo1+=90.0f;
      break;
    
    case 2:
      angulo2+=90.0f;
      break;
    
    case 3:
      angulo3+=90.0f;
      break;
    
    default:
      printf("\nNingún objeto está girando");
      break;
  }
}

void moverse(int ntaburete,char coordenada,float cantidad){
  
  if(coordenada=='x'){
    switch(ntaburete){
      case 1:
        if(comprobarTopeX(ntaburete,cantidad)){
          posTaburete1[0]+=cantidad;
        }else{
          posTaburete1[0]+=(cantidad*-1);
        }
        break;
      
      case 2:
        if(comprobarTopeX(ntaburete,cantidad)){
          posTaburete2[0]+=cantidad;
        }else{
          posTaburete2[0]+=(cantidad*-1);
        }
        break;
    
      case 3:
        if(comprobarTopeX(ntaburete,cantidad)){
          posTaburete3[0]+=cantidad;
        }else{
          posTaburete3[0]+=(cantidad*-1);
        }
        break;

      default:
        printf("\nNo estás seleccionando un taburete válido");
    }
  }else{
    switch(ntaburete){
      case 1:
        if(comprobarTopeZ(ntaburete,cantidad)){
          posTaburete1[2]+=cantidad;
        }else{
          posTaburete1[2]+=(cantidad*-1);
        }
        break;
      
      case 2:
        if(comprobarTopeZ(ntaburete,cantidad)){
          posTaburete2[2]+=cantidad;
        }else{
          posTaburete2[0]+=(cantidad*-1);
        }
        break;
    
      case 3:
        if(comprobarTopeZ(ntaburete,cantidad)){
          posTaburete3[2]+=cantidad;
        }else{
          posTaburete3[0]+=(cantidad*-1);
        }
        break;

      default:
        printf("\nNo se está moviendo el taburete");
    }

  }
}

bool comprobarTopeX(int ntaburete,float cantidad){
  bool valido;
  switch(ntaburete){
    case 1:
      if(posTaburete1[0]+cantidad<30 && posTaburete1[0]+cantidad>-30){
        valido=true;
      }else{
        valido=false;
      }
      break;
    case 2:
      if(posTaburete2[0]+cantidad<30 && posTaburete2[0]+cantidad>-30){
        valido=true;
      }else{
        valido=false;
      }
      break;
    case 3:
      if(posTaburete3[0]+cantidad<30 && posTaburete3[0]+cantidad>-30){
        valido=true;
      }else{
        valido=false;
      }
      break;
    default:
      printf("\nLlamada a comprobarTopeX incorrecta");
  }

  return valido;
}

bool comprobarTopeZ(int ntaburete, float cantidad)
{
    bool valido;
    switch (ntaburete)
    {
    case 1:
      if(posTaburete1[2]+cantidad<30 && posTaburete1[2]+cantidad>-30){
        valido=true;
      }else{
        valido=false;
      }
      break;
    case 2:
      if(posTaburete2[2]+cantidad<30 && posTaburete2[2]+cantidad>-30){
        valido=true;
      }else{
        valido=false;
      }
      break;
    case 3:
      if(posTaburete3[2]+cantidad<30 && posTaburete3[2]+cantidad>-30){
        valido=true;
      }else{
        valido=false;
      }
      break;
    default:
      printf("\nLlamada a comprobarTopeX incorrecta");
  }

  return valido;
}

// PRÁCTICA 4 - Mallas a dibujar y Dado

// Dado dado(4.0f,ID_DADO); // Dado "hereda" de Malla
// Malla coche1("plys/big_dodge.ply",false,ID_COCHE1); // Reflectividad difusa
// Malla coche2("plys/big_dodge.ply",false,ID_COCHE2); // Reflectividad ambiente
// Malla coche3("plys/big_dodge.ply",false,ID_COCHE3); // Reflectividad especular

// PRÁCTICA 4 - Dos focos de luz distintos

GLfloat posLuz1[4] = {5.0,5.0,10.0,0.0}; // Será el foco de luz por defecto (la que hemos tenido hasta ahora)
GLfloat posLuz2[4] = {-5.0,10.0,-5.0,1.0};

bool luzActiva=true;

/**
 * @brief Inicializa el modelo y de las variables globales
*/
void
initModel (){

  // ////////// //
  // Práctica 2 //
  // ////////// //

  // beethoven.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  // beethoven.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  // beethoven.asignarExponenteEspecular(49.0f);

  // big_dodge.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  // big_dodge.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  // big_dodge.asignarExponenteEspecular(49.0f);

  // ////////// //
  // Práctica 4 //
  // ////////// //

  // dado.cargarTextura("JPEG/dado.jpg");
  // dado.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  // dado.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  // dado.asignarExponenteEspecular(49.0f);
  // dado.setSombreadoSuave(true);

  // coche1.cargarTextura("JPEG/texturaMarmol.jpg");
  // coche1.calculoCoordenadasTexturaCilindrica();
  // coche1.configuracionMaterial1();
  // coche1.setSombreadoSuave(true);

  // coche2.cargarTextura("JPEG/texturaMarmol.jpg");
  // coche2.calculoCoordenadasTexturaCilindrica();
  // coche2.configuracionMaterial2();
  // coche2.setSombreadoSuave(true);

  // coche3.configuracionMaterial3();
  // coche3.setSombreadoSuave(true);
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

// //////////
// PRÁCTICA 4 - Alternar entre los focos de luz definidos. Tecla W
// //////////

void establecerLuzActiva(){

  luzActiva = !luzActiva;

  if(luzActiva){
    glLightfv(GL_LIGHT0,GL_POSITION,posLuz1);
  }else{
    glLightfv(GL_LIGHT0,GL_POSITION,posLuz2);
  }

  glutPostRedisplay();
}

                                // ////////// //
                                // PRÁCTICA 5 //
                                // ////////// //

bool modoSeleccion=false;

bool getModoSeleccion(){
  return modoSeleccion;
}

void setModoSeleccion(bool s){
  modoSeleccion=s;
}

// Implemento colorSeleccion //
// ///////////////////////// //

void colorSeleccion(int id/*, int componente*/){
  static int ultimoID=-1;
  unsigned char r = id & 0xFF;
  unsigned char g = (id >> 10) & 0xFF;
  glColor3ub(r,g,0);

  if(id!=ultimoID){
    // printf("Asignando color: R=%d, G=%d, B=%d para ID=%d\n",r,g,0,id);
    ultimoID=id;
  }
}

// Creo dibujoEscena() a partir de lo que contenía Dibuja() //
// //////////////////////////////////////////////////////// //

void dibujaEscena() {

    float morado[4]={0.8,0,1,1};
    float verde[4]={0,1,0,1};
    float rojo[4]={1,0,0,1};

    glPushMatrix();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // Configura la transformación de visualización
    transformacionVisualizacion();

    // Dibujar los ejes (sin iluminación)
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING);
    ejesCoordenadas.draw();
    glPopAttrib();

    // Taburete 1
    glPushMatrix();
    glTranslatef(posTaburete1[0],posTaburete1[1],posTaburete1[2]);
    glRotatef(angulo1,0,1,0);
    if(getModoSeleccion()){
      colorSeleccion(ID_TABURETE1);
    }
    dibujaTaburete(ID_TABURETE1);
    glPopMatrix();

    // Taburete 2
    glPushMatrix();
    glTranslatef(posTaburete2[0],posTaburete2[1],posTaburete2[2]);
    glRotatef(angulo2,0,1,0);
    if(getModoSeleccion()){
      colorSeleccion(ID_TABURETE2);
    }
    dibujaTaburete(ID_TABURETE2);
    glPopMatrix();

    // Taburete 3
    glPushMatrix();
    glTranslatef(posTaburete3[0],posTaburete3[1],posTaburete3[2]);
    glRotatef(angulo3,0,1,0);
    if(getModoSeleccion()){
      colorSeleccion(ID_TABURETE3);
    }
    dibujaTaburete(ID_TABURETE3);
    glPopMatrix();

    // MESA
    dibujaMesa();

    glPopMatrix();
}


/**
 * @brief Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
*/
void Dibuja (void){
  dibujaEscena();
  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**
 * @brief Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.
*/
void idle (int v){

  // Actualización de la velocidad de escalado de altura del cilindro
  if(animacionActiva){
    if(alturaCilindro>=2.0f || alturaCilindro<=0.5f){
      VEL_Cilindro = -VEL_Cilindro;
    }

    alturaCilindro += VEL_Cilindro;

    // Actualización de la velocidad de rotación del asiento

    rotacionAsiento += VEL_Asiento;

    if(rotacionAsiento >= 360.0f || rotacionAsiento <= -360.0f){
      rotacionAsiento=0.0f;  
    }

    // Actualización de la velocidad de rotación (inclinación) del respaldo
    
    if(inclinacionRespaldo >= 0.0f || inclinacionRespaldo <= -25.0f){
      VEL_Respaldo = -VEL_Respaldo;
    }

    inclinacionRespaldo += VEL_Respaldo; 
  }
  
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}

void dibujaMesa(){
  float marronTabla[4]={0.55f,0.27f,0.07f,1.0f};
  float grisPatas[4]={0.5f,0.5f,0.5f,1.0f};

  glPushMatrix();
    glTranslatef(0.0f,5.0f,0.0f);
    glScalef(30.0f,0.5f,6.0f);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,marronTabla);
    glutSolidCube(1.0f);
  glPopMatrix();

  for(float x=-10.0f; x<=10.0f; x+=20.0f){
    for(float z=-2.5f;z<=2.5f;z+=5.0f){
      glPushMatrix();
        glTranslatef(x,0.0f,z);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,grisPatas);
        GLUquadric* quad=gluNewQuadric();
        gluCylinder(quad,0.3f,0.3f,5.0f,32,32);
        gluDeleteQuadric(quad);
      glPopMatrix();
    }
  }
}