#include <stdlib.h>
#include <string.h>
#include "creacionNodos.h"

NodoCadena * cadena(const char * cadena) {
  NodoCadena * nodo = malloc(sizeof(NodoCadena));
  nodo->tipo = NODO_CADENA;
  nodo->valor = calloc(strlen(cadena) + 1, sizeof(char));
  strcpy(nodo->valor, cadena);
  return nodo;
}

NodoConstante * constante(const char * constante) {
  NodoConstante * nodo = malloc(sizeof(NodoConstante));
  nodo->tipo = NODO_CONSTANTE;
  nodo->valor = calloc(strlen(constante) + 1, sizeof(char));
  strcpy(nodo->valor, constante);
  return nodo;
}

NodoVariable * variable(const char * variable, Nodo * almacenado) {
  NodoVariable * nodo = malloc(sizeof(NodoVariable));
  nodo->tipo = NODO_VARIABLE;
  nodo->nombre = calloc(strlen(variable) + 1, sizeof(char));
  nodo->almacenado = almacenado;
  strcpy(nodo->nombre, variable);
  return nodo;
}


NodoOperacion * operacion(const Nodo * primero, const Nodo * segundo, const char * operador) {
  NodoOperacion * nodo = malloc(sizeof(NodoOperacion));
  nodo->tipo = NODO_OPERACION;
  nodo->primero = (Nodo *)primero;
  nodo->segundo = (Nodo *)segundo;
  nodo->operador = calloc(strlen(operador) + 1, sizeof(char));
  strcpy(nodo->operador, operador);
  return nodo;
}

NodoCondicional * condicional(const Nodo * primero, const Nodo * segundo, const Nodo * tercero) {
  NodoCondicional * nodo = malloc(sizeof(NodoCondicional));
  nodo->tipo = NODO_CONDICIONAL;
  nodo->primero = (Nodo *)primero;
  nodo->segundo = (Nodo *)segundo;
  nodo->tercero = (Nodo *)tercero;
  return nodo;
}


NodoSi * si(const Nodo * condicion, const Nodo * entonces, const Nodo * sino) {
  NodoSi * nodo = malloc(sizeof(NodoSi));
  nodo->tipo = NODO_SI;
  nodo->condicion = (Nodo *) condicion;
  nodo->entonces = (Nodo *)  entonces;
  nodo->sino = (Nodo *)  sino;
  return nodo;
}

NodoMientras * mientras(const Nodo * condicion, const Nodo * bloque) {
  NodoMientras * nodo = malloc(sizeof(NodoMientras));
  node->tipo = NODO_MIENTRAS;
  node->condicion = (Nodo *)  condicion;
  node->bloque = (Nodo *)  bloque;
  return nodo;
}

NodoLista * listaInstrucciones(const Nodo * nodo) {
  NodoLista * lista = malloc(sizeof(NodoLista));
  lista->tipo = NODO_INSTRUCCIONES;
  lista->nodo = (Nodo *) nodo;
  lista->siguiente = NULL;
  return lista;
}

NodoLista * agregarInstruccion(const NodoLista * lista, const Nodo * nodo) {
  NodoLista * nodoActual = (NodoLista *)lista;
  while (nodoActual->siguiente != NULL) nodoActual = nodoActual->siguiente;
  nodoActual->siguiente = newInstructionsList(nodo);

  return (NodoLista *)lista;
}

NodoRetornar * retornar(const Nodo * expresion) {
  NodoRetornar * nodo = malloc(sizeof(NodoRetornar));
  nodo->tipo = NODO_RETORNAR;
  nodo->expresion = (Nodo *)expresion;
  return nodo;
}


NodoBloque * bloque(const NodoLista * instrucciones) {
  NodoBloque * nodo = malloc(sizeof(NodoBloque));
  nodo->tipo = NODO_BLOQUE;
  nodo->instrucciones = (NodoLista *) instrucciones;
  return nodo;
}


Nodo * vacio() {
  Nodo * nodo = malloc(sizeof(Nodo));
  nodo->tipo = NODO_VACIO;
  return nodo;
}

NodoInstruccion * instruccion(Nodo * instruccion) {
  NodoInstruccion * nodo = malloc(sizeof(NodoInstruccion));
  nodo->tipo = NODO_INSTRUCCION;
  nodo->instruccion = instruccion;
  return nodo;
}

NodoNegacion * negacion(Nodo * expresion) {
  NodoNegacion * nodo = malloc(sizeof(NodoNegacion));
  nodo->tipo = NODO_NEGACION;
  nodo->expresion = expresion;
  return nodo;
}

NodoImprimir * imprimir(Nodo * expresion) {
  NodoImprimir * nodo = malloc(sizeof(NodoImprimir));
  nodo->tipo = NODO_IMPRIMIR;
  nodo->expresion = expresion;
  return nodo;
}
