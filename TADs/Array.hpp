#ifndef _TARR_TAD_
#define _TARR_TAD_

#include <iostream>
#include <stdlib.h>
#include "C:\funciones\arrays.hpp"

using namespace std;

template <typename T>
struct Array
{
   T *e;    // puntero a elemento
   int len; // long del arr
   int cap; // capacidad del arr
};

template <typename T>
Array<T> array()
{
   Array<T> ret;
   ret.len = 0;
   ret.cap = 10;
   ret.e = new T[ret.cap]; // puntero a array con capacidad dinamica

   return ret;
}

template <typename T>
int arrayAdd(Array<T> &a, T t)
{
   if (a.cap == a.len) // el array esta lleno
   {
      // solicito mas espacio en memoria
      int nuevaCap = (a.cap == 0) ? 1 : a.cap * 2; // si el array sigue vacio le asigno 1, sino la multiplico por dos (para q la cap no se inicialice en 0)

      T *nuevoArr = new T[nuevaCap]; // solicito crear un nuevo array con la nueva capacidad

      // copio los elementos del array a al nuevo array
      for (int i = 0; i < a.len; i++)
      {
         nuevoArr[i] = a.e[i];
      }

      // libero la memoria del antiguo array
      delete[] a.e;

      // asigno nuevos valores a la structura
      a.cap = nuevaCap;
      a.e = nuevoArr; // hago que a.e apunte al nuevo arr
   }

   // agrego elemento y no sumo su long ya que la suma add
   add<T>(a.e, a.len, t);

   return a.len - 1;
}

template <typename T>
T *arrayGet(Array<T> a, int p)
{
   return &a.e[p]; // retorno la direccion del elemento del arr
}

template <typename T>
void arraySet(Array<T> &a, int p, T t)
{
   if (p >= 0 && p < a.len)
   {
      a.e[p] = t; // asigno el valor t a la posicion p del array a
   }
}

template <typename T>
void arrayInsert(Array<T> &a, T t, int p) // nose cual es la diff con arraySet
{
   insert<T>(a.e, a.len, t, p); // inserta el elemento en la posicion p, desplaza los elementos a la derecha
}

template <typename T>
int arraySize(Array<T> a)
{
   return a.len;
}

template <typename T>
T arrayRemove(Array<T> &a, int p)
{
   T t = *arrayGet<T>(a, p); // elemento a eliminar

   // remuevo el elemento
   remove<T>(a.e, a.len, p);

   if (a.len < (a.cap / 2)) // si la longitud es menor que el 50% de la capacidad actualizo su capacidad
   {

      T *nuevoArr = new T[a.len]; // solicito espacio para un nuevo array mas chico, con una capacidad igual a su longitud

      // copio los elementos al nuevo array
      for (int i = 0; i < arraySize<T>(a); i++)
      {
         nuevoArr[i] = a.e[i];
      }

      // libero memoria del array viejo y grande
      delete[] a.e;

      // actualizo valores en la estructura
      a.cap = a.len;
      a.e = nuevoArr;
   }

   return t;
}

template <typename T>
void arrayRemoveAll(Array<T> &a)
{
   delete[] a.e;  // libero la memoria de los elementos
   a.e = nullptr; // seteo el puntero a elementos en nullptr para evitar accesos posteriores
   a.len = 0;     // seteo la longitud en 0
   a.cap = 0;     //  seteo la capacidad en 0 si es relevante
}

template <typename T, typename K>
int arrayFind(Array<T> a, K k, int cmpTK(T, K))
{
   return find<T, K>(a.e, a.len, k, cmpTK);
}

template <typename T>
int arrayOrderedInsert(Array<T> &a, T t, int cmpTT(T, T))
{
   return orderedInsert<T>(a.e, a.len, t, cmpTT);
}

template <typename T>
T *arrayDiscover(Array<T> &a, T t, int cmpTT(T, T))
{
   int p = arrayFind<T, T>(a, t, cmpTT);
   if (p < 0) // no encontro, lo agrego
   {
      p = arrayAdd<T>(a, t);
   }
   T *pT = arrayGet<T>(a, p); // obtengo el elemento en esa pos y lo paso por ref
   return pT;
}

template <typename T>
void arraySort(Array<T> &a, int cmpTT(T, T))
{
   int len = arraySize(a);
   for (int i = 0; i < len - 1; i++)
   {
      int minIndex = i;
      for (int j = i + 1; j < len; j++)
      {
         if (cmpTT(*arrayGet<T>(a, j), *arrayGet<T>(a, minIndex)) < 0)
         {
            minIndex = j;
         }
      }
      if (minIndex != i)
      {
         T temp = a.e[i];
         a.e[i] = a.e[minIndex];
         a.e[minIndex] = temp;
      }
   }
}

#endif
