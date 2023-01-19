#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    //Abrir archivo
    const char* filename = "input.txt";
    int coincidencia = 0,cuantas=0;
    int tam=0,tam2=0,palabras=0;
    FILE* input_file = fopen(filename, "r");
    if (!input_file)
        exit(EXIT_FAILURE);

    //Contamos cuantos caracteres tiene el archivo
    while(1){
        fgetc(input_file);
        if(feof(input_file)){
            break;
        }
        tam++;
    }
    rewind(input_file);
    char caracteres[tam];
    
    //Guardamos en una rreglo
    for(int i=0; i<tam; i++){
        caracteres[i] =fgetc(input_file);
    }
    //Cuenta palabras
    for(int i=0; i<tam; i++){
        if(caracteres[i]==32||caracteres[i]=='\n'||caracteres[i]=='\t'){
            palabras++;
        }
    }
    
    //Pregutnamos busqueda
    printf("Cuantas palabra desea buscar:");
    scanf("%d",&cuantas);
    //Contamos tamaño de la busqueda
    char busqueda[cuantas][tam];
    for(int i=0; i<cuantas; i++){
        printf("Cual palabra desea buscar:");
        scanf("%s",busqueda[i]);
    }
    

    //Buscamos coincidencias
    for(int i=0; i<cuantas; i++){
        tam2=0;
        coincidencia=0;

        for(int j=0; j<tam; j++){
            if(busqueda[i][j]=='\0'){
                break;
            }
            tam2++;
            
        }
        
        for(int j=0; j<tam; j++){
            if(busqueda[i][0]==caracteres[j]){
                int aux=j+1;
                int aux2=1;
                while(busqueda[i][aux2]==caracteres[aux]){
                    aux++;
                    aux2++;
                    if(aux2==tam2){
                        coincidencia++;
                        break;
                    }
                }
            }
        }
        printf("Palabra %s coincidio %d \n",busqueda[i],coincidencia);
    }

    //Imprimos tamaño de archivos y palabras
    printf("Su archivo contiene:%d caracteres y %d palabras\n", tam,palabras);
    //Cerramos archivero
    fclose(input_file);
}