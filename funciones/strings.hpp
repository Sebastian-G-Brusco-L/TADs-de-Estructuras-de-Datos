#ifndef _TSTRINGS_T_
#define _TSTRINGS_T_

#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

int length(string s)
{
   int i = 0;
   for (; s[i] != '\0'; i++)
   {
      /* code */
   }

   return i;
}

// cuenta cuantas veces aparece un caracter
int charCount(string s, char c)
{
   int contador = 0;

   for (int i = 0; i < length(s); i++)
   {
      if (s[i] == c)
      {
         contador++;
      }
   }

   return contador;
}

// subcadena con inicio y final a eleccion
string substring(string s, int d, int h)
{
   string retorno;

   for (; d < h; d++)
   {
      retorno += s[d];
   }

   return retorno;
}
// sobrecarga de substring, inicio d hasta el final
string substring(string s, int d) // ok
{
   string ret;
   for (; d < length(s); d++)
   {
      ret += s[d];
   }
   return ret;
}
// la primera posicion de el caracter c
int indexOf(string s, char c) // ok
{
   int pos = -1;

   for (int i = 0; i < length(s); i++)
   {
      if (s[i] == c)
      {
         pos = i;
         break;
      }
   }

   return pos;
}
// sobre carga, retorna posicion de un caracter con desplazamiento de x caracteres
int indexOf(string s, char c, int offSet) // ok
{
   int pos = 0;

   for (int i = 0; i < length(s); i++)
   {
      if (s[offSet] == c)
      {
         pos = offSet;
         break;
      }
      offSet++;
   }

   return pos;
}

int indexOf(string s, string toSearch) // ok
{

   for (int i = 0; i <= length(s) - length(toSearch); i++)
   {
      int j;
      for (j = 0; j < length(toSearch); j++)
      {
         if (s[i + j] != toSearch[j])
         {
            break;
         }
      }
      if (j == length(toSearch))
      {
         return i;
      }
   }
   return -1;
}

int indexOf(string s, string toSearch, int offset) // ok
{

   for (int i = offset; i <= length(s) - length(toSearch); i++)
   {
      bool match = true;
      for (int j = 0; j < length(toSearch); j++)
      {
         if (s[i + j] != toSearch[j])
         {
            match = false;
            break;
         }
      }
      if (match)
      {
         return i;
      }
   }

   return -1;
}
// ultima posicion de x caracter
int lastIndexOf(string s, char c)
{
   int pos = -1;
   for (int i = length(s) - 1; i >= 0; i--)
   {
      if (s[i] == c)
      {
         pos = i;
         break;
      }
   }
   return pos;
}

int indexOfN(string s, char c, int n)
{
   int count = 0;
   int pos = -1;
   for (int i = 0; i < length(s); i++)
   {
      if (s[i] == c)
      {
         count++;
         if (count == n)
         {
            pos = i;
            break;
         }
      }
   }
   if (n == 0 || count < n)
   {
      return -1;
   }
   else if (count == n)
   {
      return pos;
   }
   else
   {
      return length(s);
   }
}

int charToInt(char c)
{
   if (c >= '0' && c <= '9')
   {
      return c - '0';
   }
   else if (c >= 'a' && c <= 'z')
   {
      return c - 'a' + 10;
   }
   else if (c >= 'A' && c <= 'Z')
   {
      return c - 'A' + 10;
   }
   return -1; // Carácter inválido
}

char intToChar(int i)
{
   if (i >= 0 && i <= 9)
   {
      return i + '0';
   }
   else if (i >= 10 && i <= 35)
   {
      return i - 10 + 'A';
   }
   // Si no se cumple ninguna de las condiciones anteriores, retorna un carácter nulo ('\0')
   return '\0';
}

int getDigit(int n, int i)
{
   int retorno;

   string c = to_string(n);
   int p = (length(c) - i) - 1;
   for (int j = length(c); j > 0; j--)
   {
      retorno = charToInt(c[p]);
   }

   return retorno;
}

int digitCount(int n)
{
   string s = to_string(n);
   return length(s);
}

string intToString(int i) // 12345
{

   string s;
   for (int j = 0; j < digitCount(i); j++)
   {

      int p = getDigit(i, j);
      char c = intToChar(p);
      s = c + s;
   }

   return s;
}

