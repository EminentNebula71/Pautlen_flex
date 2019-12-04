#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H
#include "tablaHash.h"

typedef struct _TablaSimbolos TablaSimbolos;


int printTablaLocal(FILE* fp);
int printTablaGlobal(FILE* fp);
AMBITO getAmbito();
STATUS setAmbito(AMBITO amb);
INFO_SIMBOLO* buscar(const char* lexema);
STATUS insertar(const char* lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
STATUS declararGlobal(const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
STATUS declararLocal(const char* lexema,  CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
INFO_SIMBOLO *usoGlobal(const char* lexema);
INFO_SIMBOLO *usoLocal(const char* lexema);
STATUS declararFuncion(const char* lexema,  CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
void cerrarFuncion();
void limpiarTablas();

#endif