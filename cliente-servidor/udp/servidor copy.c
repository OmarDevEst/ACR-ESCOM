
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <arpa/inet.h>

void *atencionClientes(void *param) {
    int *comm_fd = (int *)param;
    char cadena[100];
    time_t t;
    struct tm * tm;
    char hora[100];
    char * tmp;
    char sendLine[100]= "Usando el puerto 22000\n";
    printf("Llegue");

    while(!strstr (cadena,"exit") && !strstr(sendLine,"exit")){
        bzero(cadena,100);
        t= time(NULL);
        tm = localtime(&t);
        strftime(hora,100,"\n otro usuario (%H:%M)->",tm);
        //read(*comm_fd,cadena,100);
        recv(*comm_fd,cadena,strlen(cadena),0);
        tmp = strcat(hora,cadena);
        printf("%s",tmp);
        if(!strstr(cadena,"exit")){
            strftime(hora,100,"\n yo(%H:%M)->",tm);
            printf("Canal: %d %s", *comm_fd, hora);
            scanf("%s",sendLine);
            tmp = strcat(hora,sendLine);
            //write(*comm_fd,sendLine,strlen(sendLine));
            send(*comm_fd,sendLine,strlen(sendLine),0);
        }
    }
    close(*comm_fd);
    free(comm_fd);
}

int main(void)
{
    int listen_fd;
    struct sockaddr_in servaddr,cli;
    int len = sizeof(cli);
    char sendLine[100]= "Usando el puerto 22000\n";
    char cadena[100];

    listen_fd = socket(AF_INET,SOCK_STREAM,0);
    if(listen_fd     < 0) {
        printf("Error al abrir socket\n");
        exit(-1);
    }

    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr =  inet_addr("127.0.0.1");

    int isBind =bind(listen_fd,(struct  sockaddr*)&servaddr ,sizeof(servaddr));
    if (isBind == -1) {
        printf("No se establecio la conexion con el servidor\n");
        exit(-1);
    }


    listen(listen_fd,4);

    while(1) {
        //strcpy( cadena, "conexion finalizada" );
        //strcpy( sendLine, "conexion finalizada" );
        //printf("ciclo reiniciado");
        int * comm_fd = (int *)malloc(sizeof(int));
        *comm_fd = accept(listen_fd,(struct sockaddr*)&cli,&len);

        printf("-----------------Se establecion coneixon-----------------\n");

        pthread_t id;
        pthread_create(&id, NULL, atencionClientes, comm_fd);    
    }
}