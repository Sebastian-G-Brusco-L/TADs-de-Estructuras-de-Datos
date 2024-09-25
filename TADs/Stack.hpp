#ifndef _TSTACK_TAD_
#define _TSTACK_TAD_

#include <iostream>
#include "C:\funciones\lists.hpp"

using namespace std;

template <typename T>
struct Stack
{
   Node<T> *top;
   int size;
};

template <typename T>
Stack<T> stack()
{
   Stack<T> st;
   st.top = nullptr;
   st.size = 0;
   return st;
}

template <typename T>
T *stackPush(Stack<T> &st, T e)
{
   Node<T> *newNode = new Node<T>;

   newNode->info = e;     // seteo el valor del nuevo nodo
   newNode->sig = st.top; // el nuevo nodo apunta al nodo actual 
   st.top = newNode;      // actualizo el puntero 'top' para que apunte al nuevo nodo
   st.size++;             // incremento el contador de elementos en la pila

   return &(newNode->info); // devuelvo la direcc del elemento apilado
}

template <typename T>
T stackPop(Stack<T> &st)
{
   Node<T> *poppedNode = st.top;     // obtengo el nodo en la cima
   T poppedValue = poppedNode->info; // obtengo el valor del nodo

   st.top = st.top->sig; // actualizo el puntero 'top' para que apunte al siguiente nodo
   delete poppedNode;    // libero la memoria del nodo desapilado
   st.size--;            // decremento el contador de elementos en la pila

   return poppedValue; // devuelvo el el elemento desapilado
}

template <typename T>
bool stackIsEmpty(Stack<T> st)
{
   // verifico si el contador de elementos es igual a cero (pila vacia)
   return st.size == 0;
}

template <typename T>
int stackSize(Stack<T> st)
{
   // retorno el valor del contador de elementos en la pila
   return st.size;
}

#endif
