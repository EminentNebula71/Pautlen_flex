#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H
#include "tablaHash.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _TablaSimbolos TablaSimbolos;


int printTablaLocal(FILE* fp);
int printTablaGlobal(FILE* fp);
int getAmbito();
int setAmbito(int amb);
INFO_SIMBOLO* buscar(const char* lexema);
int insertar(const char* lexema, int categ, int tipo, int clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
int insertarVarGlobal(const char *lexema, int categ, int tipo, int clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
int insertarVarLocal(const char* lexema,  int categ, int tipo, int clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
INFO_SIMBOLO *usoGlobal(const char* lexema);
INFO_SIMBOLO *usoLocal(const char* lexema);
int declararFuncion(const char* lexema,  int categ, int tipo, int clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
void cerrarFuncion();
void limpiarTablas();

#endif

