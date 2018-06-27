%{
	#include "./creacionNodos.h"
	#include "./generarCodigoC.h"
	#define NULL 0
	extern int yylineno;
	void yyerror(NodoLista **, char *);
%}

%union {
 	int num;
 	char cadena[1000];
 	struct Nodo * nodo;
	struct NodoLista * lista;
}

%token VARIABLE NUMERO CADENA_LITERAL
%token LINEA_NUEVA
%token MEI_OP MAI_OP IGUAL_OP DIST_OP
%token CONJ_OP DISY_OP MULTI_ASIGNACION DIVIS_ASIGNACION
%token RESTA_ASIGNACION ASIGNACION SUMA_ASIGNACION
%token PAREN_ABRE PAREN_CIERRA
%token LLAVE_ABIERTA LLAVE_CERRADA
%token DOS_PUNTOS COMA
%token MULTI MODULO DIVIS SUMA RESTA
%token MENOR MAYOR
%token NEGACION
%token ENTONCES
%token SI SINO MIENTRAS RETORNAR IMPRIMIR

%type <nodo> expresion_primaria expresion_derecha operacion_multiplicativa
%type <nodo> operacion_aditiva operacion_relacional operacion_igualdad
%type <nodo> operacion_logica_conj operacion_logica_disy operacion_cond
%type <nodo> operacion_asignacion expresion bloque bloque_condicional
%type <nodo> bloque_ciclo bloque_retorno bloque_imprimir
%type <nodo> expresion_basica expresion_constante expresion_variable

%type <cadena> operador_asignacion operador_relacional ASIGNACION MULTI_ASIGNACION DIVIS_ASIGNACION SUMA_ASIGNACION RESTA_ASIGNACION
%type <cadena> VARIABLE CADENA_LITERAL NUMERO

%type <lista> llaves lista_instrucciones

%parse-param {NodoLista ** programa}

%start lista_instrucciones

%%

expresion_primaria:
	  expresion_constante { $$ = $1; }
	| CADENA_LITERAL { $$ = cadena($1); }
	| PAREN_ABRE expresion PAREN_CIERRA { $$ = $2; }
	;

expresion_constante:
	NUMERO { $$ = constante($1); }
	;

expresion_variable:
	VARIABLE { $$ = variable($1); }
	;

expresion_derecha:
	  expresion_primaria { $$ = $1; }
	| expresion_variable { $$ = $1; }
	;

expresion_basica:
	  expresion_derecha { $$ = $1; }
	| NEGACION expresion_derecha { $$ = negacion($2); }
	;

operacion_multiplicativa:
	  expresion_basica { $$ = $1; }
	| operacion_multiplicativa MULTI expresion_basica { $$ = operacion($1, $3, "*"); }
	| operacion_multiplicativa DIVIS expresion_basica { $$ = operacion($1, $3, "/"); }
	| operacion_multiplicativa MODULO expresion_basica { $$ = operacion($1, $3, "%"); }
	;

operacion_aditiva:
	  operacion_multiplicativa { $$ = $1; }
	| operacion_aditiva SUMA operacion_multiplicativa { $$ = operacion($1, $3, "+"); }
	| operacion_aditiva RESTA operacion_multiplicativa { $$ = operacion($1, $3, "-"); }
	;

operacion_relacional:
	  operacion_aditiva { $$ = $1; }
	| operacion_relacional operador_relacional operacion_relacional { $$ = operacion($1, $3, $2); }
	;

operador_relacional:
	  MENOR { strcpy($$, "<"); }
	| MAYOR { strcpy($$, ">"); }
	| MEI_OP { strcpy($$, "<="); }
	| MAI_OP { strcpy($$, ">="); }
	;

operacion_igualdad:
	  operacion_relacional { $$ = $1; }
	| operacion_igualdad IGUAL_OP operacion_relacional { $$ = operacion($1, $3, "=="); }
	| operacion_igualdad DIST_OP operacion_relacional { $$ = operacion($1, $3, "!="); }
	;

operacion_logica_conj:
	  operacion_igualdad { $$ = $1; }
	| operacion_logica_conj CONJ_OP operacion_igualdad { $$ = operacion($1, $3, "&&"); }
	;

operacion_logica_disy:
	  operacion_logica_conj { $$ = $1; }
	| operacion_logica_disy DISY_OP operacion_logica_conj { $$ = operacion($1, $3, "||"); }
	;

operacion_cond:
	  operacion_logica_disy { $$ = $1; }
	| operacion_logica_disy ENTONCES expresion DOS_PUNTOS operacion_cond { $$ = condicional($1, $3, $5); }
	;

operacion_asignacion:
	  operacion_cond { $$ = $1; }
	| expresion_variable operador_asignacion operacion_asignacion { $$ = operacion($1, $3, $2); }
	;

operador_asignacion:
	  ASIGNACION { strcpy($$, "="); }
	| MULTI_ASIGNACION { strcpy($$, "*="); }
	| DIVIS_ASIGNACION { strcpy($$, "/="); }
	| SUMA_ASIGNACION { strcpy($$, "+="); }
	| RESTA_ASIGNACION { strcpy($$, "-="); }
	;

expresion:
	operacion_asignacion { $$ = $1; }
	;

bloque:
	  llaves { $$ = bloque($1); }
	| bloque_condicional { $$ = $1; }
	| bloque_ciclo { $$ = $1; }
	| bloque_retorno { $$ = $1; }
	| bloque_imprimir { $$ = $1; }
	| expresion  { $$ = instruccion($1); }
	| LINEA_NUEVA { $$ = vacio(); }
	;

llaves:
	  LLAVE_ABIERTA LLAVE_CERRADA { $$ = listaInstrucciones(NULL); }
	| LLAVE_ABIERTA lista_instrucciones LLAVE_CERRADA { $$ = $2; }
	;

lista_instrucciones:
	  bloque { $$ = (*programa = listaInstrucciones($1)); }
	| lista_instrucciones bloque { $$ = (*programa = agregarInstruccion($1, $2)); }
	;

bloque_condicional:
	  SI PAREN_ABRE expresion PAREN_CIERRA llaves { $$ = si($3, $5, NULL); }
	| SI PAREN_ABRE expresion PAREN_CIERRA llaves SINO llaves { $$ = si($3, $5, $7); }
	;

bloque_ciclo:
	MIENTRAS PAREN_ABRE expresion PAREN_CIERRA llaves { $$ = mientras($3, $5); }
	;

bloque_retorno:
	RETORNAR PAREN_ABRE expresion PAREN_CIERRA { $$ = retornar($3); }
	;

bloque_imprimir:
	IMPRIMIR PAREN_ABRE expresion PAREN_CIERRA { $$ = imprimir($3); }
	;

%%
void yyerror(NodoLista ** programa, char *msg) {
  printf("%s en la linea %d\n\n", msg, yylineno);
  exit(1);
}
int main() {

	NodoLista * programa;
  int ret = yyparse(&programa);
	if (ret == 1) {
		printf("%s", "Hubo un error en el parsing del programa.");
		return 1;
	} else if (ret == 2) {
		printf("%s", "No hay memoria suficiente");
	}
	
	printf("%s\n", generarCodigoC(programa));
	return 0;
}