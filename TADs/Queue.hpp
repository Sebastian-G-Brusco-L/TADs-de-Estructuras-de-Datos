#ifndef _TQUEUE_TAD_
#define _TQUEUE_TAD_

#include <iostream>
#include "\funciones\lists.hpp"

using namespace std;

template <typename T>
struct Queue
{
   Node<T> *front; // puntero al frente de la cola
   Node<T> *rear;  // puntero al final de la cola
   int size;       // contador de elementos en la cola
};

template <typename T>
Queue<T> queue()
{
   Queue<T> newQueue;
   newQueue.front = nullptr;
   newQueue.rear = nullptr;
   newQueue.size = 0;
   return newQueue;
}

template <typename T>
T *queueEnqueue(Queue<T> &q, T e)
{
   Node<T> *newNode = new Node<T>;
   if (!newNode)
   {
      // error: no se pudo asignar memoria para el nuevo nodo
      return nullptr;
   }

   newNode->info = e; // seteo el valor del nuevo nodo
   newNode->sig = nullptr;

   if (q.size == 0)
   {
      // la cola estaba vacia, este nuevo nodo será el frente como el final
      q.front = newNode;
      q.rear = newNode;
   }
   else
   {
      // la cola ya tenia elementos, agregamos el nuevo nodo al final
      q.rear->sig = newNode;
      q.rear = newNode;
   }

   q.size++; // incremento el contador de elementos 

   return &(newNode->info); // devuelvo la direcc del elemento encolado
}

template <typename T>
T queueDequeue(Queue<T> &q)
{
   if (q.size == 0)
   {
      // error: la cola está vacia, no se puede desencolar
      
      //  devuelvo un valor predeterminado para el tipo T
      return T();
   }

   // guardo el elemento del frente de la cola
   T element = q.front->info;

   // actualizo el frente de la cola al siguiente nodo
   Node<T> *temp = q.front;
   q.front = q.front->sig;

   // si la cola queda vacia, tambien actualizo el puntero al final de la cola
   if (q.size == 1)
   {
      q.rear = nullptr;
   }

   // libero la memoria del nodo desencolado
   delete temp;

   // decremento el contador de elementos
   q.size--;

   return element; // retorno el elemento desencolado
}

template <typename T>
bool queueIsEmpty(Queue<T> q)
{
   return q.size == 0;
}

template <typename T>
int queueSize(Queue<T> q)
{
   return q.size;
}

#endif
