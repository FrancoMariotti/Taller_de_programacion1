#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "netdb.h"
#include "sys/socket.h"
#include "ctype.h"
#include "unistd.h"
#include "stdbool.h"


#define EXITO 0
#define ERROR 1
#define DELIMITADORES ",="
#define LONGITUD_MAX_NUMERO 10
#define FIN "FIN"
#define FIN_CADENA '\0'
#define QUEUE_LENGTH 10

bool terminarPrograma(char* paquete) {
    if(strcmp(paquete,FIN) != 0) return false;
    return true;
}

int recibir(int fd,char* buffer,size_t longitud_buffer) {
    size_t bytes_recibidos = 0;
    size_t bytes_recibidos_totales = 0;
    size_t buffer_restante = 0;

    while ((longitud_buffer - bytes_recibidos_totales) != 0) {
        buffer_restante = longitud_buffer - bytes_recibidos_totales;
        bytes_recibidos = recv(fd,buffer + bytes_recibidos_totales,buffer_restante,0);
        if(bytes_recibidos < 0) return ERROR;

        bytes_recibidos_totales += bytes_recibidos;
    }

    return EXITO;
} 

char* recibirPaquete(int fd) {
    u_int32_t longitud_paquete = 0;
    recibir(fd,(char*)&longitud_paquete,4);
    longitud_paquete = ntohl(longitud_paquete);

    int longitud_buffer = longitud_paquete + 1;
    char* buffer = (char*) malloc((sizeof(char)) * longitud_buffer);
    buffer[longitud_buffer - 1] = FIN_CADENA;
    recibir(fd,buffer,longitud_paquete);

    return buffer;
}

int procesarPaquete(char* paquete) {
    size_t longitud_paquete = strlen(paquete);

    int suma = 0;
    char sumando_str[LONGITUD_MAX_NUMERO] = {FIN_CADENA};

    for (int i=0 ; i<longitud_paquete ; i++) {
        if (isdigit(paquete[i])) {
            char digito[] = {paquete[i], FIN_CADENA};
            if(strlen(sumando_str) < LONGITUD_MAX_NUMERO)
                strcat(sumando_str,digito);
        } else if (strchr(DELIMITADORES,paquete[i])) {
            suma += atoi(sumando_str);
            memset(sumando_str,0,LONGITUD_MAX_NUMERO);
        }
    }

    return suma;
} 


int main(int argc, char const *argv[]) {
    if(argc != 3) return ERROR;

    printf("IP:%s\n",argv[1]);
    printf("PUERTO:%s\n",argv[2]);

    int fd = socket(AF_INET,SOCK_STREAM,0);

    if(fd < 0) {
        perror("error al crear socket");
        return ERROR;
    }
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *results;
    int status = 1;
    status = getaddrinfo(argv[1],argv[2],&hints,&results);
    if (status != 0) return ERROR;

    status = bind(fd,results->ai_addr,results->ai_addrlen);
    if (status != 0) return ERROR;

    freeaddrinfo(results);

    status = listen(fd,QUEUE_LENGTH);
    if (status != 0) return ERROR;

    printf("escuchando en el puerto: %s\n",argv[2]);
    
    int fd_cliente = accept(fd,NULL,NULL);
    printf("nuevo cliente aceptado\n");
    bool finalizar = false;

    while(!finalizar) {
        char* paquete = recibirPaquete(fd_cliente);
        printf("paquete recibido:%s\n",paquete);
        int suma = procesarPaquete(paquete);
        printf("Suma:%d\n", suma);
        if (terminarPrograma(paquete)) {
            finalizar = true;
        }

        free(paquete);
    }

    shutdown(fd_cliente,SHUT_RDWR);
    shutdown(fd,SHUT_RDWR);
    close(fd_cliente);
    close(fd);

    return EXITO;
}
