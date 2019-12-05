#ifndef TABLAHASH_H
#define TABLAHASH_H

//#include "generacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_INI 5381
#define HASH_FACTOR 33

typedef struct {
    char *lexema;           
    int categoria;   /*0 para variable, 1 para parametro y 2 para funcion */    
    int tipo;    /*0 para entero y 1 para booleano */              
    int clase;   /*0 para escalar y 1 para vector */        
    int tam;              
    int n_locales;          
    int pos_local;          
    int n_param;            
    int pos_param;        
} INFO_SIMBOLO;

typedef struct nodo_hash {
    INFO_SIMBOLO *info;      
    struct nodo_hash *siguiente;   
} NODO_HASH;

typedef struct {
    int tam;            
    NODO_HASH **tabla;  
} TABLA_HASH;



int printTablaSimbolos(FILE* fp, const TABLA_HASH *th);
int printSimbolo(FILE* fp, INFO_SIMBOLO* info);
INFO_SIMBOLO *crear_info_simbolo(const char *lexema, int categ, int tipo, int clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);
void liberar_info_simbolo(INFO_SIMBOLO *is);
NODO_HASH *crear_nodo(INFO_SIMBOLO *is);
void liberar_nodo(NODO_HASH *nh);
TABLA_HASH *crear_tabla(int tam);
void liberar_tabla(TABLA_HASH *th);
unsigned long hash(const char *str);
INFO_SIMBOLO *buscar_simbolo(const TABLA_HASH *th, const char *lexema);
int insertar_simbolo(TABLA_HASH *th, const char *lexema, int categ, int tipo, int clase, int tam, int n_locales, int pos_local, int n_params, int pos_param);  /*0 errpr y 1 éxito */
void borrar_simbolo(TABLA_HASH *th, const char *lexema);

#endif