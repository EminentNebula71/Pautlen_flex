#include "../includes/tablaSimbolos.h"
#define TABLESIZE 256

struct _TablaSimbolos{
	TABLA_HASH * tablaSimbolosGlobal;
	TABLA_HASH * tablaSimbolosLocal;
	AMBITO ambito;
};

TablaSimbolos * ts = NULL;

int printTablaLocal(FILE* fp){
	if(!ts || !ts->tablaSimbolosLocal || !fp){
		return 0;
	}
	return printTablaSimbolos(fp, ts->tablaSimbolosLocal);
}

int printTablaGlobal(FILE* fp){
	if(!ts || !ts->tablaSimbolosGlobal || !fp)
		return 0;
	return printTablaSimbolos(fp, ts->tablaSimbolosGlobal);
}

AMBITO getAmbito(){
	if(!ts)
		return GLOBAL;
	return ts->ambito;
}

STATUS setAmbito(AMBITO amb){
	if(!ts){
		ts = (TablaSimbolos*)calloc(1, sizeof(TablaSimbolos));
		ts->tablaSimbolosGlobal = NULL;
		ts->tablaSimbolosLocal = NULL;
		ts->ambito = amb;
		return OK;
	}
	if(amb == GLOBAL)
		cerrarFuncion();

	ts->ambito = amb;
	return OK;
}

INFO_SIMBOLO* buscar(const char* lexema){
	if(!ts){
		ts = (TablaSimbolos*)calloc(1, sizeof(TablaSimbolos));
		ts->tablaSimbolosGlobal = NULL;
		ts->tablaSimbolosLocal = NULL;
		ts->ambito = GLOBAL;
	}
	if(ts->ambito == GLOBAL){
		return usoGlobal(lexema);
	} else {
		return usoLocal(lexema);
	}
}

STATUS insertar(const char* lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param){
	if(!ts){
		ts = (TablaSimbolos*)calloc(1, sizeof(TablaSimbolos));
		ts->tablaSimbolosGlobal = NULL;
		ts->tablaSimbolosLocal = NULL;
		ts->ambito = GLOBAL;
	}
	if(categ == FUNCION){
		return declararFuncion(lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
	} else if(categ == PARAMETRO){
		return declararLocal(lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
	} else {
		if(ts->ambito == GLOBAL){
			return declararGlobal(lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
		} else {
			return declararLocal(lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
		}
	}
}


STATUS declararGlobal(const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param) {
	if (ts->tablaSimbolosGlobal == NULL)
		ts->tablaSimbolosGlobal = crear_tabla(TABLESIZE);
	if (ts->tablaSimbolosGlobal)
		return insertar_simbolo(ts->tablaSimbolosGlobal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
	else
		return ERR;
}


STATUS declararLocal(const char* lexema,  CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param) {
	if (ts->tablaSimbolosLocal)
		return insertar_simbolo(ts->tablaSimbolosLocal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
	else
		return ERR;
}// 4, 5, 6, 7, 8


INFO_SIMBOLO *usoGlobal(const char* lexema) {
	if (ts->tablaSimbolosGlobal)
		return buscar_simbolo(ts->tablaSimbolosGlobal, lexema);
	else
		return NULL;
}


INFO_SIMBOLO *usoLocal(const char* lexema) {
	if (ts->tablaSimbolosLocal && ts->tablaSimbolosGlobal) {
		INFO_SIMBOLO * aux = buscar_simbolo(ts->tablaSimbolosLocal, lexema);
		if (aux)
			return aux;
		else
			return buscar_simbolo(ts->tablaSimbolosGlobal, lexema);
	}
	else
		return NULL;
}


STATUS declararFuncion(const char* lexema,  CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param) {
	if (ts->tablaSimbolosGlobal == NULL) {
		ts->tablaSimbolosGlobal = crear_tabla(TABLESIZE);
		if (ts->tablaSimbolosGlobal == NULL)
			return ERR;
	}

	liberar_tabla(ts->tablaSimbolosLocal);
	ts->tablaSimbolosLocal = crear_tabla(TABLESIZE);
	ts->ambito = LOCAL;

	if (ts->tablaSimbolosLocal) {
		if (insertar_simbolo(ts->tablaSimbolosGlobal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param) == ERR) {
			liberar_tabla(ts->tablaSimbolosLocal);
			ts->tablaSimbolosLocal = NULL;
			return ERR;
		}
		return insertar_simbolo(ts->tablaSimbolosLocal, lexema, categ, tipo, clase, tam, n_locales, pos_local, n_params, pos_param);
	} else {
		return ERR;
	}
}

void cerrarFuncion() {
	liberar_tabla(ts->tablaSimbolosLocal);
	ts->tablaSimbolosLocal = NULL;
}

void limpiarTablas() {
	if(ts){
		cerrarFuncion();
		liberar_tabla(ts->tablaSimbolosGlobal);
		ts->tablaSimbolosGlobal = NULL;
		free(ts);
		ts = NULL;
	}
}