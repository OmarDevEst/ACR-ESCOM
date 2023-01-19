#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct nodo {
    int i;
    char *cars;
};

void *holaMundo(void *param){
    //int v = *((int *)param);
    struct nodo v = *((struct nodo *)param);
	printf("\nHola del ID %ld",pthread_self());
   	printf(",Hilo  numero - %d \n",v.i);
   	// pthread_exit();
	return NULL;
}

int main(int argc, char *argv[])
{
	/*if(argc != 2){
	    printf("\nLe falto indicar cuantos hilos crear");
	    exit(-1);
	}*/
	
	// Paso 1: Crear hilos
	// int numh = atoi(argv[1]);
	int numh = 5;
	pthread_t id[numh];
	int num[numh];
	int crecall;
	struct nodo array[numh];
	
	for(int i = 0; i < numh; i++){
	    //num[i] = i;
	    array[i].i = i;
		array[i].cars=(char*)malloc((10)*sizeof(char));
		if(array[i].cars==NULL)
		{
		printf("Error al generar arreglo dinamico");
		exit(0);	
		}	
	    strcpy(array[i].cars, "Hola");
	    //pthread_create(&id[i], NULL, holaMundo, &num[i]);
		array[i].i=i;
	    crecall=pthread_create(&id[i], NULL, holaMundo, &array[i]);
		 if (crecall) {
            printf("ERORR; return code from pthread_create() is %d\n", crecall);
            exit(EXIT_FAILURE);
        }
	}
	
	int ret;
	for(int i = 0; i < numh; i++){
		void *retornovalor;
	       ret = pthread_join(id[i], &retornovalor);
		   
		    if (retornovalor == PTHREAD_CANCELED)
            printf("El hilo fue cancelado - ");
        	else
            printf("Hilo numero: %d - ",array[i].i);

		    switch (ret) {
				case 0:
					printf("Hilo inicado Exitosamente\n");
					break;
				case EDEADLK:
					printf("Bloqueo detectado\n");
					break;
				case EINVAL:
					printf("El hilo no se pudo inicar\n");
					break;
				case ESRCH:
					printf("Sin valor de id \n");
					break;
				default:
					printf("Error ocurrido al iniciar el hilo\n");
        }
	}

 	pthread_exit(NULL);
}