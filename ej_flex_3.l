%{
  #include "tokens.h"
  #include <stdio.h>
%}
%option noyywrap

%%
main  {return TOK_MAIN;}
array  {return TOK_ARRAY;}
int  {return TOK_INT;}
if  {return TOK_IF;}
else  {return TOK_ELSE;}
while  {return TOK_WHILE;}
;  {return TOK_PUNTOYCOMA;}
"("  {return TOK_PARENTESISIZQUIERDO;}
")"  {return TOK_PARENTESISDERECHO;}
"*"  {return TOK_ASTERISCO;}
"+"  {return TOK_MAS;}
"<="  {return TOK_MENORIGUAL;}
"{"  {return TOK_LLAVEIZQUIERDA;}
"}"  {return TOK_LLAVEDERECHA;}
[a-zA-Z]([a-zA-Z]|[0-9])*  {return TOK_IDENTIFICADOR;}
%%

int yylex();
int main(int argc, char *argv[]){
  extern FILE * yyin;
  extern FILE* yyout;
  extern int yyleng;
  extern long nlin, ncol;
  int ret;
  yyin = fopen(argv[1], "r");
  yyout = fopen("salida.txt", "w");

  while((ret = yylex())!=0){
    if (ret == TOK_MAIN || ret == TOK_INT || ret == TOK_ARRAY || ret == TOK_IF || ret == TOK_ELSE || ret == TOK_WHILE || ret == TOK_PUNTOYCOMA |ret == TOK_PARENTESISIZQUIERDO || ret == TOK_PARENTESISDERECHO || ret == TOK_ASTERISCO || ret == TOK_MAS ||  ret == TOK_MENORIGUAL || ret == TOK_LLAVEIZQUIERDA || ret == TOK_LLAVEDERECHA || ret == TOK_IDENTIFICADOR){
      fprintf(yyout, "RECONOCIDO %d: %s\n", ret, yytext);
    }
    else{
      fprintf(yyout, "ERROR\n");
    }
  }
  fclose(yyin);
  fclose(yyout);
  return 0;
}
