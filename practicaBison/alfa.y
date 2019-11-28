%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);



}%

%union{
  char operador;
  int numero;
}

%token <operador> OP
%token <numero> NUM
%token TOK_PARENTESISIZQUIERDO TOK_PARENTESISDERECHO TOK_ASTERISCO TOK_MAS TOK_MENOS TOK_MENORIGUAL TOK_MENOR TOK_MAYOR TOK_IGUAL TOK_LLAVEIZQUIERDA TOK_LLAVEDERECHA TOK_COMA TOK_PUNTOYCOMA
%token TOK_MAIN TOK_ARRAY TOK_INT TOK_IF TOK_ELSE TOK_WHILE

%left '+' '-' 'o'
%left '*' '/' 'y'
%right MENOSU TOK_NO
%%

int main(){

}

void yyerror(const char* s) {
	fprintf(stderr, "Error: %s\n", s);
	return;
}


%%
