#include "tablaSimbolos.h"
#define TAMANIO 256

struct _TablaSimbolos{
	TABLA_HASH * tablaGlobal;
	TABLA_HASH * tablaLocal;
	int ambito;  /*0 si es global y 1 si es local */
};

TablaSimbolos * tabla = NULL;

// int printTablaLocal(FILE* fp){
// 	if(!ts || !ts->tablaLocal || !fp){
// 		return 0;
// 	}
// 	return printTablaSimbolos(fp, ts->tablaLocal);
// }

// int printTablaGlobal(FILE* fp){
// 	if(!ts || !ts->tablaGlobal || !fp)
// 		return 0;
// 	return printTablaSimbolos(fp, ts->tablaGlobal);
// }

// AMBITO getAmbito(){
// 	if(!ts)
// 		return GLOBAL;
// 	return ts->ambito;
// }

// STATUS setAmbito(AMBITO amb){
// 	if(!ts){
// 		ts = (TablaSimbolos*)calloc(1, sizeof(TablaSimbolos));
// 		ts->tablaGlobal = NULL;
// 		ts->tablaLocal = NULL;
// 		ts->ambito = amb;
// 		return OK;
// 	}
// 	if(amb == GLOBAL)
// 		cerrarFuncion();

// 	ts->ambito = amb;
// 	return OK;
// }

// INFO_SIMBOLO* buscar(const char* lexema){
// 	if(!ts){
// 		ts = (TablaSimbolos*)calloc(1, sizeof(TablaSimbolos));
// 		ts->tablaGlobal = NULL;
// 		ts->tablaLocal = NULL;
// 		ts->ambito = GLOBAL;
// 	}
// 	if(ts->ambito == GLOBAL){
// 		return usoGlobal(lexema);
// 	} else {
// 		return usoLocal(lexema);
// 	}
// }

// STATUS insertar(const char* lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param){
// 	if(!ts){
// 		ts = (TablaSimbolos*)calloc(1, sizeof(TablaSimbolos));
// 		ts->tablaGlobal = NULL;
// 		ts->tablaLocal = NULL;
// 		ts->ambito = GLOBAL;
// 	}
// 	if(categ == FUNCION){
// 		return declararFuncion(lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
// 	} else if(categ == PARAMETRO){
// 		return declararLocal(lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
// 	} else {
// 		if(ts->ambito == GLOBAL){
// 			return declararGlobal(lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
// 		} else {
// 			return declararLocal(lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
// 		}
// 	}
// }


// STATUS declararGlobal(const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param) {
// 	if (ts->tablaGlobal == NULL)
// 		ts->tablaGlobal = crear_tabla(TABLESIZE);
// 	if (ts->tablaGlobal)
// 		return insertar_simbolo(ts->tablaGlobal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
// 	else
// 		return ERR;
// }


// STATUS declararLocal(const char* lexema,  CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param) {
// 	if (ts->tablaLocal)
// 		return insertar_simbolo(ts->tablaLocal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
// 	else
// 		return ERR;
// }// 4, 5, 6, 7, 8


// INFO_SIMBOLO *usoGlobal(const char* lexema) {
// 	if (ts->tablaGlobal)
// 		return buscar_simbolo(ts->tablaGlobal, lexema);
// 	else
// 		return NULL;
// }


// INFO_SIMBOLO *usoLocal(const char* lexema) {
// 	if (ts->tablaLocal && ts->tablaGlobal) {
// 		INFO_SIMBOLO * aux = buscar_simbolo(ts->tablaLocal, lexema);
// 		if (aux)
// 			return aux;
// 		else
// 			return buscar_simbolo(ts->tablaGlobal, lexema);
// 	}
// 	else
// 		return NULL;
// }


// STATUS declararFuncion(const char* lexema,  CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param) {
// 	if (ts->tablaGlobal == NULL) {
// 		ts->tablaGlobal = crear_tabla(TABLESIZE);
// 		if (ts->tablaGlobal == NULL)
// 			return ERR;
// 	}

// 	liberar_tabla(ts->tablaLocal);
// 	ts->tablaLocal = crear_tabla(TABLESIZE);
// 	ts->ambito = LOCAL;

// 	if (ts->tablaLocal) {
// 		if (insertar_simbolo(ts->tablaGlobal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param) == ERR) {
// 			liberar_tabla(ts->tablaLocal);
// 			ts->tablaLocal = NULL;
// 			return ERR;
// 		}
// 		return insertar_simbolo(ts->tablaLocal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
// 	} else {
// 		return ERR;
// 	}
// }

// void cerrarFuncion() {
// 	liberar_tabla(ts->tablaLocal);
// 	ts->tablaLocal = NULL;
// }

