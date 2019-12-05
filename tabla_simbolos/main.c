#include <stdio.h>
#include <string.h>
#include "tablaHash.h"
#include "tablaSimbolos.h"

int main(int argc, char *argv[]){
    FILE *entrada = fopen(argv[1], "r");
    FILE *salida = fopen(argv[2], "w");
    char aux[100];
    char aux2[100];
    int num=-1000;
    INFO_SIMBOLO* res;
    int i=0;
    while(fgets(aux2, 100, entrada)!=NULL){
        printf("aux2: %s\n", aux2);
        num=-1000;
        if(sscanf(aux2, "%s %d", aux, &num)){
            if(num==-1000){
                res=buscar(aux);

                if(res==NULL){
                    fprintf(salida, "%s -1\n", aux);
                }
                else{
                    fprintf(salida, "%s %d\n", res->lexema, res->tam);
                }
            }
            else if(num>=0){
                if(insertar(aux, 0, 0, 0, num, 0,0,0,0)==1){
                    fprintf(salida, "-1 %s\n", aux);
                }
                else{
                    fprintf(salida, "%s\n", aux);
                }
            }
            else{
                printf("llega a comprobar el cierre. %s %d\n", aux, num);
                if(strcmp(aux, "cierre")==0 && num==-999){
                    printf("Entra\n");
                    cerrarFuncion();
                    fprintf(salida, "cierre\n");
                }
                else{
                    declararFuncion(aux, 2, 0, 0, num, 0,0,0,0);
                }
            }
        }
        i++;
    }
    return 0;
}