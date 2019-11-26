%{
  #include "tokens.h"
  #include <stdio.h>
  #define COLUMNAS ncol+=yyleng;
  #define FILAS nlin++;
  FILE * yyin;
  FILE* yyout;
  int yyleng;
  long nlin=1, ncol=1;
  char c;
%}
%option noyywrap

%%
main     {COLUMNAS;return TOK_MAIN;}
array    {COLUMNAS;return TOK_ARRAY;}
int      {COLUMNAS;return TOK_INT;}
boolean  {COLUMNAS;return TOK_BOOLEAN;}
function {COLUMNAS;return TOK_FUNCTION;}
scanf    {COLUMNAS;return TOK_SCANF;}
printf   {COLUMNAS;return TOK_PRINTF;}
return   {COLUMNAS;return TOK_RETURN;}
if       {COLUMNAS;return TOK_IF;}
else     {COLUMNAS;return TOK_ELSE;}
while    {COLUMNAS;return TOK_WHILE;}
true     {COLUMNAS;return TOK_TRUE;}
false    {COLUMNAS;return TOK_FALSE;}
;        {COLUMNAS;return TOK_PUNTOYCOMA;}
"("      {COLUMNAS;return TOK_PARENTESISIZQUIERDO;}
")"      {COLUMNAS;return TOK_PARENTESISDERECHO;}
"*"      {COLUMNAS;return TOK_ASTERISCO;}
"/"      {COLUMNAS;return TOK_DIVISION;}
"+"      {COLUMNAS;return TOK_MAS;}
"-"      {COLUMNAS;return TOK_MENOS;}
"<="     {COLUMNAS;return TOK_MENORIGUAL;}
">="     {COLUMNAS;return TOK_MAYORIGUAL;}
"<"      {COLUMNAS;return TOK_MENOR;}
">"      {COLUMNAS;return TOK_MAYOR;}
"="      {COLUMNAS;return TOK_IGUAL;}
"!="     {COLUMNAS;return TOK_DISTINTO;}
"&&"     {COLUMNAS;return TOK_AND;}
"||"     {COLUMNAS;return TOK_OR;}
"!"      {COLUMNAS;return TOK_NOT;}
"{"      {COLUMNAS;return TOK_LLAVEIZQUIERDA;}
"}"      {COLUMNAS;return TOK_LLAVEDERECHA;}
"["      {COLUMNAS;return TOK_CORCHETEIZQUIERDO;}
"]"      {COLUMNAS;return TOK_CORCHETEDERECHO;}
","      {COLUMNAS;return TOK_COMA;}
"//".*   {FILAS;}
[a-zA-Z]([a-zA-Z]|[0-9])*  {COLUMNAS;return TOK_IDENTIFICADOR;}
[0-9]+   {COLUMNAS;return TOK_CONSTANTE_ENTERA;}
[\t]     {COLUMNAS;}
[\n]     {ncol=1;FILAS;}
[ ]      {COLUMNAS;}
.        {return TOK_ERROR;}
%%

int yylex();
int main(int argc, char *argv[]){

  int ret;
  yyin = fopen(argv[1], "r");
  yyout = fopen(argv[2], "w");

  while((ret = yylex())!=0){
    if ((ret == TOK_MAIN || ret == TOK_INT || ret == TOK_ARRAY || ret == TOK_IF || ret == TOK_ELSE || ret == TOK_WHILE || ret == TOK_PUNTOYCOMA |ret == TOK_PARENTESISIZQUIERDO || ret == TOK_PARENTESISDERECHO || ret == TOK_ASTERISCO || ret == TOK_MAS ||  ret == TOK_MENORIGUAL || ret == TOK_LLAVEIZQUIERDA || ret == TOK_LLAVEDERECHA || ret == TOK_IDENTIFICADOR || ret == TOK_CONSTANTE_ENTERA || ret == TOK_MENOS || ret == TOK_MENOR || ret == TOK_MAYOR || ret == TOK_IGUAL || ret == TOK_COMA) && yyleng<100){
      fprintf(yyout, "RECONOCIDO %d: %s\n", ret, yytext);
    }
    else if(yyleng>=100){
      fprintf(stderr, "identificador demasiado largo(%s)\n", yytext);
    }
    else if(ret == TOK_ERROR){
      fprintf(stderr, "Error en [lin %ld, col %ld]: simbolo no permitido(%s)\n", nlin, ncol, yytext);
    }
  }
  fclose(yyin);
  fclose(yyout);
  return 0;
}
