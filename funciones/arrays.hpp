#ifndef _TARRAYS_T_
#define _TARRAYS_T_

#include <iostream>

template <typename T>
int add(T arr[], int &len, T e)
{
   arr[len] = e;
   len++;

   return len-1;
}

template <typename T>
void insert(T arr[], int &len, T e, int p)
{
   for (int i = len; i > p; i--)
   {
      arr[i] = arr[i - 1];
   }
   arr[p] = e;
   len++;
}

template <typename T>
T remove(T arr[], int &len, int p)
{
   T ret;
   ret = arr[p];
   for (int i = p + 1; i < len; i++)
   {
      arr[i - 1] = arr[i];
   }
   len--;
   return ret;
}


template <typename T, typename K>
int find(T arr[], int len, K k, int cmpTK(T, K))
{
   int pos = -1;
   for (int i = 0; i < len; i++) // recorro la coleccion
   {

      T t = arr[i];          // extrae un elemento del arr, lo convierte al tipo T y lo almacena en la variable t
      int cmp = cmpTK(t, k); // guardo valor de funcion de comparacion
      if (cmp == 0)          // si encontro coincidencia
      {
         pos = i; // se retorna la posición
         break;
      }
   }

   return pos; // no se encontro ninguna coincidencia
}

template <typename T>
int orderedInsert(T arr[], int &len, T e, int cmpTT(T, T)) // arr=[1,2,3,5,6,7,8]   e=4
{

   // si el array esta vacio, simplemente insertamos el elemento en la primera posicion
   if (len == 0)
   {
      arr[0] = e;
      len++;
      return 0; // retorna la posicion 0
   }

   int pos = 0;

   // recorremos el array para encontrar la posicion de insercion
   while (pos < len && cmpTT(e, arr[pos]) >= 0)
   {
      pos++;
   }

   // desplazamos los elementos mayores hacia la derecha para hacer espacio
   for (int i = len; i > pos; i--)
   {
      arr[i] = arr[i - 1];
   }

   // insertamos el elemento en la posicion encontrada
   arr[pos] = e;
   len++;

   return pos;
}

template <typename T>
void sort(T arr[], int len, int cmpTT(T, T))
{

   for (int i = 0; i < len; i++)
   {
      for (int j = 0; j < len - i - 1; j++)
      {
         T t1 = arr[j];
         T t2 = arr[j + 1];

         if (cmpTT(t1, t2) == 1)
         {
            // realiza el intercambio de elementos cuando t1 > t2
            T temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
         }
      }
   }

   return;
}

#endif
