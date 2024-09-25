#ifndef _TLIST_T_
#define _TLIST_T_

#include <iostream>
#include <stdio.h>

template <typename T>
struct Node
{
   T info;
   Node<T> *sig;
};

template <typename T>
Node<T> *add(Node<T> *&p, T e)
{
   Node<T> *nuevo = new Node<T>(); // solicito espacio para el nuevo nodo
   // guardo valores en el nuevo nodo
   nuevo->info = e;
   nuevo->sig = NULL; // null porque es el ultimo

   if (p != NULL) // si es el primero de la lista
   {
      Node<T> *aux = p; // puntero aux que apunta al primer nodo
      // recorro la lista hasta el null (ultimo elemento)
      while (aux->sig != NULL)
      {
         aux = aux->sig; // hago que aux apunte al siguiente nodo para vovler a verificar si es null
      }
      // terminado el ciclo tengoa a aux apuntando al ultimo nodo para asi asignarle el nuevo noodo creado
      aux->sig = nuevo; // asigno el nuevo nodo al sig
   }
   else // si no es el primero de la lista
   {
      p = nuevo; // p al ser null, le asigno el nuevo nodo convirtiendolo en el primer nodo de la lista
   }

   return nuevo;
}

template <typename T>
Node<T> *addFirst(Node<T> *&p, T e)
{
   // crear un nuevo nodo con el elemento e
   Node<T> *nuevo = new Node<T>;
   nuevo->info = e;

   // establecer el siguiente del nuevo nodo al nodo actualmente en el inicio
   nuevo->sig = p;

   // actualizar el puntero p para que apunte al nuevo nodo
   p = nuevo;

   // retornar la direccion del nodo que contiene el elemento que se agrego (nuevo nodo)
   return nuevo;
}

template <typename T, typename K>
T remove(Node<T> *&p, K k, int cmpTK(T, K))
{

   Node<T> *current = p;
   Node<T> *previous = nullptr;

   while (current != nullptr)
   {
      if (cmpTK(current->info, k) == 0)
      {
         // encontramos una coincidencia y elimina el nodo actual
         if (previous == nullptr)
         {
            // el nodo a eliminar es el primer nodo de la lista
            p = current->sig;
         }
         else
         {
            // el nodo a eliminar no es el primero de la lista
            previous->sig = current->sig;
         }

         T removedValue = current->info;
         delete current;
         return removedValue; // retorna el valor del elemento removido
      }

      // avanzar al siguiente nodo
      previous = current;
      current = current->sig;
   }
   //  no se encontro la coincidencia en toda la lista
   // devuelve un valor predeterminado para T 
   return T();
}

template <typename T>
T removeFirst(Node<T> *&p)
{
   Node<T> *firstNode = p;           //  primer nodo
   T removedValue = firstNode->info; //  valor del primer nodo

   p = p->sig; // actualiza el puntero al primer nodo para que apunte al siguiente

   delete firstNode; // libera la memoria del nodo eliminado

   return removedValue; // retorna el valor del elemento removido
}

template <typename T, typename K>
Node<T> *find(Node<T> *p, K k, int cmpTK(T, K))
{
   Node<T> *current = p;

   while (current != NULL)
   {
      if (cmpTK(current->info, k) == 0)
      {
         // encontramos una coincidencia retorno la direccion del nodo actual
         return current;
      }

      // avanzar al siguiente nodo
      current = current->sig;
   }

   // no se encontro ninguna coincidencia retorno NULL
   return NULL;
}

template <typename T>
Node<T> *orderedInsert(Node<T> *&p, T e, int cmpTT(T, T))
{
   Node<T> *newNode = new Node<T>(); // nuevo nodo con el elemento e
   newNode->info = e;

   Node<T> *current = p;
   Node<T> *previous = NULL;

   // recorro la lista mientras se cumple el criterio de ordenamiento
   while (current != NULL && cmpTT(e, current->info) > 0)
   {
      previous = current;
      current = current->sig;
   }

   // inserto el nuevo nodo entre el nodo anterior y el nodo actual
   if (previous != NULL)
   {
      previous->sig = newNode;
   }
   else
   {
      // si previous es nullptr, el nuevo nodo se convierte en el primer nodo de la lista
      p = newNode;
   }

   newNode->sig = current; // conecto el nuevo nodo al nodo actual

   return newNode; // devuelvo la direccion del nodo insertado
}

template <typename T>
Node<T> *searchAndInsert(Node<T> *&p, T e, bool &enc, int cmpTT(T, T))
{
   enc = false; // inicialmente, no se encontro ni inserto el elemento

   Node<T> *newNode = new Node<T>(); // creo un nuevo nodo con el elemento e
   newNode->info = e;

   Node<T> *current = p;
   Node<T> *previous = NULL;

   // recorro la lista mientras se cumple el criterio de ordenamiento
   while (current != NULL && cmpTT(e, current->info) > 0)
   {
      previous = current;
      current = current->sig;
   }

   // compruebo si el elemento se encontro en la lista
   if (current != NULL && cmpTT(e, current->info) == 0)
   {
      enc = true;     // se encontro el elemento
      delete newNode; // no se necesita el nuevo nodo
      return current; // devuelvo la direccion del nodo encontrado
   }

   // inserto el nuevo nodo entre el nodo anterior y el nodo actual
   if (previous != NULL)
   {
      previous->sig = newNode;
   }
   else
   {
      // si previous es nullptr, el nuevo nodo se convierte en el primer nodo de la lista
      p = newNode;
   }

   newNode->sig = current; // conecto el nuevo nodo al nodo actual

   return newNode; // devuelvo la dirección del nodo insertado
}

