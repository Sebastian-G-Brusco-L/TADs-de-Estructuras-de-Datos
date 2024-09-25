
#ifndef _TMAP_TAD_
#define _TMAP_TAD_

#include <iostream>
#include "C:\tads\Array.hpp"
#include "C:\principal.hpp"

using namespace std;

template <typename K, typename V>
struct Map
{
   Array<K> keys;
   Array<V> values;
   int currentPos = 0;
};

template <typename K, typename V>
Map<K, V> map()
{
   Map<K, V> m;
   m.keys = array<K>();
   m.values = array<V>();
   return m;
}

template <typename K, typename V>
V *mapGet(Map<K, V> m, K k)
{
   int p = arrayFind<K, K>(m.keys, k, cmpTK);

   if (p < 0) // no encontro
   {
      return NULL;
   }
   else
      return arrayGet<V>(m.values, p); // direccion del valor asociado a la key
}

template <typename K, typename V>
V *mapPut(Map<K, V> &m, K k, V v)
{
   // verifico que la key no exista, si existe reemplazo su valor asociado
   int p = arrayFind<K, K>(m.keys, k, cmpTK);
   if (p < 0) // no esta, lo agrego
   {
      p = arrayAdd<K>(m.keys, k);
      arrayAdd<V>(m.values, v);
   }
   else
      arraySet<V>(m.values, p, v); // si ya existe esa key, reemplazo el value

   return arrayGet<V>(m.values, p);
}

template <typename K, typename V>
bool mapContains(Map<K, V> m, K k)
{

   int p = arrayFind<K, K>(m.keys, k, cmpTK);
   bool contains = (p >= 0); // si p>=0 es porque encontro

   return contains;
}

template <typename K, typename V>
V mapRemove(Map<K, V> &m, K k)
{
   int p = arrayFind<K>(m.keys, k, cmpTK); // busco la pos de la key
   V *v = arrayGet<V>(m.values, p);        // obtengo la direcc del valor asociado a la key
   arrayRemove<K>(m.keys, p);              // remuevo la key
   arrayRemove<V>(m.values, p);            // remuevo el value
   return *v;                              // devuelvo el elemento
}

template <typename K, typename V>
void mapRemoveAll(Map<K, V> &m)
{
   arrayRemoveAll<K>(m.keys);
   arrayRemoveAll<V>(m.values);
}

template <typename K, typename V>
int mapSize(Map<K, V> m)
{
   return arraySize<K>(m.keys);
}

template <typename K, typename V>
bool mapHasNext(Map<K, V> m)
{

   return m.currentPos < arraySize<K>(m.keys);
}

template <typename K, typename V>
K mapNextKey(Map<K, V> &m)
{
   K *k;
   if (mapHasNext(m))
   {
      k = arrayGet<K>(m.keys, m.currentPos);
      m.currentPos++;
   }

   return *k;
}

template <typename K, typename V>
V *mapNextValue(Map<K, V> &m)
{
   V *v;
   if (mapHasNext(m))
   {
      v = arrayGet<V>(m.values, m.currentPos);
      m.currentPos++;
   }
   return v;
}

template <typename K, typename V>
void mapReset(Map<K, V> &m)
{
   m.currentPos = 0;
}

template <typename K, typename V>
V *mapDiscover(Map<K, V> &m, K k, V v)
{
   V *ret;
   bool posee = mapContains<K, V>(m, k);
   if (posee == true)
   {
      ret = mapGet<K, V>(m, k);
   }
   else
   {
      ret = mapPut<K, V>(m, k, v);
   }
   return ret;
}

template <typename K, typename V>
void mapSortByKeys(Map<K, V> &m, int cmpKK(K, K))
{
   int n = m.keys.len;
   for (int i = 0; i < n - 1; i++)
   {
      for (int j = 0; j < n - i - 1; j++)
      {
         K *key1 = arrayGet<K>(m.keys, j);
         K *key2 = arrayGet<K>(m.keys, j + 1);
         if (cmpKK(*key1, *key2) > 0)
         {
            // intercambio las claves
            K temp = *key1;
            arraySet<K>(m.keys, j, *key2);
            arraySet<K>(m.keys, j + 1, temp);

            // intercambio los valores correspondientes
            V value1 = *arrayGet<V>(m.values, j);
            V value2 = *arrayGet<V>(m.values, j + 1);
            arraySet<V>(m.values, j, value2);
            arraySet<V>(m.values, j + 1, value1);
         }
      }
   }
}

template <typename K, typename V>
void mapSortByValues(Map<K, V> &m, int cmpVV(V, V))
{
   int n = m.values.len;
   for (int i = 0; i < n - 1; i++)
   {
      for (int j = 0; j < n - i - 1; j++)
      {
         V *value1 = arrayGet<V>(m.values, j);
         V *value2 = arrayGet<V>(m.values, j + 1);
         if (cmpVV(*value1, *value2) > 0)
         {
            // intercambio los valores
            V temp = *value1;
            arraySet<V>(m.values, j, *value2);
            arraySet<V>(m.values, j + 1, temp);

            // intercambio las claves correspondientes
            K key1 = *arrayGet<K>(m.keys, j);
            K key2 = *arrayGet<K>(m.keys, j + 1);
            arraySet<K>(m.keys, j, key2);
            arraySet<K>(m.keys, j + 1, key1);
         }
      }
   }
}

#endif
