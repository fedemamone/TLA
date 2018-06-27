typedef enum {
  NODO_CADENA = 0,
  NODO_CONSTANTE,
  NODO_VARIABLE,
  NODO_OPERACION,
  NODO_CONDICIONAL,
  NODO_BLOQUE,
  NODO_VACIO,
  NODO_SI,
  NODO_MIENTRAS,
  NODO_RETORNAR,
  NODO_INSTRUCCIONES,
  NODO_INSTRUCCION,
  NODO_NEGACION,
  NODO_IMPRIMIR
} tipoNodo;

typedef struct Nodo {
  tipoNodo tipo;
} Nodo;

typedef struct NodoLista {
  tipoNodo tipo;
  Nodo * nodo;
  struct NodoLista * siguiente;
} NodoLista;

typedef struct NodoCadena {
  tipoNodo tipo;
  char * cadena;
} NodoCadena;

typedef struct NodoConstante {
  tipoNodo tipo;
  char * constante;
} NodoConstante;

typedef struct NodoVariable {
  tipoNodo tipo;
  int declarado;
  char* nombre;
  Nodo * almacenado;
  char * variable;
} NodoVariable;

typedef struct NodoOperacion {
  tipoNodo tipo;
  Nodo * primero;
  Nodo * segundo;
  char * operador;
} NodoOperacion;

typedef struct NodoCondicional {
  tipoNodo tipo;
  Nodo * primero;
  Nodo * segundo;
  Nodo * tercero;
} NodoCondicional;

typedef struct NodoSi {
  tipoNodo tipo;
  Nodo * condicion;
  Nodo * entonces;
  Nodo * sino;
} NodoSi;

typedef struct NodoMientras {
  tipoNodo tipo;
  Nodo * condicion;
  Nodo * bloque;
} NodoMientras;

typedef struct NodoRetornar {
  tipoNodo tipo;
  Nodo * expresion;
} NodoRetornar;

typedef struct NodoBloque {
  tipoNodo tipo;
  NodoLista * instrucciones;
} NodoBloque;

typedef struct NodoInstruccion {
  tipoNodo tipo;
  Nodo * instruccion;
} NodoInstruccion;

typedef struct NodoNegacion {
  tipoNodo tipo;
  Nodo * expresion;
} NodoNegacion;

typedef struct NodoImprimir {
  tipoNodo tipo;
  Nodo * expresion;
} NodoImprimir;