template <typename T>
void sort(Node<T> *&p, int cmpTT(T, T))
{
   // si la lista esta vacia o tiene un solo elemento, ya esta ordenada
   if (p == NULL || p->sig == NULL)
   {
      return;
   }

   Node<T> *current = p;
   Node<T> *index = NULL;
   T temp;

   while (current != NULL)
   {
      index = current->sig;

      while (index != NULL)
      {
         if (cmpTT(current->info, index->info) > 0)
         {
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
bool isEmpty(Node<T> *p)
{
   return p == NULL; // comparo si el puntero es nulo, si lo es, llego al final
}

template <typename T>
void free(Node<T> *&p)
{
   while (p != NULL)
   {
      Node<T> *temp = p;
      p = p->sig;
      delete temp;
   }
   p = NULL; // asigna null a p para indicar que la lista esta vacia.
}

template <typename T>
Node<T> *push(Node<T> *&p, T e)
{
   Node<T> *nuevo = new Node<T>(); // creo un nuevo nodo
   nuevo->info = e;                // asigno el valor e al nuevo nodo
   nuevo->sig = p;                 // hago que el nuevo nodo apunte al nodo actual (primer nodo de la lista)
   p = nuevo;                      // actualiuzo el puntero al primer nodo para que sea el nuevo nodo

   return p; // retorno la direccion del nuevo nodo)
}

template <typename T>
T pop(Node<T> *&p)
{
   Node<T> *temp = p;    // almaceno el primer nodo temporalmente
   T elemento = p->info; // almaceno el valor del primer nodo

   p = p->sig; // actualizo el puntero al primer nodo para que apunte al siguiente nodo

   delete temp; // libero la memoria del nodo removido

   return elemento; // retorno el elemento que estaba en el primer nodo
}

template <typename T>
Node<T> *enqueue(Node<T> *&p, Node<T> *&q, T e)
{
   Node<T> *nuevo = new Node<T>(); // creo un nuevo nodo
   nuevo->info = e;                // asugno el elemento al nuevo nodo
   nuevo->sig = NULL;              // me aseguro de que el nuevo nodo sea el ultimo (apunte a nullptr)

   if (p == NULL)
   {
      // si la lista esta vacia, ambos punteros apuntan al nuevo nodo
      p = nuevo;
      q = nuevo;
   }
   else
   {
      // si la lista no esta vacia, solo el puntero q (ultimo) se actualiza
      q->sig = nuevo;
      q = nuevo;
   }

   return nuevo; // retorno el nodo que contiene el elemento que se agrego al final
}

template <typename T>
Node<T> *enqueue(Node<T> *&q, T e)
{
   Node<T> *nuevo = new Node<T>(); // creo un nuevo nodo
   nuevo->info = e;                // asigno el elemento al nuevo nodo

   if (q == NULL)
   {
      // sii la lista está vacia, el nuevo nodo se convierte en el unico nodo de la lista
      nuevo->sig = nuevo; // hago que el nuevo nodo apunte a si mismo
      q = nuevo;          // actualizo el puntero al ultimo nodo
   }
   else
   {
      // Ssi la lista no esta vacia, inserto el nuevo nodo despues del ultimo nodo (q)
      nuevo->sig = q->sig; // el nuevo nodo apunta al primer nodo de la lista
      q->sig = nuevo;      // actualizo el ultimo nodo para que apunte al nuevo nodo
      q = nuevo;           // actualizo el puntero al ultimo nodo
   }

   return nuevo; // retorno el nodo que contiene el elemento que se agrego al final
}

template <typename T>
T dequeue(Node<T> *&p, Node<T> *&q)
{
   Node<T> *removedNode = p;           // obtengo el primer nodo a eliminar
   T removedValue = removedNode->info; // obtengo el valor del nodo a eliminar

   if (p == q)
   {
      // si hay un solo nodo en la lista, la lista se vuelve vacia
      p = NULL;
      q = NULL;
   }
   else
   {
      // si hay mas de un nodo en la lista, actualizo el puntero al primer nodo (p)
      // para que apunte al siguiente nodo despues del nodo a eliminar
      p = p->sig;
      q->sig = p; // actualizo el puntero del último nodo para que apunte al nuevo primer nodo
   }

   delete removedNode;  // libero la memoria del nodo eliminado
   return removedValue; // retorno el valor del elemento que fue removido
}

template <typename T>
T dequeue(Node<T> *&q)
{
   Node<T>* removedNode = q->sig; // obtengo el primer nodo a eliminar
    T removedValue = removedNode->info; // obtengo el valor del nodo a eliminar

    if (q == q->sig) {
        // si hay un solo nodo en la lista, la lista se vuelve vacia
        q = nullptr;
    } else {
        // si hay mas de un nodo en la lista, actualizo el puntero del ultimo nodo (q)
        // para que apunte al siguiente nodo despues del nodo a eliminar
        q->sig = removedNode->sig;
    }

    delete removedNode; // libero la memoria del nodo eliminado
    return removedValue; // retorno el valor del elemento que fue removido
}

#endif
