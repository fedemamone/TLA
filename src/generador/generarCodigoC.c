#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "generarCodigoC.h"

static variableDefinida variables[MAX_VARIABLES];

typedef char *(*reductor)(Nodo *);

reductor reductores[] = {
    reducirNodoCadena,
    reducirNodoConstante,
    reducirNodoVariable,
    reducirNodoOperacion,
    reducirNodoCondicional,
    reducirNodoBloque,
    reducirNodoVacio,
    reducirSi,
    reducirMientras,
    reducirRetornar,
    reducirInstrucciones,
    reducirInstruccion,
    reducirNegacion,
    reducirImprimir};

char *reducirNodoCadena(Nodo *nodo)
{
  char *valor = ((NodoCadena *)nodo)->cadena;

  const size_t bufferLongitud = strlen(valor) + 1;
  char *buffer = malloc(bufferLongitud);
  snprintf(buffer, bufferLongitud, "%s", valor);

  return buffer;
}

char *reducirNodoConstante(Nodo *nodo)
{
  char *valor = ((NodoConstante *)nodo)->constante;
  return valor;
}

char *reducirNodoVariable(Nodo *nodo)
{
  char *nombre = ((NodoVariable *)nodo)->nombre;
  char *longitudPuntuacion = "_";
  char *nuevaVariable = calloc(strlen(nombre) + strlen(longitudPuntuacion) + 1, sizeof(char));

  strcpy(nuevaVariable, nombre);
  strcat(nuevaVariable, "_");

  return nuevaVariable;
}

variableDefinida buscarOCrearVariable(char *nombreDeLaVariable)
{
  int i;
  int encontrado;

  for (i = 0, encontrado = 0; variables[i].nombre[0] != '0' && i < MAX_VARIABLES && !encontrado; i++)
  {
    if (strcmp(variables[i].nombre, nombreDeLaVariable) == 0)
    {
      encontrado = 1;
      variables[i--].definida = 1;
    }
  }

  if (!encontrado)
  {
    strcpy(variables[i].nombre, nombreDeLaVariable);
    variables[i].definida = 0;
  }

  return variables[i];
}

char *reducirNodoOperacion(Nodo *nodo)
{
  NodoOperacion *nodoValor = (NodoOperacion *)nodo;

  char *primero = eval(nodoValor->primero);
  char *segundo = eval(nodoValor->segundo);
  char *operador = nodoValor->operador;
  char *buffer;

  if (nodoValor->primero->tipo == NODO_VARIABLE && strcmp(nodoValor->operador, "=") == 0)
  {
    variableDefinida variable = buscarOCrearVariable(((NodoVariable *)nodoValor->primero)->nombre);

    NodoVariable *nodoPrimero = (NodoVariable *)nodoValor->primero;
    NodoVariable *nodoSegundo = (NodoVariable *)nodoValor->segundo;

    if ((nodoValor->segundo->tipo == NODO_CADENA || (nodoValor->segundo->tipo == NODO_VARIABLE && nodoSegundo->almacenado != NULL && nodoSegundo->almacenado->tipo == NODO_CADENA)))
    {
      const size_t tipoLongitud = strlen("char* ");
      const size_t bufferLongitud = strlen(primero) + strlen(operador) + strlen(segundo) + tipoLongitud + 4;
      buffer = malloc(bufferLongitud);
      if (variable.definida == 0)
      {
        snprintf(buffer, bufferLongitud, "char* ");
      }
      variable.tipo = NODO_CADENA;
    }
    else
    {
      const size_t tipoLongitud = strlen("int ");
      const size_t bufferLongitud = strlen(primero) + strlen(operador) + strlen(segundo) + tipoLongitud + 4; //el "_", " " y ";"
      buffer = malloc(bufferLongitud);
      if (variable.definida == 0)
      {
        snprintf(buffer, bufferLongitud, "int ");
      }
      variable.tipo = NODO_CONSTANTE;
    }

    strcat(buffer, primero);
    strcat(buffer, " ");
    strcat(buffer, operador);
    strcat(buffer, " ");
    strcat(buffer, segundo);
    strcat(buffer, ";");

    return buffer;
  }
  else
  {
    const size_t delimitadorLongitud = strlen("()");
    const size_t bufferLongitud = strlen(primero) + strlen(operador) + strlen(segundo) + delimitadorLongitud + 1;
    buffer = malloc(bufferLongitud);
    snprintf(buffer, bufferLongitud, "(%s%s%s)", primero, operador, segundo);
    return buffer;
  }
}

char *reducirNodoCondicional(Nodo *nodo)
{
  NodoCondicional *nodoValor = (NodoCondicional *)nodo;

  char *primero = eval(nodoValor->primero);
  char *segundo = eval(nodoValor->segundo);
  char *tercero = eval(nodoValor->tercero);

  const size_t delimitadorLongitud = 2 + 3 + 3; // "()", " ? ", " : "
  const size_t bufferLongitud = strlen(primero) + strlen(segundo) + strlen(tercero) + delimitadorLongitud + 1;
  char *buffer = malloc(bufferLongitud);
  snprintf(buffer, bufferLongitud, "(%s ? %s : %s)", primero, segundo, tercero);

  return buffer;
}

