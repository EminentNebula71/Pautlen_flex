%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern FILE* salida;

void yyerror(const char* s) {
	fprintf(stderr, "Error: %s\n", s);
	return;
}


%}

%union{
  char operador;
  int numero;
}

%token <operador> OP
%token <numero> NUM
%token TOK_PARENTESISIZQUIERDO TOK_PARENTESISDERECHO TOK_ASTERISCO TOK_MAS TOK_MENOS TOK_MENORIGUAL TOK_MENOR TOK_MAYOR TOK_IGUAL TOK_LLAVEIZQUIERDA TOK_LLAVEDERECHA TOK_COMA TOK_PUNTOYCOMA TOK_RETURN TOK_DIVISION TOK_AND TOK_OR TOK_TRUE TOK_FALSE
%token TOK_MAIN TOK_ARRAY TOK_INT TOK_IF TOK_ELSE TOK_WHILE

%left TOK_MAS TOK_MENOS TOK_OR
%left TOK_ASTERISCO TOK_DIVISION TOK_AND
%right MENOSU TOK_NOT

%%

general: TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones funciones sentencias TOK_LLAVEDERECHA{fprintf(salida, ";R1:\t<general> ::= main{<declaraciones> <operaciones> <funciones> <sentencias>}\n");}

declaraciones: declaracion {fprintf(salida, ";R2:\t<declaraciones> ::= <declaracion>\n");} |
               declaracion declaraciones {fprintf(salida, ";R3:\t<declaraciones> ::= <declaracion><declaraciones>\n");} ;
      
declaracion: clase identificadores TOK_PUNTOYCOMA {fprintf(salida, ";R4:\t<declaracion> ::= <clase> <identificadores>;\n");}

clase: clase_escalar {fprintf(salida, ";R5:\t<clase> ::= <clase_escalar>\n");} |
       clase_vector {fprintf(salida, ";R6:\t<clase> ::= <clase_vector>\n");} ;

clase_escalar: tipo {fprintf(salida, ";R9:\t<clase_escalar> ::= <tipo>\n");}

tipo: TOK_INT {fprintf(salida, ";R10:\t<tipo> ::= int\n");}  |
      TOK_BOOLEAN {fprintf(salida, ";R11:\t<tipo> ::= boolean\n");} ;

clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO constante_entera TOK_CORCHETEDERECHO {fprintf(salida, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");}

identificadores: identificador {fprintf(salida, ";R18:\t<identificadores> ::=  <identificador> <identificadores>\n");}  |
                 identificador TOK_COMA identificadores {fprintf(salida, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");} ;

funciones: funcion funciones {fprintf(salida, ";R20:\t<funciones> ::= <funcion> <funciones>\n");}  |
          {fprintf(salida, ";R21:\t<funciones> ::= \n");}
            ;

funcion: TOK_FUNCTION tipo identificador TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion sentencias TOK_LLAVEDERECHA {fprintf(salida, ";R22:\t<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ){ <declaraciones_funcion> <sentencias> }\n");}

parametros_funcion: parametro_funcion resto_parametros_funcion {fprintf(salida, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}  |
                    {fprintf(salida, ";R24:\t<parametros_funcion> ::= \n");}
                    ;

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {fprintf(salida, ";R25:\t<resto_parametros_funcion> ::= <parametro_funcion><resto_parametros_funcion>\n");}  |
                          {fprintf(salida, ";R26:\t<resto_parametros_funcion> ::= \n");}
                          ;

parametro_funcion: tipo  identificador {fprintf(salida, ";R27:\t<parametro_funcion> ::= <tipo> <identificador>\n");}

declaraciones_funcion: declaraciones {fprintf(salida, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");}  |
                       {fprintf(salida, ";R29:\t<declaraciones_funcion> ::= \n");}
                       ;

sentencias: sentencia {fprintf(salida, ";R30:\t<sentencias> ::= <sentencia>\n");}  |
            sentencia sentencias {fprintf(salida, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");}  ;

sentencia: sentencia_simple TOK_PUNTOYCOMA {fprintf(salida, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}  |
           bloque {fprintf(salida, ";R33:\t<sentencia> ::= <bloque>\n");}  ;

sentencia_simple: asignacion {fprintf(salida, ";R34:\t<sentencia_simple> ::= <asignacion>\n");}  |
                  lectura {fprintf(salida, ";R35:\t<sentencia_simple> ::= <lectura>\n");}  |
                  escritura {fprintf(salida, ";R36:\t<sentencia_simple> ::= <escritura>\n");}  |
                  retorno_funcion {fprintf(salida, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");}  ;

bloque: condicional {fprintf(salida, ";R40:\t<bloque> ::= <condicional>\n");}  |
        bucle {fprintf(bloque, ";R41:\t<bloque> ::= <bucle>\n");}  ;

asignacion: identificador TOK_IGUAL exp {fprintf(salida, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");}  |
            elemento_vector TOK_IGUAL exp {fprintf(salida, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");}  ;

elemento_vector: identificador TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {fprintf(salida, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");}

condicional: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(salida, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");}  |
             TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {fprintf(salida, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");}  ;

bucle: TOK_WHILE TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA  {fprintf(salida, ";R52:\t<bucle> ::= TOK_WHILE ( <exp> ) { <sentencias> }\n");}

lectura: TOK_SCANF identificador {fprintf(salida, ";R54:\t<lectura> ::= scanf <identificador> \n");}

escritura: TOK_PRINTF exp {fprintf(salida, ";R56:\t<condicional> ::= printf <exp>\n");}
        



retorno_funcion: TOK_RETURN exp {fprintf(salida, ";R61: <retorno_funcion> ::= return <exp>\n");}
exp: exp TOK_MAS exp {fprintf (salida, ";R72: <exp> ::= <exp> + <exp>\n");} |
     exp TOK_MENOS exp {fprintf(salida, ";R73: <exp> ::= <exp> - <exp>\n");} |
     exp TOK_DIVISION exp {fprintf(salida, ";R74: <exp> ::= <exp> / <exp>\n");} |
     exp TOK_ASTERISCO exp {fprintf(salida, ";R75: <exp> ::= <exp> * <exp>\n");} |
     MENOSU exp {fprintf(salida, ";R76: <exp> ::= - <exp>\n");} |
     exp TOK_AND exp {fprintf(salida, ";R77: <exp> ::= <exp> && <exp>\n");} |
     exp TOK_OR exp {fprintf(salida, ";R78: <exp> ::= <exp> || <exp>\n");} |
     TOK_NOT exp {fprintf(salida, ";R79: <exp> ::= ! <exp>\n");} |
     identificador {fprintf(salida, ";R80: <exp> ::= <identificador>\n");} |
     constante {fprintf(salida, ";R81: <exp> ::= <constante>\n");} |
     TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {fprintf(salida, ";R82: <exp> ::= ( <exp> )\n");} |
     TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {fprintf(salida, ";R83: <exp> ::= ( <comparacion> )\n");} |
     elemento_vector {fprintf(salida, ";R85: <exp> ::= <elemento_vector>\n");} |
     identificador TOK_PARENTESISIZQUIERDO lista_expresiones TOK_PARENTESISDERECHO {fprintf(salida, ";R88: <exp> ::= <identificador> (<lista_expresiones>)\n");}
     ;

lista_expresiones: exp resto_lista_expresiones {fprintf(salida, ";R89: <lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");} |
                   {fprintf(salida, ";R90:\t<lista_expresiones> ::= \n");}
                   ;
resto_lista_expresiones: TOK_COMA exp resto_lista_expresiones {fprintf(salida, ";R91: <resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n");} |
                        {fprintf(salida, ";R92:\t<resto_lista_expresiones> ::= \n");}
                        ;
comparacion: exp TOK_IGUAL TOK_IGUAL exp {fprintf(salida, ";R93: <comparacion> ::= <exp> == <exp>\n");} |
             exp TOK_NOT TOK_IGUAL exp {fprintf(salida, ";R94: <comparacion> ::= <exp> != <exp>\n");} |
             exp TOK_MENORIGUAL exp {fprintf(salida, ";R95: <comparacion> ::= <exp> <= <exp>\n");} |
             exp TOK_MAYORIGUAL exp {fprintf(salida, ";R96: <comparacion> ::= <exp> >= <exp>\n");} |
             exp TOK_MENOR exp {fprintf(salida, ";R97: <comparacion> ::= <exp> < <exp>\n");} |
             exp TOK_MAYOR exp {fprintf(salida, ";R98: <comparacion> ::= <exp> > <exp>\n");}
             ;
constante: constante_logica {fprintf(salida, ";R99: <constante> ::= <constante_logica>\n");} |
           constante_entera {fprintf(salida, ";R100: <constante> ::= <constante_entera>\n");}
           ;
constante_logica: TOK_TRUE {fprintf(salida, ";R102: <constante_logica> ::= true\n");} |
                  TOK_FALSE {fprintf(salida, ";R103: <constante_logica> ::= false\n");}
                  ;
constante_entera: numero {fprintf(salida, ";R104: <constante_entera> ::= <numero>\n");}

numero: digito {fprintf(salida, ";R105: <numero> ::= <digito>\n");} |
        numero digito {fprintf(salida, ";R106: <numero> ::= <numero> <digito>\n");}
        ;
identificador: letra {fprintf(salida, ";R108: <identificador> ::= <letra>\n");} |
               letra cola_identificador {fprintf(salida, ";R109: <identificador> ::= <letra> <cola_identificador>\n");}
               ;
               
cola_identificador: alfanumerico {fprintf(salida, ";R110: <cola_identificador> ::= <alfanumerico>\n");} |
                    digito {fprintf(salida, ";R113: <cola_identificador> ::= <digito>\n");}
                    ;
                    
alfanumerico: letra {fprintf(salida, ";R112: <alfanumerico> ::= <letra>\n");} |
              digito {fprintf(salida, ";R113: <alfanumerico> ::= <digito>\n");}
              ;
letra: HACER__ESTO
digito: HACER__ESTO
     
     
%%

int main(){

}