int stringToInt(string s, int b) // ok
{
   int result = 0;
   int base = 1;

   // Iteramos la cadena desde el último carácter al primero
   for (int i = length(s) - 1; i >= 0; i--)
   {
      // Obtenemos el valor numérico del carácter actual
      int digit = charToInt(s[i]);

      // Si el valor numérico es mayor o igual que la base, la cadena no representa un número válido
      if (digit >= b)
      {
         return -1;
      }

      // Agregamos al resultado el valor numérico del carácter multiplicado por la base correspondiente
      result += digit * base;

      // Actualizamos la base para el siguiente carácter
      base *= b;
   }

   return result;
}

int stringToInt(string s) // ok
{
   int ret = 0; // 12345
   int potencia = 1;
   for (int i = length(s) - 1; i >= 0; i--) // 5>0
   {

      ret += charToInt(s[i]) * potencia; // retorno = 0 + 5*1
      potencia *= 10;                    // 1*10
   }

   return ret;
}

string charToString(char c)
{
   string s;
   return s += c;
}

char stringToChar(string s)
{
   char c;

   return c += s[0];
}

string stringToString(string s)
{
   return s;
}

string doubleToString(double d)
{
   int parte_entera = floor(d);                                                                     // floor() funcion de math.h que retorna la parte entera
   double parte_decimal = fmod(d, 1.00);                                                            // fmod(dividendo,divisor) funcion de math.h que retronadevuelve el resto de la división del dividendo por el divisor, como un número de punto flotante ej 105.4345 retorna 0.4345
   string s = intToString(parte_entera) + "." + intToString((int)((parte_decimal + 0.0001) * 1000)); // le doy 2 decimales al multiplicar por 100 y le sumo 0.0001 para el error, por ej sin sumarle me daria 1.39, al sumarle 1.4
   return s;
}

double stringToDouble(string s) // 105.56
{
   int hastaPunto = indexOf(s, '.');                  // cantidad de digitos parte entera
   string parte_entera = substring(s, 0, hastaPunto); // string 105
   int x = stringToInt(parte_entera);                 // int 105

   string parte_decimal = substring(s, hastaPunto + 1); // string 56
   double z = stringToInt(parte_decimal);               // int 56
   int largoCadenaDecimal = length(parte_decimal);

   double ret = x + (z / pow(10, largoCadenaDecimal));

   return ret;
}
// cout<<boolalpha para ver explicitamente true or false en vez de 1 o 0
bool isEmpty(string s)
{
   bool vacia = false;
   if (length(s) == 0)
   {
      return vacia = true;
   }

   return vacia;
}

bool startsWith(string s, string x) // s="cursoDeAlgoritmos"     z="curso"
{
   string z = substring(s, 0, length(x)); // subcadena desde el inicio de x hasta el tamanio del prefijo
   bool coincide = false;
   if (x == z)
   {
      return coincide = true;
   }

   return coincide;
}

bool endsWith(string s, string x) // s=cursoDeAlgoritmos    x = Algoritmos
{
   int startsSufijo = length(s) - length(x);         // donde empieza el sufijo
   string z = substring(s, startsSufijo, length(s)); // subcadena desde donde empieza el sufijo hasta el fin de la cadena s
   bool coincide = false;
   if (x == z)
   {
      return coincide = true;
   }

   return coincide;
}

bool contains(string s, char c)
{
   bool contiene = true;
   if (indexOf(s, c) == -1)
   {
      return contiene = false;
   }

   return contiene;
}

string replace(string s, char oldChar, char newChar) // Esto es una prueba       'e'  por  'X'         =    Esto Xs una pruXba
{
   string nuevaS = s; // hago una copia de la cadena para no pasarla por referencia
   int pos = 0;
   for (int i = 1; i <= charCount(s, oldChar); i++)
   {
      pos = indexOfN(s, oldChar, i); // retorna posicion del caracter oldchar
      nuevaS[pos] = newChar;         // a esa posicion le asigno el nuevo caracters
   }

   return nuevaS;
}

string insertAt(string s, int pos, char c) // Esto es una prueba    pos=6  ,  'X'       = Esto eXs una prueba
{
   string nuevaS = s;
   string subAntes = substring(s, 0, pos); // separo la string antes de la pos 6
   string subDespues = substring(s, pos);  // separo la string despues de la pos 6

   char p = nuevaS[pos] = c; // p es el reemplazo  / en la cadena nuevaS[6] le asigno el nuevo caracter 'X', esto se lo asigno a un caracter para sumarlo en la cadena
   nuevaS = subAntes + p + subDespues;
   return nuevaS;
}

