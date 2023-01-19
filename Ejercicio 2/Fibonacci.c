/*============================================================================
   Description :The Fibonacci sequence
  ============================================================================ */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct numero { 
    int numero;
    int secuencia[100];
    int tam;
    int id;
};


void* runn(void *param)
{

     struct numero * v = malloc(sizeof(struct numero));
    *v = *((struct numero *)param);
    

    int x=0;
    int y=1;
    v->tam=2;
    for (int i=0;i<=100;i++) v->secuencia[i]=0;
    v->secuencia[0]=0;
    v->secuencia[1]=1;
    
    for (int i=2;i<=100;i++)
    {
        if (v->secuencia[i] <= v->numero)
        {
            v->secuencia[i]=x+y;
            x=y;
            y=v->secuencia[i];
            v->tam++;
            printf("Secuencia = %d,numero=%d",v->secuencia[i],v->numero);
        }
        if (v->secuencia[i] >= v->numero) break;
    }
    printf("tam=%d",v->tam);
    pthread_exit((void *)v);      
}  

int main(int argc, char *argv[])
{

    if(argc != 2){
        printf("\n Le falto indicar cuantos hilos crear");
        exit(-1);
    }
    //inciamos tantos hilos como se nos indique
    int numh = atoi(argv[1]);
    //Creamos estructura
    pthread_t *id = (pthread_t *)malloc(numh * sizeof(pthread_t));
    struct numero *numeros = (struct numero *)malloc(numh * sizeof(struct numero));;
    struct numero *resultado;
    //llenamos estructura
    for(int i = 0; i < numh ; i++){
    printf("Indique el numero %d:",i+1);
    scanf("%d",&numeros[i].numero);
    numeros[i].id=i;
    }


    for (int i = 0; i < numh; i++)
    {
        pthread_create(id+i, NULL, runn, numeros+i);
    }                          


    for(int i = 0; i < numh; i++)
    {
        pthread_join(id[i], (void**)(&resultado));
        printf("\nEl hilo  %d con el numero %d tiene la siguiente suceccion:\n",(*resultado).id,(*resultado).numero);
        for(int j = 0; j < (*resultado).tam+1;j++){
                printf("%d,",(*resultado).secuencia[j]);
        }
    }                         
 
}                              

            