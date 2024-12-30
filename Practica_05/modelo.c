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

Malla beethoven1("plys/beethoven.ply",true,ID_BEETHOVEN1);
Malla beethoven2("plys/beethoven.ply",true,ID_BEETHOVEN2);
Malla beethoven3("plys/beethoven.ply",true,ID_BEETHOVEN3);
// Malla big_dodge("plys/big_dodge.ply",false,ID_BIG_DODGE);


void seleccionarMalla(int c){
  beethoven1.setSeleccionado(false);
  beethoven2.setSeleccionado(false);
  beethoven3.setSeleccionado(false);
  
  switch(c){
    case ID_BEETHOVEN1:
      beethoven1.setSeleccionado(true);
      break;
    case ID_BEETHOVEN2:
      beethoven2.setSeleccionado(true);
      break;
    case ID_BEETHOVEN3:
      beethoven3.setSeleccionado(true);
      break;
    default:
      printf("\nNO HAS SELECCIONADO NINGUNA MALLA\n");
      break;
  }
}

bool mallaSeleccionada(int c){
  switch(c){
    case ID_BEETHOVEN1:
      return beethoven1.getSeleccionado();
      break;
    case ID_BEETHOVEN2:
      return beethoven2.getSeleccionado();
      break;
    case ID_BEETHOVEN3:
      return beethoven3.getSeleccionado();
      break;
    default:
      return false;
      break;
  }
}

// PRÁCTICA 3 - Componentes de mi modelo jerárquico articulado

bool animacionActiva=false; // Se gestiona con A y a
bool otraAnimacion=false;

float VEL_Cilindro=0.01f;   // Se gestiona con T y G
float VEL_Asiento=0.5f;     // Se gestiona con Y y H
float VEL_Respaldo=0.1f;    // Se gestiona con U y J

float posTaburete1[3] = {-15.0f,0.0f,-5.0f};
float posTaburete2[3] = {0.0f,0.0f,-5.0f};
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

Dado dado(4.0f,ID_DADO,1); // Dado "hereda" de Malla

bool dadoEnAnimacion=false;

float carasDado[6][2] = {
  {0.0f,0.0f},
  {90.0f,0.0f},
  {-90.0f,0.0f},
  {0.0f,90.0f},
  {0.0f,-90.0f},
  {180.0f,0.0f}
};

float ajusteAlturaCaras[6] = {0.0f,2.0f,2.0f,0.0f,0.0f,0.0f};
float ajusteProfundidadCaras[6] = {0.0f,-2.0f,2.0f,0.0f,0.0f,0.0f};

float alturaDado=0.0f;
float rotacionDadoX=0.0f;
float rotacionDadoY=0.0f;
float rotacionDadoZ=0.0f;

bool getDadoEnAnimacion(){
  return dadoEnAnimacion;
}

void setDadoEnAnimacion(bool b){
  dadoEnAnimacion=b;
}

void setAlturaDado(float a){
  alturaDado=a;
}

void setRotacionDadoX(float r){
  rotacionDadoX=r;
}

void setRotacionDadoY(float r){
  rotacionDadoY=r;
}

void setRotacionDadoZ(float r){
  rotacionDadoZ=r;
}

void cambiarCaraVisible(int c){
  dado.setCaraVisible(c);
}

// Malla coche1("plys/big_dodge.ply",false,ID_COCHE1); // Reflectividad difusa
// Malla coche2("plys/big_dodge.ply",false,ID_COCHE2); // Reflectividad ambiente
// Malla coche3("plys/big_dodge.ply",false,ID_COCHE3); // Reflectividad especular


// PRÁCTICA 3 - Dos focos de luz distintos

GLfloat posLuz1[4] = {5.0,5.0,10.0,0.0}; // Será el foco de luz por defecto (la que hemos tenido hasta ahora)
GLfloat posLuz2[4] = {-5.0,10.0,-5.0,1.0};

bool luzActiva=true;

// ////////////// //
// PELOTA BOTANDO //
// ////////////// //
typedef struct{
  float y;
  float velY;
  float radio;
  float gravedad;
  float rebote;
} Pelota;

Pelota pelota = {2.0f,0.0f,0.2f,0.01f,0.8f};

bool pelotaEnAnimacion;

void setPelotaEnAnimacion(bool p){
  pelotaEnAnimacion=p;
}

bool getPelotaEnAnimacion(){
  return pelotaEnAnimacion;
}

