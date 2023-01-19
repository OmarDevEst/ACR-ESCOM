#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<unistd.h>
#include<stdlib.h>
#include <arpa/inet.h>

int main(void)
{
    char cadena[100];
    int sockfd;
    struct sockaddr_in servaddr,cli;
    time_t t;
    struct tm * tm;
    char hora[100];
    char * tmp;
    char sendLine[100]= "Usando el puerto 22000\n";

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }

    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port= htons(22000);

    int aux = connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(aux !=0){
        printf("connection with the server failed...\n");
        exit(0);
    }

    printf("-----------------Se inicio el chat-----------------\n");


    while(!strstr(cadena,"exit") && !strstr(sendLine,"exit")){
                bzero(cadena,100);
        t= time(NULL);
        tm = localtime(&t);
        strftime(hora,100,"\n yo (%H:%M)->",tm);
        printf("%s",hora);
        scanf("%s",sendLine);
        tmp=strcat(hora,sendLine);
        //write(sockfd,sendLine,strlen(sendLine)+1);
        send(sockfd,sendLine,strlen(sendLine),0);
        if(!strstr(cadena,"exit")){
            strftime(hora,100,"\n Cliente(%H:%M)->",tm);
            //read(sockfd,cadena,100);
            recv(sockfd,cadena,strlen(cadena),0);
            tmp=strcat(hora,cadena);
            printf("%s",tmp);
        }
    }
    exit(0);



}