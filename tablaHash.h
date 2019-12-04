#ifndef TABLAHASH_H
#define TABLAHASH_H

#include "generacion.h"

/**************** CONSTANTES ****************/

#define HASH_INI 5381
#define HASH_FACTOR 33


/**************** DECLARACIONES DE TIPOS ****************/

/* Información de un símbolo */
typedef struct {
    char *lexema;           /* identificador */
    CATEGORIA categoria;    /* categoría { VARIABLE, PARAMETRO, FUNCION } */
    TIPO tipo;              /* tipo { ENTERO, BOOLEANO } */
    CLASE clase;            /* clase { ESCALAR, VECTOR } */
    int tam;                /* tamaño de un vector */
    int n_locales;          /* numero de variables locales */
    int pos_local;          /* posicion de variable local */
    int n_param;            /* numero de parametros */
    int pos_param;          /* posicion del parametro */
    /*int adicional1;     valor si escalar, longitud si vector, número de parámetros si función */
    /*int adicional2;     posición en llamada a función si parámetro, posición de declaración si variable local de función, número de variables locales si función */
} INFO_SIMBOLO;

/* Nodo de la tabla hash */
typedef struct nodo_hash {
    INFO_SIMBOLO *info;      /* información del símbolo */
    struct nodo_hash *siguiente;    /* puntero al siguiente nodo (encadenamiento si colisión en misma celda) */
} NODO_HASH;

/* Tabla hash */
typedef struct {
    int tam;            /* tamaño de la tabla hash */
    NODO_HASH **tabla;  /* tabla en sí (array de tam punteros a nodo) */
} TABLA_HASH;


/**************** FUNCIONES ****************/

int printTablaSimbolos(FILE* fp, const TABLA_HASH *th);
int printSimbolo(FILE* fp, INFO_SIMBOLO* info);
INFO_SIMBOLO *crear_info_simbolo(const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
void liberar_info_simbolo(INFO_SIMBOLO *is);
NODO_HASH *crear_nodo(INFO_SIMBOLO *is);
void liberar_nodo(NODO_HASH *nh);
TABLA_HASH *crear_tabla(int tam);
void liberar_tabla(TABLA_HASH *th);
unsigned long hash(const char *str);
INFO_SIMBOLO *buscar_simbolo(const TABLA_HASH *th, const char *lexema);
STATUS insertar_simbolo(TABLA_HASH *th, const char *lexema, CATEGORIA categ, TIPO tipo, CLASE clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
void borrar_simbolo(TABLA_HASH *th, const char *lexema);

#endif