/**
 * @brief Inicializa el modelo y de las variables globales
*/
void
initModel (){

  // ////////// //
  // Práctica 2 //
  // ////////// //

  actualizarCamara();

  beethoven1.cargarTextura("JPEG/texturaMarmol.jpg");
  beethoven1.calculoCoordenadasTexturaCilindrica();
  beethoven1.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  beethoven1.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  beethoven1.asignarExponenteEspecular(20.0f);

  beethoven2.cargarTextura("JPEG/texturaMadera1.jpg");
  beethoven2.calculoCoordenadasTexturaEsfera();
  beethoven2.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  beethoven2.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  beethoven2.asignarExponenteEspecular(20.0f);

  beethoven3.cargarTextura("JPEG/texturaMetalica1.jpg");
  beethoven3.calculoCoordenadasTexturaPlano();
  beethoven3.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  beethoven3.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  beethoven3.asignarExponenteEspecular(20.0f);

  printf("\nBEETHOVEN 1 tiene ID = %d",beethoven1.getId());
  printf("\nBEETHOVEN 2 tiene ID = %d",beethoven2.getId());
  printf("\nBEETHOVEN 3 tiene ID = %d",beethoven3.getId());

  // big_dodge.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  // big_dodge.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  // big_dodge.asignarExponenteEspecular(49.0f);

  // ////////// //
  // Práctica 4 //
  // ////////// //

  dado.cargarTextura("JPEG/dado.jpg");
  dado.asignarReflectividadAmbiente(0.5f,0.5f,0.5f,0.6f);
  dado.asignarReflectividadEspecular(1.0f,1.0f,1.0f,1.0f);
  dado.asignarExponenteEspecular(49.0f);
  dado.setSombreadoSuave(true);

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

  // //////////////// //
  // PELOTA REBOTANDO //
  // //////////////// //

  pelota.y = 2.0f;
  pelota.velY = 0.0f;
  pelota.radio = 0.2f;
  pelota.gravedad = 0.01f;
  pelota.rebote = 0.8f;
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
  /*unsigned char r = id;
  unsigned char g = 0;
  unsigned char b = 0;

  glColor3ub(r,g,b);
  printf("Asignando color para ID: %d, RGB=(%d,%d,%d)\n",id,r,g,b);*/
  static int ultimoID=-1;
  unsigned char r = id & 0xFF;
  unsigned char g = (id >> 8) & 0xFF;
  glColor3ub(r,g,0);

  if(id!=ultimoID){
    
    ultimoID=id;
  }
  //printf("Asignando color: R=%d, G=%d, B=%d para ID=%d\n",r,g,0,id);
}

// ////////////// //
// PELOTA BOTANDO //
// ////////////// //
float naranja[4]={1.0f,0.5f,0.0f,1.0f};
void dibujarPelota(){
  glPushMatrix();
    glTranslatef(0.0f,pelota.y,0.0f);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,naranja);
    glutSolidSphere(pelota.radio,50,50);
  glPopMatrix();
}

void actualizarPelota(){
  pelota.velY -= pelota.gravedad;
  pelota.y += pelota.velY;

  if(pelota.y <= pelota.radio){
    pelota.y = pelota.radio;
    pelota.velY = -pelota.velY * pelota.rebote;
  }
}

// Creo dibujoEscena() a partir de lo que contenía Dibuja() //
// //////////////////////////////////////////////////////// //

void dibujaEscena() {

    float morado[4]={0.8,0,1,1};
    float verde[4]={0,1,0,1};
    float rojo[4]={1,0,0,1};

    glPushMatrix();
    glClearColor(1.0, 1.0, 1.0, 1.0);
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
    
    // DADO

    int caraVisible = dado.getCaraVisible();
    float ajusteAltura = ajusteAlturaCaras[caraVisible-1];
    float ajusteProfundidad = ajusteProfundidadCaras[caraVisible-1];

    glPushMatrix();
      glTranslatef(4.0f,5.5f + alturaDado + ajusteAltura,-20.0f + ajusteProfundidad);
      glRotatef(rotacionDadoX,1,0,0);
      glRotatef(rotacionDadoY,0,1,0);
      glRotatef(rotacionDadoZ,0,0,1);
      dado.draw();
    glPopMatrix();

    // BEETHOVEN
    glPushMatrix();
      glTranslatef(-10.0f,6.5f,0.0f);
      glScalef(0.25,0.25f,0.25);
      if(getModoSeleccion()){
        colorSeleccion(ID_BEETHOVEN1);
      }
      beethoven1.draw();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0.0f,6.5f,0.0f);
      glScalef(0.25,0.25f,0.25);
      if(getModoSeleccion()){
        colorSeleccion(ID_BEETHOVEN2);
      }
      beethoven2.draw();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(10.0f,6.5f,0.0f);
      glScalef(0.25,0.25f,0.25);
      if(getModoSeleccion()){
        colorSeleccion(ID_BEETHOVEN3);
      }
      beethoven3.draw();
    glPopMatrix();

    // PELOTA

    glPushMatrix();
      glTranslatef(-10.0f,0.0f,-20.0f);
      glScalef(2,2,2);
      glColor3f(1,0,0);
      dibujarPelota();
    glPopMatrix();

    // MESA
    glPushMatrix();
      dibujaMesa();
    glPopMatrix();

    // MESITA
    glPushMatrix();
      glTranslatef(4.0f,0.0f,-20.0f);
      dibujaMesaPequenia();
    glPopMatrix();

    // TEXTO
    glPushMatrix();
      string text1;
      text1="Instrucciones para los TABURETES:";
      glColor3f(1,0,0);
      drawText(text1.data(),text1.size(),20,90);
    glPopMatrix();
    glPushMatrix();
      string text2;
      text2="-TABURETE 1 -> Usamos A,a,Z,z";
      glColor3f(1,1,0);
      drawText(text2.data(),text2.size(),20,75);
    glPopMatrix();
    glPushMatrix();
      string text3;
      text3="-TABURETE 2 -> Usamos S,s,X,x";
      glColor3f(1,1,0);
      drawText(text3.data(),text3.size(),20,60);
    glPopMatrix();
    glPushMatrix();
      string text4;
      text4 ="-TABURETE 3 -> Usamos D,d,C,c";
      glColor3f(1,1,0);
      drawText(text4.data(),text4.size(),20,45);
    glPopMatrix();
    glPushMatrix();
      string text7;
      text7 ="-Tambien puedes rotarlos usando: 1,2,3";
      glColor3f(1,1,0);
      drawText(text7.data(),text7.size(),20,30);
    glPopMatrix();
    glPushMatrix();
      string text8;
      text8 ="o haciendo click con la ruedecilla del raton sobre cada uno";
      glColor3f(1,1,0);
      drawText(text8.data(),text8.size(),20,15);
    glPopMatrix();
    glPushMatrix();
      string text5;
      text5 ="-¿Por que no lanzas el Dado?";
      glColor3f(0,1,1);
      drawText(text5.data(),text5.size(),20,575);
    glPopMatrix();
    glPushMatrix();
      string text6;
      text6 =("-La cara actual es " + std::to_string(dado.getCaraVisible()));
      glColor3f(0,1,1);
      drawText(text6.data(),text6.size(),20,560);
    glPopMatrix();
    glPushMatrix();
      string text9;
      text9 =("-CAMBIA LA CAMARA CON CLICK DERECHO");
      glColor3f(0,1,1);
      drawText(text9.data(),text9.size(),470,560);
    glPopMatrix();

    // Fin
    glPopMatrix();
}


