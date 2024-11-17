/*	Prácticas de Informática Gráfica
	practicasIG.h
*/
#include  "modelo.h"
#include  "mouse.h"
#include  "entradaTeclado.h"
#include  "visual.h"
#include  "file_ply_stl.h"

// PRÁCTICA 2
#include "Punto3D.h"
#include "Triangulo.h"
#include "Malla.h"

// PRÁCTICA 3
#include  "Respaldo.h"
#include  "Asiento.h"
#include  "Cilindro.h"
#include  "Taburete.h"

// PRÁCTICA 4
#include "lector-jpg.h"
#include "Dado.h"

// PRÁCTICA 5
g++ -g -c -DXWINDOWS  -I/usr/X11R6/include     -c -o practicasIG.o practicasIG.c
In file included from include/practicasIG.h:4,
                 from include/Respaldo.h:10,
                 from include/practicasIG.h:16,
                 from practicasIG.c:5:
include/modelo.h:33:7: error: redefinition of ‘class Objeto3D’
   33 | class Objeto3D{
      |       ^~~~~~~~
In file included from include/practicasIG.h:4,
                 from practicasIG.c:5:
include/modelo.h:33:7: note: previous definition of ‘class Objeto3D’
   33 | class Objeto3D{
      |       ^~~~~~~~
In file included from include/practicasIG.h:4,
                 from include/Cilindro.h:9,
                 from include/practicasIG.h:18,
                 from include/Respaldo.h:10,
                 from include/practicasIG.h:16,
                 from practicasIG.c:5:
include/modelo.h:33:7: error: redefinition of ‘class Objeto3D’
   33 | class Objeto3D{
      |       ^~~~~~~~
In file included from include/practicasIG.h:4,
                 from practicasIG.c:5:
include/modelo.h:33:7: note: previous definition of ‘class Objeto3D’
   33 | class Objeto3D{
      |       ^~~~~~~~
In file included from include/practicasIG.h:4,
                 from include/Taburete.h:10,
                 from include/practicasIG.h:19,
                 from include/Cilindro.h:9,
                 from include/practicasIG.h:18,
                 from include/Respaldo.h:10,
                 from include/practicasIG.h:16,
                 from practicasIG.c:5:
include/modelo.h:33:7: error: redefinition of ‘class Objeto3D’
   33 | class Objeto3D{
      |       ^~~~~~~~
In file included from include/practicasIG.h:4,
                 from practicasIG.c:5:
include/modelo.h:33:7: note: previous definition of ‘class Objeto3D’
   33 | class Objeto3D{
      |       ^~~~~~~~
make: *** [<integrado>: practicasIG.o] Error 1