// void limpiarTablas() {
// 	if(ts){
// 		cerrarFuncion();
// 		liberar_tabla(ts->tablaGlobal);
// 		ts->tablaGlobal = NULL;
// 		free(ts);
// 		ts = NULL;
// 	}
// }


int printTablaGlobal(FILE *f){
    if(!tabla || !tabla->tablaGlobal || !f){
        return -1;
    }
    return printTablaSimbolos(f, tabla->tablaGlobal);
}

int printTablaLocal(FILE *f){
    if(!tabla || !tabla->tablaLocal || !f){
        return -1;
    }
    return printTablaSimbolos(f, tabla->tablaLocal);
}

int getAmbito(){
    if(tabla==NULL){
        return -1;
    }
    return tabla->ambito;
}

int insertarVarGlobal(const char *lex, int cat, int tipo, int clase, int tam, int n_locales, int pos_local, int n_param, int pos_param){
    if(tabla->tablaGlobal==NULL){
        tabla->tablaGlobal = crear_tabla(TAMANIO);
    }
    if(tabla->tablaGlobal){
        return insertar_simbolo(tabla->tablaGlobal, lex, cat, tipo, clase, tam, n_locales, pos_local, n_param, pos_param);
    }
    else{
        return -1;
    }
}

int insertarVarLocal(const char *lex, int cat, int tipo, int clase, int tam, int n_locales, int pos_local, int n_param, int pos_param){
    if(tabla->tablaLocal){
        return insertar_simbolo(tabla->tablaLocal, lex, cat, tipo, clase, tam, n_locales, pos_local, n_param, pos_param);
    }
    else{
        return -1;
    }
}

INFO_SIMBOLO *usoGlobal(const char* lex){
    if(tabla->tablaGlobal==NULL){
        return NULL;
    }
    return buscar_simbolo(tabla->tablaGlobal, lex);
}

INFO_SIMBOLO *usoLocal(const char* lex){
    if(tabla->tablaLocal && tabla->tablaGlobal){
        INFO_SIMBOLO* prueba = buscar_simbolo(tablaLocal, lex);
        if(prueba){
            return prueba;
        }
        else{
            return NULL;
        }
    }
    return NULL;
}

int setAmbito(int ambito){
    if(!tabla){
        tabla=(TablaSimbolos*)calloc(sizeof(tablaSimbolos));
        tabla->tablaGlobal = NULL;
        tabla->tablaLocal = NULL;
        tabla->ambito = ambito;
        return 0;
    }
    if(ambito==0){
        cerrarFuncion();
    }
    return 0;
}

void cerrarFuncion(){
    liberar_tabla(tabla->tablaLocal);
    tabla->tablaLocal=NULL;
}

void limpiarTablaSimbolos(){
    if(tabla){
        cerrarFuncion();
        liberar_tabla(tabla->tablaGlobal);
        tabla->tablaGlobal=NULL;
        free(tabla);
    }
}

INFO_SIMBOLO* buscar(const char *lex){
    if(!tabla)
        return NULL;

    if(tabla->ambito == 0)
        return usoGlobal(lex);
    else if
        return usoLocal(lex);
    else
        return NULL;
}

int declararFuncion(const char *lex, int cat, int tipo, int clase, int tam, int n_locales, int pos_local, int n_param, int pos_param){
    if(tabla->tablaGlobal == NULL){
        tabla->tablaGlobal = crear_tabla(TAMANIO);
    }
    liberar_tabla(tabla->tablaLocal);
    tabla->tablaLocal = crear_tabla(TAMANIO);
    tabla->ambito = 1;

    if(tabla->tablaLocal){
        if(insertar_simbolo(tabla->tablaLocal, lex, cat, tipo, clase, tam, n_locales, pos_local, n_params, pos_param) == -1)){
            liberar_tabla(tabla(tablaLocal);
            tabla->tablaLocal = NULL;
            return -1;
        }
        return insertar_simbolo(tabla->tablaLocal, lex, cat, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
    }
    else
        return -1;
}

int insertar(const char* lex, int cat, int tipo, int clase, int tam, int n_locales, int pos_local, int n_params, int pos_param){
    if(!tabla){
        tabla=(TablaSimbolos*)calloc(sizeof(tablaSimbolos));
        tabla->tablaGlobal = NULL;
        tabla->tablaLocal = NULL;
        tabla->ambito = 0;
    }
    if(cat == 0){ /*es una variable */
        if(tabla->ambito == 0){
            return insertarVarGlobal(lex, cat, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
        }
        else{
            return insertarVarLocal(lex, cat, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
        }
    } else if(cat == 1){ /*es un parámetro de una función */
        return insertarVarLocal(lex, cat, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
    } else{ /*es una función */
        declararFuncion(lex, cat, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
    }
}