char *reducirNodoBloque(Nodo *nodo)
{
  return eval(nodo);
}

char *reducirNodoVacio(Nodo *nodo)
{
  const char *delimitador = "\n";

  const size_t bufferLongitud = strlen(delimitador) + 1;
  char *buffer = malloc(bufferLongitud);
  strcpy(buffer, delimitador);

  return buffer;
}

char *reducirSi(Nodo *nodo)
{
  NodoSi *nodoValor = (NodoSi *)nodo;

  char *condicion = eval(nodoValor->condicion);
  char *entonces = eval(nodoValor->entonces);
  char *sino = eval(nodoValor->sino);

  const size_t delimitadorLongitud = strlen("if %s {%s} else {%s}");
  const size_t bufferLongitud = strlen(condicion) + strlen(entonces) + strlen(sino) + delimitadorLongitud + 1;
  char *buffer = malloc(bufferLongitud);
  snprintf(buffer, bufferLongitud, "if %s {%s} else {%s}", condicion, entonces, sino);

  return buffer;
}

char *reducirMientras(Nodo *nodo)
{
  NodoMientras *nodoValor = (NodoMientras *)nodo;

  char *condicion = eval(nodoValor->condicion);
  char *bloque = eval(nodoValor->bloque);

  const size_t delimitadorLongitud = strlen("while %s {%s}");
  const size_t bufferLongitud = strlen(condicion) + strlen(bloque) + delimitadorLongitud + 1;
  char *buffer = malloc(bufferLongitud);
  snprintf(buffer, bufferLongitud, "while %s {%s}", condicion, bloque);

  return buffer;
}

char *reducirRetornar(Nodo *nodo)
{
  NodoRetornar *nodoValor = (NodoRetornar *)nodo;

  char *expresion = eval(nodoValor->expresion);

  const size_t delimitadorLongitud = strlen("return ;");
  const size_t bufferLongitud = strlen(expresion) + delimitadorLongitud + 1;
  char *buffer = malloc(bufferLongitud);
  snprintf(buffer, bufferLongitud, "return %s;\n", expresion);

  return buffer;
}

char *reducirInstrucciones(Nodo *nodo)
{
  NodoLista *lista = (NodoLista *)nodo;

  char *buffer = malloc(1);
  buffer[0] = '\0';
  size_t delimitadorLongitud = 0;

  if (lista == NULL)
    return buffer;

  do
  {
    Nodo *nodoActual = (Nodo *)lista->nodo;
    if (nodoActual == NULL)
      break;

    char *producto = eval(nodoActual);
    buffer = realloc(buffer, strlen(producto) + strlen(buffer) + delimitadorLongitud + 1);
    strcat(buffer, producto);

  } while ((lista = lista->siguiente) != NULL);

  return buffer;
}

char *reducirInstruccion(Nodo *nodo)
{
  NodoInstruccion *nodoValor = (NodoInstruccion *)nodo;

  char *instruccion = eval(nodoValor->instruccion);

  const size_t delimitadorLongitud = strlen(";");
  const size_t bufferLongitud = strlen(instruccion) + delimitadorLongitud + 1;
  char *buffer = malloc(bufferLongitud);
  snprintf(buffer, bufferLongitud, "%s\n", instruccion);

  return buffer;
}

char *reducirNegacion(Nodo *nodo)
{
  NodoNegacion *nodoValor = (NodoNegacion *)nodo;
  char *expresion = eval(nodoValor->expresion);

  const size_t delimitadorLongitud = strlen("(!)");
  const size_t bufferLongitud = strlen(expresion) + delimitadorLongitud + 1;
  char *buffer = calloc(bufferLongitud, sizeof(char));
  snprintf(buffer, bufferLongitud, "(!%s)", expresion);

  return buffer;
}
//chequear
char *reducirImprimir(Nodo *nodo)
{
  NodoImprimir *nodoValor = (NodoImprimir *)nodo;
  char *expresion = eval(nodoValor->expresion);
  char *parametroPrintf;
  variableDefinida variable = buscarOCrearVariable(expresion);

  if (variable.tipo == NODO_CADENA)
    parametroPrintf = "%s";
  else
    parametroPrintf = "%d";

  const size_t delimitadorLongitud = strlen("printf('', );\n") + 2; //2 de %s o %d
  const size_t bufferLongitud = strlen(expresion) + delimitadorLongitud + 1;
  char *buffer = calloc(bufferLongitud, sizeof(char));
  snprintf(buffer, bufferLongitud, "printf('%s', %s);\n", parametroPrintf, expresion);

  return buffer;
}

//Toma el nodo y llama al reductor correspondiente al tipo

static char *eval(Nodo *nodo)
{
  if (nodo == NULL || reductores[nodo->tipo] == NULL)
  {
    char *cadenaVacia = "";
    return cadenaVacia;
  }

  return reductores[nodo->tipo](nodo);
}

// Genera el codigo C

char *generarCodigoC(Nodo *nodo)
{
  for (int i = 0; i < MAX_VARIABLES; i++)
  {
    memset(variables[i].nombre, '0', MAX_LONGITUD_NOMBRE_VARIABLE);
  }

  char *codigo = eval(nodo);

  return codigo;
}
