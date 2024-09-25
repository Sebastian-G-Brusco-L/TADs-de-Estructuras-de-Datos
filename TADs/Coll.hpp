#ifndef _TCOLL_T_
#define _TCOLL_T_

#include <iostream>
#include "C:\funciones\strings.hpp"
#include "C:\funciones\tokens.hpp"

using namespace std;

template <typename T>
struct Coll
{
   string s;
   char sep;
   int pos = 0;
};

template <typename T>
Coll<T> coll(char sep)
{
   Coll<T> c;
   c.s = "";
   c.sep;

   return c;
}

template <typename T>
Coll<T> coll() // hardcodeo valores iniciales al coll
{
   Coll<T> c;
   c.s = "";
   c.sep = '|';

   return c;
}

template <typename T>
int collSize(Coll<T> c)
{
   return tokenCount(c.s, c.sep);
}

template <typename T>
void collRemoveAll(Coll<T> &c)
{
   c.s = "";
}

template <typename T>
void collRemoveAt(Coll<T> &c, int p)
{
   removeTokenAt(c.s, c.sep, p);
}

template <typename T>
int collAdd(Coll<T> &c, T t, string tToString(T)) // tToString(T) la funcion de conversion de cualquier tipo de dato a string
{
   addToken(c.s, c.sep, tToString(t)); // agrego token al final
   return tokenCount(c.s, c.sep) - 1;
}

template <typename T>
void collSetAt(Coll<T> &c, T t, int p, string tToString(T)) // T t es el elemento a remplazar a la coleccion
{
   setTokenAt(c.s, c.sep, tToString(t), p); // remplazo un token a la collecion y lo paso a string
}

template <typename T>
T collGetAt(Coll<T> c, int p, T tFromString(string))
{
   T t; // declaro una variable t de tipo template que puede contener cualquier tipo de dato
   t = tFromString(getTokenAt(c.s, c.sep, p));
   return t;
}

template <typename T, typename K>
int collFind(Coll<T> c, K k, int cmpTK(T, K), T tFromString(string)) // tFromString, funcion de conversion a t, depende de que funcion de conversion use en su invocacion
{
   int pos = -1;
   for (int i = 0; i < collSize(c); i++) // recorro la coleccion
   {

      T t = tFromString(getTokenAt(c.s, c.sep, i)); // extrae un elemento de la colección c, lo convierte al tipo T utilizando la función tFromString y lo almacena en la variable t
      int cmp = cmpTK(t, k);                        // guardo valor de funcion de comparacion
      if (cmp == 0)                                 // si encontro coincidencia
      {
         pos = i; // se retorna la posición
         break;
      }
   }

   return pos; // No se encontró ninguna coincidencia
}

template <typename T>
void collSort(Coll<T> &c, int cmpTT(T, T), T tFromString(string), string tToString(T)) // Seba|Pepe|Jorgelin|Blanco|pepito|grilo
{

   int cmp;
   for (int i = 0; i < collSize(c); i++)
   {

      for (int j = 0; j < collSize(c) - i - 1; j++) // -i-1  en cada iteración del bucle externo, el elemento más grande se coloca en la posición correcta al final del arreglo. Por lo tanto, no es necesario iterar hasta el final en el bucle interno.
      {
         // obtengo el token en la pos i, lo almaceno en un tipo T y tFromString para convertir la cadena obtenida  al tipo T.
         T t1 = tFromString(getTokenAt(c.s, c.sep, j));     // seba
         T t2 = tFromString(getTokenAt(c.s, c.sep, j + 1)); // pepe

         if (cmpTT(t1, t2) == 1) // t1>t2
         {
            // muevo entre si los elementos adjacentes
            setTokenAt(c.s, c.sep, tToString(t2), j);     // pepe|seba|blanco|jorgelin
            setTokenAt(c.s, c.sep, tToString(t1), j + 1); // pepe|jorgelin|blanco|seba
         }
      }
   }
   
}

template <typename T>
bool collHasNext(Coll<T> c)
{
   return collSize(c) > 0; // si el tamanio de c es mayor a cero true, es decir que puede iterar, de lo contrario, false
}

template <typename T>
T collNext(Coll<T> &c, T tFromString(string)) // en cada llamada de la funcion debo retornar el elemento siguiente
{
   T t;
   // static int pos = c.pos; creo variable statica para que conserve su valor en cada llamada, otra posible solucion
   if (collHasNext(c))
   {
      t = tFromString(getTokenAt(c.s, c.sep, c.pos)); // guardo el token en t
      c.pos++;                                        // aumento el iterador del col
   }

   return t;
}

template <typename T>
T collNext(Coll<T> &c, bool &endOfColl, T tFromString(string))
{
   T t;
   // static int pos = c.pos; creo variable statica para que conserve su valor en cada llamada, otra posible solucion
   if (!endOfColl) // lo mismo pero utilizando una variable bool externa
   {
      t = tFromString(getTokenAt(c.s, c.sep, c.pos)); // guardo el token en t
      c.pos++;                                        // aumento el iterador del col
   }
   return t;
}

template <typename T>
void collReset(Coll<T> &c)
{
   c.pos = 0;
}

template<typename T>
string collToString(Coll<T> c)
{
	return c.sep+c.s;
}

template<typename T>
Coll<T> collFromString(string s)
{
	Coll<T> c;
	c.sep=s[0];
	c.s=substring(s,1);
	return c;
}


#endif
