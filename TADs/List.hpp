#ifndef _TLIST_TAD_
#define _TLIST_TAD_

#include <iostream>
#include "C:\funciones\lists.hpp"

using namespace std;

template <typename T>
struct List
{
   Node<T> *head;
   Node<T> *tail;
   int count;
};

template <typename T>
List<T> list()
{
   List<T> newList;
   newList.head = nullptr;
   newList.tail = nullptr;
   newList.count = 0;
   return newList;
}

template <typename T>
T *listAdd(List<T> &lst, T e)
{
   Node<T> *newNode = new Node<T>();
   newNode->info = e;
   newNode->sig = nullptr;

   if (lst.head == nullptr)
   {
      // si la lista esta vacia, el nuevo nodo es tanto la cabeza como la cola
      lst.head = newNode;
      lst.tail = newNode;
   }
   else
   {
      // agrego el nuevo nodo al final de la lista y actualizo la cola
      lst.tail->sig = newNode;
      lst.tail = newNode;
   }

   lst.count++; 

   return &(newNode->info);
}

template <typename T>
T *listAddFirst(List<T> &lst, T e)
{
   Node<T> *newNode = new Node<T>();
   newNode->info = e;
   newNode->sig = lst.head;

   lst.head = newNode;

   if (lst.tail == nullptr)
   {
      // si la lista estaba vacia, el nuevo nodo tamb es la cola
      lst.tail = newNode;
   }

   lst.count++; 

   return &(newNode->info);
}

template <typename T, typename K>
T listRemove(List<T> &lst, K k, int cmpTK(T, K))
{
   Node<T> *current = lst.head;
   Node<T> *previous = nullptr;

   while (current != nullptr)
   {
      if (cmpTK(current->info, k) == 0)
      {
         if (previous == nullptr)
         {
            // elimino el primer nodo
            lst.head = current->sig;
            if (lst.head == nullptr)
            {
               // si solo habia un elemento, actualizo la cola
               lst.tail = nullptr;
            }
         }
         else
         {
            previous->sig = current->sig;
            if (current == lst.tail)
            {
               // si el nodo a eliminar era la cola, actualizo la cola
               lst.tail = previous;
            }
         }

         T removedValue = current->info;
         delete current;

         lst.count--; 
         return removedValue;
      }

      previous = current;
      current = current->sig;
   }

   // devuelvo un valor predeterminado
   return T();
}

template <typename T>
T listRemoveFirst(List<T> &lst)
{
   if (lst.head == nullptr)
   {
      // lista vacia, no hay nada que eliminar
      return T();
   }

   Node<T> *firstNode = lst.head;
   T removedValue = firstNode->info;

   lst.head = lst.head->sig;

   delete firstNode;

   lst.count--; 

   if (lst.head == nullptr)
   {
      // si la lista  esta vacia, tamb actualiza la cola
      lst.tail = nullptr;
   }

   return removedValue;
}

template <typename T, typename K>
T *listFind(List<T> lst, K k, int cmpTK(T, K))
{
   Node<T> *current = lst.head;

   while (current != nullptr)
   {
      if (cmpTK(current->info, k) == 0)
      {
         return &(current->info);
      }
      current = current->sig;
   }

   return nullptr;
}

template <typename T>
bool listIsEmpty(List<T> lst)
{
   return lst.count == 0;
}

template <typename T>
int listSize(List<T> lst)
{
   return lst.count;
}

template <typename T>
void listFree(List<T> &lst)
{
   Node<T> *current = lst.head;

   while (current != nullptr)
   {
      Node<T> *temp = current;
      current = current->sig;
      delete temp;
   }

   lst.head = nullptr;
   lst.tail = nullptr;
   lst.count = 0; // reincio el contador
}

template <typename T>
T *listDiscover(List<T> &lst, T t, int cmpTT)
{
   // busco si el elemento ya esta en la lista
   Node<T> *foundNode = find(lst.head, t, cmpTT);

   if (foundNode != nullptr)
   {
      // el elemento ya existe en la lista, se devuelve la direcc de memoria de ese elemento
      return &(foundNode->info);
   }
   else
   {
      // el elemento no esta en la lista, se agrega al final de la lista
      Node<T> *newNode = enqueue(lst.head, lst.tail, t);

      // retorno la direccion de memoria del elemento agregado
      return &(newNode->info);
   }
}

template <typename T>
T *listOrderedInsert(List<T> &lst, T t, int cmpTT(T, T))
{
   // si la lista está vacia o el nuevo elemento es menor o igual al primer elemento,
   // insertamos el nuevo elemento al principio de la lista.
   if (isEmpty(lst.head) || cmpTT(t, lst.head->info) <= 0)
   {
      Node<T> *newNode = addFirst(lst.head, t);
      return &(newNode->info);
   }
   else
   {
      Node<T> *current = lst.head;
      Node<T> *previous = nullptr;

      while (current != nullptr && cmpTT(t, current->info) > 0)
      {
         previous = current;
         current = current->sig;
      }

      // creamos un nuevo nodo con el elemento t
      Node<T> *newNode = new Node<T>;
      newNode->info = t;

      // insertamos el nuevo nodo entre previous y current
      previous->sig = newNode;
      newNode->sig = current;

      // retornamos la direcc de memoria del elemento insertado
      return &(newNode->info);
   }
}

template <typename T>
void listSort(List<T> &lst, int cmpTT(T, T))
{
   // si la lista esta vacia o tiene un solo elemento, ya esta ordenada
   if (isEmpty(lst.head) || lst.head->sig == nullptr)
   {
      return;
   }

   Node<T> *current = lst.head;
   Node<T> *index = nullptr;
   T temp;

   while (current != nullptr)
   {
      index = current->sig;

      while (index != nullptr)
      {
         if (cmpTT(current->info, index->info) > 0)
         {
            // intercambio los valores de current y index
            temp = current->info;
            current->info = index->info;
            index->info = temp;
         }

         index = index->sig;
      }

      current = current->sig;
   }
}

template <typename T>
void listReset(List<T> &lst)
{
   lst.count = 0;
}

template <typename T>
bool listHasNext(List<T> lst)
{
   return lst.count > 0;
}

template <typename T>
T *listNext(List<T> &lst)
{
    if (lst.count <= 0 || lst.head == nullptr)
   {
      // no quedan elementos en la lista para iterar
      return nullptr;
   }

   // obtengo el nodo actual apuntado por el contador
   Node<T> *current = lst.head;

   // avanza al siguiente nodo
   lst.head = current->sig;

   
   lst.count--;

   // retorno la dirección del elemento actual
   return &(current->info);
}

template <typename T>
T *listNext(List<T> &lst, bool &endOfList)
{
   if (lst.count <= 0)
   {
      // no quedan elementos en la lista para iterar
      endOfList = true;
      return nullptr;
   }

   // obtengo el nodo actual apuntado por el puntero iterador
   Node<T> *current = lst.iterator;

   // avanzo el puntero iterador al siguiente nodo
   lst.iterator = current->sig;

   
   lst.count--;

   if (lst.count <= 0)
   {
      // indico que  llegamos al final de la lista
      endOfList = true;
   }
   else
   {
      endOfList = false;
   }

   // retorno la direcc del elemento actual
   return &(current->info);
}


#endif
