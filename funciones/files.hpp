#ifndef _TFILES_T_
#define _TFILES_T_

#include <iostream>
#include <stdio.h>
// Se debe anteponer esta linea al inicio de la funcion.
// De otro modo, apareceran errores al momento de actualizar
// archivos. Esto se debe a un error en la implementacion de Windows.
//
// fseek(f,0,SEEK_CUR);
template <typename T>
void write(FILE *f, T t)
{
   fseek(f, 0, SEEK_CUR);

   fwrite(&t, sizeof(T), 1, f); // escribo en el archivo, le paso el valor a escribir por ref, luego el tamanio de su tipo de dato, luego indico la cantidad de elemntos a escribir y el archivo donde se escribe
}

template <typename T>
T read(FILE *f)
{
   fseek(f, 0, SEEK_CUR);
   T t;
   fread(&t, sizeof(T), 1, f); // leo el primer byte

   return t; // devuelvo el valor que lei
}

template <typename T>
void seek(FILE *f, int n)             // n numero de registro al que haremos apuntar, en bytes, ej: tengo 3 short, 111 222 333, cada uno tiene 2 bytes, con n=0 me da el primer short(el inicio del nuevo registro), n=2 el segundo y n=4 el 3.
{                                     // estas posiciones (n) coinciden con el producto entre el numero de registro que comienza y el tamanio del tipo de dato del archivo
   fseek(f, n * sizeof(T), SEEK_SET); // le paso el archvio, en que pos empiece a leer y seek_set  indica que el desplazamiento se realizará desde el inicio del archivo. por eso debo multiplicarlo por el tamanio del tipo de dato de los registros si es que quiero utilizar 0,1,2,3 etc..
}

template <typename T>
int fileSize(FILE *f)
{
   int i = 0;
   T t;
   t = read<T>(f);  // leo primer registro
   while (!feof(f)) // si no esta vacio, entro, aumento el iterador y sigo leyendo hasta el fin
   {
      i++;
      t = read<T>(f);
   }

   return i;
}

template <typename T>
int filePos(FILE *f) //retorna el numero de registro que esta siendo apuntado por el indicador de posicion del archivo f
{
   return ftell(f);
}

#endif