string removeAt(string s, int pos) // Esto es una prueba pos=7  =   Esto esuna pureba
{
   string sub_cadena_uno = substring(s, 0, pos);  // Esto es
   string sub_cadena_dos = substring(s, pos + 1); // una prueba

   string retorno = sub_cadena_uno + sub_cadena_dos;

   return retorno;
}

string ltrim(string s)
{
   string retorno;
   int i = 0;
   for (; s[i] == ' '; i++)
   {
   }
   retorno = substring(s, i, length(s));

   return retorno;
}

string rtrim(string s) // [Esto es una prueba   ]
{

   int i = length(s) - 1;
   for (; s[i] == ' '; i--)
   {
   }
   string retorno = substring(s, 0, i + 1);

   return retorno;
}

string trim(string s)
{
   string retorno = rtrim(s);

   retorno = ltrim(retorno);

   return retorno;
}

string replicate(char c, int n)
{
   std::string s(n, c); // funcionalidad de la biblioteca estandar, al string s le paso (tamanio,contenido)
   return s;
}

string spaces(int n)
{
   std::string s(n, ' '); // funcionalidad de la biblioteca estandar, al string s le paso (tamanio,contenido)
   return s;
}

string lpad(string s, int n, char c)
{
   string cadena = replicate(c, n);
   cadena += s;

   return cadena;
}

string rpad(string s, int n, char c)
{
   string cadena = replicate(c, n);
   s += cadena;

   return s;
}

string cpad(string s, int n, char c)
{
   string cadena = lpad(s, n, c);
   cadena = rpad(cadena, n, c);

   return cadena;
}

bool isDigit(char c)
{
   bool esdigito = false;
   if (c >= 48 && c <= 57)
   {
      return esdigito = true;
   }

   return esdigito;
}

bool isLetter(char c)
{
   bool esletra = false;
   if (c >= 65 && c <= 90)
   {
      return esletra = true;
   }
   if (c >= 97 && c <= 122)
   {
      return esletra = true;
   }

   return esletra;
}

bool isUpperCase(char c)
{
   bool esletra = false;
   if (c >= 65 && c <= 90)
   {
      return esletra = true;
   }

   return esletra;
}

bool isLowerCase(char c)
{
   bool esletra = false;
   if (c >= 97 && c <= 122)
   {
      return esletra = true;
   }

   return esletra;
   return true;
}

char toUpperCase(char c)
{

   if (isLowerCase(c))
   {
      c = c - 'a' + 'A';
   }
   return c;
}

char toLowerCase(char c)
{
   if (isUpperCase(c))
   {
      c = c - 'A' + 'a';
   }

   return c;
}

string toUpperCase(string s)
{
   string retorno;
   for (int i = 0; i < length(s); i++)
   {
      retorno += toUpperCase(s[i]);
   }

   return retorno;
}

string toLowerCase(string s)
{
   string retorno;
   for (int i = 0; i < length(s); i++)
   {
      retorno += toLowerCase(s[i]);
   }

   return retorno;
}

int cmpString(string a, string b) // hola   holaaaa
{
   int cmp = 0;
   int cadena_mas_corta = 0;
   if (length(a) > length(b)) // para no iterear de mas
   {
      cadena_mas_corta = length(b);
   }
   else
      cadena_mas_corta = length(a);

   for (int i = 0; i < cadena_mas_corta; i++)
   {
      if (a[i] == b[i])
      {
         cmp = 0;
      }
      else if (a[i] > b[i])
      {
         return 1;
      }
      else if (a[i] < b[i])
      {
         return -1;
      }
   }

   // para una cadena compara su longitud, ya que holaaaa al tener mas caracteres la convierte en una cadena mas grande
   if (length(a) < length(b))
   {
      return -1;
   }
   else if (length(a) > length(b))
   {
      return 1;
   }
   return cmp;
}

int cmpDouble(double a, double b)
{
   if (a > b)
   {
      return 1;
   }
   else if (a < b)
   {
      return -1;
   }

   return 0;
}

#endif
