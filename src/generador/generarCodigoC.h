#ifndef _GENERAR_CODIGO_C_H
#define _GENERAR_CODIGO_C_H

#include "creacionNodos.h"

char * cadenaVacia = "";

typedef char * (* reductor)(Nodo *);


char * reducirNodoCadena(Nodo * nodo);
char * reducirNodoConstante(Nodo * nodo);
char * reducirNodoVariable(Nodo * nodo);
char * reducirNodoOperacion(Nodo * nodo);
char * reducirNodoCondicional(Nodo * nodo);
char * reducirNodoBloque(Nodo * nodo);
char * reducirNodoVacio(Nodo * nodo);
char * reducirSi(Nodo * nodo);
char * reducirMientras(Nodo * nodo);
char * reducirRetornar(Nodo * nodo);
char * reducirInstrucciones(Nodo * nodo);
char * reducirInstruccion(Nodo * nodo);
char * reducirNegacion(Nodo * nodo);
char * reducirImprimir(Nodo * nodo);

static char * eval(Nodo * nodo);
char * generarCodigoC(Nodo * nodo);

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
  reducirImprimir
};
#endif
