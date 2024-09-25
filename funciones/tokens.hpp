#ifndef _TTOKENS_T_
#define _TTOKENS_T_

#include <iostream>
#include <stdio.h>
#include "strings.hpp"
using namespace std;

int tokenCount(string s, char sep)
{
   return isEmpty(s) ? 0 : charCount(s, sep) + 1;
}

void addToken(string &s, char sep, string t)
{
   s = isEmpty(s) ? t : s + sep + t;
}

string getTokenAt(string s, char sep, int i) //"John|Paul|George|Ringo"
{
   string retorno;
   int primerPos = indexOfN(s, sep, i),      // primera posicion del caracter sep
       segundaPos = indexOfN(s, sep, i + 1); // siguiente posicion del caracter sep
   if (segundaPos == -1)
   {
      segundaPos = length(s);
   }
   //+1 al segundo arg de substring porque sino me incluye el primer caracter,
   retorno = substring(s, primerPos + 1, segundaPos); // sub( s, indXN(s,'|',1)=4    , indXN(s,'|',1+1)=9      )

   return retorno;
}

void removeTokenAt(string &s, char sep, int i) //"John|Paul|George|Ringo"
{
   int primerPos = indexOfN(s, sep, i);      // = 9   con i=2
   int segundaPos = indexOfN(s, sep, i + 1); // 16
   if (primerPos == -1)
   {
      primerPos = 0;
      segundaPos++; // para eliminar el primer sep
   }
   if (segundaPos == -1)
   {
      segundaPos = length(s);
   }

   for (int j = primerPos; j < segundaPos; j++)
   {
      s = removeAt(s, primerPos); // remueve el caracter 4
   }
}

void setTokenAt(string &s, char sep, string t, int i) //"John|Paul|George|Ringo"  t="Seba"
{
   int primerPos = indexOfN(s, sep, i);      // = 9   con i=2
   int segundaPos = indexOfN(s, sep, i + 1); // 16
   int contador = 0;
   removeTokenAt(s, sep, i); //"John|Paul|Ringo"
   // para casos de los extremos
   if (primerPos == -1)
   {
      primerPos = 0;
      t = t + sep;
   }
   else
      t = sep + t;

   for (int j = primerPos; contador < length(t); j++)
   {

      s = insertAt(s, j, t[contador]);
      contador++;
   }
}

int findToken(string s, char sep, string t) //"John|Paul|George|Ringo"   t=George
{

   int pos = -1;
   int contador = 0;
   int aparicionT = indexOf(s, t);
   bool estaDentro = false;
   string subcadenaS = substring(s, 0, aparicionT); //"John|Paul|
   for (int i = 0; i < length(subcadenaS); i++)     // recorro subcadenaS y comparo si ambos contadores son iguales para verificar que este dentro
   {

      if (contador == i)
      {
         estaDentro = true;
      }
      if (contains(s, t[i]) == true)
      {
         contador++;
      }
   }

   if (estaDentro == true)
   {
      pos = charCount(subcadenaS, sep); // cuento los caracteres sep
   }
   if (isEmpty(subcadenaS)) // si encuentra la cadena en la posicion 0
   {
      pos = 0;
   }
   if (aparicionT == -1) // si no encuentra la cadena t
   {
      pos = -1;
   }

   return pos;
}

#endif
