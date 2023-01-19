#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char busqueda[3][10];
int cuantas;

struct nodo { 
    char nombre_archivo[10];
    int posicion,caracteres,palabras;
    int concurrencias[3];
    
};

void* OpenFile(void* param){
    struct nodo v = *((struct nodo *)param);
    int tam=0,tam2=0,palabras=0,coincidencia=0;
    const char* filename = v.nombre_archivo;
    FILE* input_file = fopen(filename, "r");
    if (!input_file)
        exit(EXIT_FAILURE);

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
        v.caracteres=tam;
        printf("El archivo %d contiene %d caracteres,%d palabras y encontro la palabra %s un total de %d\n",v.posicion,tam,palabras,busqueda[i],coincidencia);
    }



    pthread_exit(NULL);
}

void main(int argc, char ** argv){
    
    int cantxt;

    if(argc != 2){
        printf("\n Le falto indicar cuantos hilos crear");
        exit(-1);
    }
    // paso 1 : crear los hilos
    int numh = atoi(argv[1]);
    pthread_t id[numh];
    int num[numh];

    struct nodo nodos [numh];



    //llenamos el nodo
    printf("Cuantos txt deseas abrir:");
    scanf("%d",&cantxt);
    for(int i = 0; i < cantxt ; i++){
        nodos[i].posicion=i;
        printf("Indica Nombre archivo %d:",i);
        scanf("%s",nodos[i].nombre_archivo);
    }


    //llenamos Palabras
    printf("Cuantas palabra desea buscar:");
    scanf("%d",&cuantas);
    for(int i = 0; i < cuantas ; i++){
        printf("Indica Palabras %d:",i);
        scanf("%s",busqueda[i]);
    }

    for(int i = 0; i < numh ; i++){
        pthread_create(&id[i], NULL, OpenFile, &nodos[i]);
    }

    for(int i = 0; i < numh ; i++){
        pthread_join(id[i], NULL);
    }



   /* for(int i = 0; i < numh ; i++){
        printf("\n\nEl txt %d,contiene %d caracteres y %d palabras,",nodos[i].posicion,nodos[i].caracteres,nodos[i].palabras);
        for(int j = 0; j < cuantas ; j++){
            printf("\nSe repitio la palabra %s un cantidad de %d veces",busqueda[j],nodos[i].concurrencias[j]);
        }
    }*/

}