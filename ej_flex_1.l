%{
  #include "tokens.h"
  #include <stdio.h>
%}

%%
main  fprintf(s, "RECONOCIDO 100: main");
array  fprintf(s, "RECONOCIDO 103: array");
int  fprintf(s, "RECONOCIDO 101: int");
if  fprintf(s, "RECONOCIDO 105: if");
else  fprintf(s, "RECONOCIDO 106: else");
while  fprintf(s, "RECONOCIDO 107: while");
%%
main(int argc, char *argv[]){
  FILE * e, *s;
  e = fopen(argv[1]);
  s = fopen(argv[2]);
  yylex();
}
