#ifndef _PLY_H
#define _PLY_H

#include <vector>

namespace ply{

// **********************************************************************
// **
// ** ply::read 
// **
// **  lee un archivo ply y lo carga en 'vertices' y 'caras'
// **
// **   - 'nombre_archivo' nombre del archivo (se le añade .ply si no 
// **     acaba en .ply)
// **   - si hay un error, aborta
// **   - elimina cualquier contenido previo en los 
// **     vectores 'vertices' y 'caras'
// **   - lee el archivo .ply y lo carga en 'vertices' y 'faces'
// **   - solo admite plys con triángulos, 
// **   - no lee colores, coordenadas de textura, ni normales.
// **
// *********************************************************************

  // const char *nombre_archivo_pse --> Nombre de archivo (ENTRADA)
  // std::vector <float>&vertices --> Vector de coordenadas de vertices (SALIDA)
  // std::vector < int >&caras --> Vector de triángulos (índices) (SALIDA)
  void read (const char *nombre_archivo_pse, std::vector < float >&vertices, std::vector < int >&caras);

// **********************************************************************
// **
// ** ply::read_vertices 
// **
// **  lee los vértices de un archivo ply y los carga en 'vertices' 
// **
// **   - 'nombre_archivo' nombre del archivo (se le añade .ply si no 
// **     acaba en .ply)
// **   - si hay un error, aborta
// **   - elimina cualquier contenido previo en el 
// **     vector 'vertices' 
// **   - lee el archivo .ply y carga los vértices en 'vertices'
// **   - no lee colores, caras, coordenadas de textura, ni normales.
// **   - se ignora la información de caras
// **
// *********************************************************************

// *const char *nombre_archivo_pse --> Nombre del archivo (ENTRADA)
// std::vector<float> &vertices --> Vector de coordenadas de vertices (SALIDA)
  void read_vertices (const char *nombre_archivo_pse, std::vector < float >&vertices);

};				// fin namespace ply

#endif // _PLY_H