/**
 * @brief Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
*/
void Dibuja (void){
  dibujaEscena();
  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
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

void dibujaMesaPequenia(){
  float colorTabla[4]={0.8f,0.0f,1.0f,1.0f};
  float grisPatas[4]={0.5f,0.5f,0.5f,1.0f};

  glPushMatrix();
    glTranslatef(0.0f,5.0f,0.0f);
    glScalef(6.0f,0.5f,6.0f);
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,colorTabla);
    glutSolidCube(1.0f);
  glPopMatrix();

  for(float x=-2.0f; x<=2.0f; x+=4.0f){
    for(float z=-1.0f;z<=1.0f;z+=2.0f){
      glPushMatrix();
        glTranslatef(x,0.0f,z);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,grisPatas);
        GLUquadric* quad=gluNewQuadric();
        gluCylinder(quad,0.2f,0.2f,5.0f,32,32);
        gluDeleteQuadric(quad);
      glPopMatrix();
    }
  }
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

  if(dadoEnAnimacion){
  
    if(alturaDado<10.0f){
      alturaDado+=0.25f;
    }else if(alturaDado>10.0f){
      alturaDado-=0.15f;
    }else{
      printf("\nYA SE HA LANZADO EL DADO");
      dadoEnAnimacion=false;
      alturaDado=0.0f;
      rotacionDadoX=0.0f;
      rotacionDadoY=0.0f;
      rotacionDadoZ=0.0f;
    }

    if(dadoEnAnimacion && alturaDado > 3.0f){
      rotacionDadoX+=15.0f;
      rotacionDadoY+=20.0f;
      rotacionDadoZ+=10.0f;

      if(rotacionDadoX >= 360.0f){
        rotacionDadoX -= 360.0f;
      }

      if(rotacionDadoY >= 360.0f){
        rotacionDadoY -= 360.0f;
      }

      if(rotacionDadoZ >= 360.0f){
        rotacionDadoZ -= 360.0f;
      }
    }

    if(!dadoEnAnimacion){
      int cara = dado.getCaraVisible();

      rotacionDadoX = carasDado[cara-1][0];
      rotacionDadoY = carasDado[cara-1][1];
      rotacionDadoZ = 0.0f;
    }
    
  }

  if(pelotaEnAnimacion){
    
    

    /*
    pelota.velY -= pelota.gravedad;
    pelota.y += pelota.velY;

    if(pelota.y <= pelota.radio){
      pelota.y = pelota.radio;
      pelota.velY = -pelota.velY * pelota.rebote;
    }*/

/*
    pelota.y=2.0f;
    pelota.velY=0.3f;
    pelota.radio=0.2f;
    pelota.gravedad=0.01f;
    pelota.rebote=0.8f;*/
  
  }
  
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}

void drawText(const char *text, int lenght, int x, int y){
  glMatrixMode(GL_PROJECTION);
  double *matrix = new double[16];
  glGetDoublev(GL_PROJECTION_MATRIX,matrix);
  glLoadIdentity();
  glOrtho(0,800,0,600,-5,5);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x,y);
    for(int i=0;i<lenght;i++){
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)text[i]);
    }
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixd(matrix);
  glMatrixMode(GL_MODELVIEW);
}