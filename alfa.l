%{
  #include <stdio.h>
  #include "alfa.tab.h"

  #define COLUMNAS ncol+=yyleng;
  #define FILAS nlin++;
  FILE * yyin;
  FILE* yyout;
  int yyleng;
  long nlin=0, ncol=0;
  char c;
%}
%option noyywrap

%%
main     {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_MAIN;}
array    {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_ARRAY;}
int      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_INT;}
boolean  {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_BOOLEAN;}
function {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_FUNCTION;}
scanf    {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_SCANF;}
printf   {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_PRINTF;}
return   {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_RETURN;}
if       {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_IF;}
else     {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_ELSE;}
while    {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_WHILE;}
true     {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_TRUE;}
false    {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_FALSE;}
;        {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_PUNTOYCOMA;}
"("      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_PARENTESISIZQUIERDO;}
")"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_PARENTESISDERECHO;}
"*"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_ASTERISCO;}
"/"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_DIVISION;}
"+"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_MAS;}
"-"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_MENOS;}
"<="     {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_MENORIGUAL;}
">="     {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_MAYORIGUAL;}
"<"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_MENOR;}
">"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_MAYOR;}
"="      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_IGUAL;}
"!="     {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_DISTINTO;}
"&&"     {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_AND;}
"||"     {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_OR;}
"!"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_NOT;}
"{"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_LLAVEIZQUIERDA;}
"}"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_LLAVEDERECHA;}
"["      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_CORCHETEIZQUIERDO;}
"]"      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_CORCHETEDERECHO;}
","      {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_COMA;}
"//".*   {FILAS;}
[a-zA-Z]([a-zA-Z]|[0-9])*  { if(yyleng>100){
                                  fprintf(stderr, "****Error en [lin %ld, col %ld]: identificador demasiado largo\n", nlin, ncol);
                                  return -1;
                              }
                              COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_IDENTIFICADOR;}
[0-9]+   {COLUMNAS;fprintf(yyout, ";D:\t%s\n", yytext);return TOK_CONSTANTE_ENTERA;}
[\t]     {COLUMNAS;}
[\n]     {ncol=1;FILAS;}
[ ]      {COLUMNAS;}
.        {fprintf(stderr, "****Error en [lin %ld, col %ld] simbolo no permitido (%s)\n", nlin, ncol, yytext);
          return -1;}
%%
