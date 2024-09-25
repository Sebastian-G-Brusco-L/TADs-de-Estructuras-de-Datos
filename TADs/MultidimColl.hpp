#ifndef _TMTX_T_
#define _TMTX_T_

#include <iostream>
#include "Coll.hpp"

using namespace std;


#include <iostream>
#include "C:\tads\Coll.hpp"



// posible mejor solicion Coll<Coll<T>> elementos;
template <typename T>
struct Mtx
{
   int cantFilas;
   int cantColum;
   Coll<T> elementos; // coll de elementos:  {    1 | 2 | 3  |   4 | 5 | 6   |   7 | 8  | 9   }   matriz 3x3
};
//   1    2    3       <----- 0
//   4    5    6       <----- 1
//   7    8    9       <----- 2

// retorna: Mtx<T> - una matriz vacia, de rows*cols celdas, inicializadas con valores defaultValue
template <typename T>
Mtx<T> mtx(int f, int c, T valorDefault, string tToString(T))
{
   Mtx<T> m;
   m.cantFilas = f;
   m.cantColum = c;
   m.elementos = coll<T>();

   // creo matriz fxc , le agrego el valorDefault y la retorno
   for (int i = 0; i < f * c; i++) // f*c tamanio de la matrix
   {
      collAdd<T>(m.elementos, valorDefault, tToString); // agrego el default a la coll (a todas las filas y col de la matriz)
   }

   return m;
}

// retorna el valor que conciente la matriz en la celda [f,c]
template <typename T>
T mtxGetAt(Mtx<T> m, int f, int c, T tFromString(string))
{
   T t;
   // indice para buscar en la coll,  filas por la cantidad de columnas mas la columna
   int indice = f * m.cantColum + c;                   // el indice de fila se multiplica por la cantidad de columnas en la matriz para "saltar" a la fila correspondiente en la coll. luego se suma el indice de columna para llegar a la posicion exacta dentro de esa fila.
   t = collGetAt<T>(m.elementos, indice, tFromString); // obtengo el elemento en la posicion f*c
   return t;
}

// asigna el valor value en la celda que se ubicada en la interseccion [f,c] de la matriz
template <typename T>
void mtxSetAt(Mtx<T> &m, T t, int f, int c, string tToString(T))
{
   // indice para buscar en la coll  filas por la cantidad de columnas mas la columna
   int indice = f * m.cantColum + c;

   collSetAt<T>(m.elementos, t, indice, tToString); // inserto el elemento t en la posicion f*c
}



// ------------------------

template<typename T>
struct Cube
{
};

template <typename T>
Cube<T> cube(int f,int c,int p,T valorDefault,string tToString(T))
{
   return {};
}

template <typename T>
T cubeGetAt(Cube<T> cu,int f,int c,int p,T tFromString(string))
{
   T t;
   return t;
}

template <typename T>
void cubeSetAt(Cube<T>& cu,T t,int f,int c,int p,string tToString(T))
{
}



#endif
