#include "tablaSimbolos.h"
#define TAMANIO 256

struct _TablaSimbolos{
	TABLA_HASH * tablaGlobal;
	TABLA_HASH * tablaLocal;
	int ambito;  /*0 si es global y 1 si es local */
};

TablaSimbolos * tabla = NULL;

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
        INFO_SIMBOLO* prueba = buscar_simbolo(tabla->tablaLocal, lex);
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
        tabla=(TablaSimbolos*)calloc(1, sizeof(TablaSimbolos));
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

    if(tabla->ambito == 0){
        return usoGlobal(lex);
    }
    else if(tabla->ambito==1){
        return usoLocal(lex);
    }
    else{
        return NULL;
    }
}

int declararFuncion(const char *lex, int cat, int tipo, int clase, int tam, int n_locales, int pos_local, int n_param, int pos_param){
    if(tabla->tablaGlobal == NULL){
        tabla->tablaGlobal = crear_tabla(TAMANIO);
    }
    liberar_tabla(tabla->tablaLocal);
    tabla->tablaLocal = crear_tabla(TAMANIO);
    tabla->ambito = 1;

    if(tabla->tablaLocal){
        if(insertar_simbolo(tabla->tablaLocal, lex, cat, tipo, clase, tam, n_locales, pos_local, n_param, pos_param) == -1){
            liberar_tabla(tabla->tablaLocal);
            tabla->tablaLocal = NULL;
            return -1;
        }
        return insertar_simbolo(tabla->tablaLocal, lex, cat, tipo, clase, tam, n_locales, pos_local, n_param, pos_param);
    }
    else
        return -1;
}

int insertar(const char* lex, int cat, int tipo, int clase, int tam, int n_locales, int pos_local, int n_param, int pos_param){
    if(!tabla){
        tabla=(TablaSimbolos*)calloc(1, sizeof(TablaSimbolos));
        tabla->tablaGlobal = NULL;
        tabla->tablaLocal = NULL;
        tabla->ambito = 0;
    }
    if(cat == 0){ /*es una variable */
        if(tabla->ambito == 0){
            return insertarVarGlobal(lex, cat, tipo, clase, tam, n_locales, pos_local, n_param, pos_param);
        }
        else{
            return insertarVarLocal(lex, cat, tipo, clase, tam, n_locales, pos_local, n_param, pos_param);
        }
    } else if(cat == 1){ /*es un parámetro de una función */
        return insertarVarLocal(lex, cat, tipo, clase, tam, n_locales, pos_local, n_param, pos_param);
    } else{ /*es una función */
        return declararFuncion(lex, cat, tipo, clase, tam, n_locales, pos_local, n_param, pos_param);
    }
}