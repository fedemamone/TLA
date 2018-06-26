#ifndef _CREACION_NODOS_H
#define _CREACION_NODOS_H

#include "Nodos.h"

NodoCadena * cadena(const char * cadena);
NodoConstante * constante(const char * constante);
NodoVariable * variable(const char * variable, Nodo * almacenado);
NodoOperacion * operacion(const Nodo * primero, const Nodo * segundo, const char * operador);
NodoCondicional * condicional(const Nodo * primero, const Nodo * segundo, const Nodo * tercero);
NodoSi * si(const Nodo * condicion, const Nodo * entonces, const Nodo * sino);
NodoMientras * mientras(const Nodo * condicion, const Nodo * bloque);
NodoLista * listaInstrucciones(const Nodo * nodo);
NodoLista * agregarInstruccion(const NodoLista * lista, const Nodo * nodo);
NodoRetornar * retornar(const Nodo * expresion);
NodoBloque * bloque(const NodoLista * instrucciones);
Nodo * vacio();
NodoInstruccion * instruccion(Nodo * instruccion);
NodoNegacion * negacion(Nodo * expresion);
NodoImprimir * imprimir(Nodo * expresion);

#endif
