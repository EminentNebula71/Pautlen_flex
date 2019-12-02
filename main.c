#include <stdio.h>
#include "alfa.tab.h"

extern FILE * yyin;
extern FILE * yyout;
int yylex();

int main(int argc, char *argv[]){

  yyin = fopen(argv[1], "r");
  yyout = fopen(argv[2], "w");

//   fclose(yyin);
//   fclose(yyout);

  yyparse();
  return 0;
}