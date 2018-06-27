%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "creacionNodos.h"
	#include "grammar.tab.h" 
%}

%option noyywrap

digito       [0-9]
cadena			\"[^\"]*\"
numero      -?[0-9]+(\.[0-9]+)?
variable  [a-zA-Z]+
lineanueva     \n
salida        ("salir")

%%
"si"			{ return(SI); }
"sino"			{ return(SINO);	}
"retornar"		{ return(RETORNAR); }
"mientras"		{ return(MIENTRAS); }
"imprimir"		{ return(IMPRIMIR); }
"+="			{ return(SUMA_ASIGNACION); }
"-="			{ return(RESTA_ASIGNACION); }
"*="			{ return(MULTI_ASIGNACION); }
"/="			{ return(DIVIS_ASIGNACION); }
"&&"			{ return(CONJ_OP); }
"||"			{ return(DISY_OP); }
"<="			{ return(MEI_OP); }
">="			{ return(MAI_OP); }
"=="			{ return(IGUAL_OP); }
"!="			{ return(DIST_OP); }
("{")			{ return(LLAVE_ABIERTA); }
("}")			{ return(LLAVE_CERRADA); }
","				{ return(COMA); }
":"				{ return(DOS_PUNTOS); }
"="				{ return(ASIGNACION); }
"("				{ return(PAREN_ABRE); }
")"				{ return(PAREN_CIERRA); }
"!"				{ return(NEGACION); }
"-"				{ return(MENOS); }
"+"				{ return(MAS); }
"/"				{ return(DIVIS); }
"*"				{ return(MULTI); }
"%"				{ return(MODULO); }
"<"				{ return(MENOR); }
">"				{ return(MAYOR); }
"?"				{ return(ENTONCES); }
{numero}        { strcpy(yylval.cadena, yytext); return NUMERO; }	
{variable}    	{ strcpy(yylval.cadena, yytext); return VARIABLE; }		
{cadena}		{ strcpy(yylval.cadena, yytext); return CADENA_LITERAL; }
{lineanueva}    { yylineno++; return LINEA_NUEVA; }
.				{ /* ignorar los demas caracteres */ }

%%