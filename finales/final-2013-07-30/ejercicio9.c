/*

Escriba un pequeño programa que, sin validar errores, 
acepte una única conexión TCP en el puerto 1972 y 
reciba paquetes de no mas de 600 bytes, terminado en 
'0x00'. Cada paquete recibido debe ser devuelto con 
todos sus bits negados. Terminar al recibir un 
paquete nulo.

*/

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif


#include "stdio.h"
#include "string.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "netdb.h"
#include "ctype.h"
#include "unistd.h"
#include "stdbool.h"


//TAMANIO MAXIMO DEL PAQUETE.
#define EXITO 0
#define ERROR 1
#define NULO 0x00
#define TAMANIO_BUFFER 600
#define IP "127.0.0.1"
#define PUERTO "1972"

void enviar(int fd,char* buffer,int lenBuffer) {
    size_t enviado = 0;
    while (enviado < lenBuffer) {
        enviado += send(fd,buffer + enviado, lenBuffer - enviado,MSG_NOSIGNAL);
    }
    
}

bool seguir_recibiendo(char* buffer, int lenBuffer) {
    for (int i = 0; i < lenBuffer; i++) {
        if(buffer[i] == NULO) 
            return false;
    }
    return true;
}

size_t recibir(int fd,char* buffer,int lenBuffer) {
    size_t recibido = 0;
    bool seguirRecibiendo = true;

    while(recibido < lenBuffer && seguirRecibiendo) {
        recibido += recv(fd,buffer + recibido, lenBuffer - recibido,0);
        seguirRecibiendo = seguir_recibiendo(buffer,lenBuffer);
    }

    return recibido;
}

void negar_bits(char* buffer,int lenBuffer) {
    for (int i = 0; i < lenBuffer; i++) {
        buffer[i] = ~buffer[i];
    }
}

int main(int argc, char const *argv[]) {
    printf("Programa Servidor Simple\n");
    int fdsck = socket(AF_INET,SOCK_STREAM,0);

    struct addrinfo hints;
    memset(&hints,0,sizeof(struct addrinfo));
    
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo* results;
    int status = getaddrinfo(IP,PUERTO,&hints,&results);

    if(status != 0) {
        perror("error al buscar direccion");
        return ERROR;
    }

    bind(fdsck,results->ai_addr,results->ai_addrlen);
    freeaddrinfo(results);
    listen(fdsck,10);
    printf("escuchando en el puerto: %s\n",PUERTO);

    int cliente = accept(fdsck,NULL,NULL);
    printf("Cliente Aceptado.\n");
    //printf("Numero:%d, Negado: %d\n",i,negado);
    char buffer[TAMANIO_BUFFER];
    memset(buffer,0,TAMANIO_BUFFER);

    //para recibir el mensaje sabemos que 
    //debemos parar de recibir al detectar un 0x00
    bool finalizar = false;
    size_t bytesRecibidos = 0;
    while(!finalizar) {
        bytesRecibidos = recibir(cliente,buffer,TAMANIO_BUFFER);
        if(buffer[0] == NULO && bytesRecibidos == 1) {
            finalizar = true;
        } else {
            negar_bits(buffer,bytesRecibidos);
            enviar(cliente,buffer,bytesRecibidos);
        }
    }

    shutdown(cliente,SHUT_RDWR);
    shutdown(fdsck,SHUT_RDWR);
    close(cliente);
    close(fdsck);
    return EXITO;
}
