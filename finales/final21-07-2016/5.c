/*	Escriba un programa que , recibiendo por linea de comandos una IP y 
	un PUERTO se conecte al puerto PUERTO del ordenador con ip IP y transmita 
	la cadena "Iniciado".
 	
 	El programa debe terminar cuando reciba "Cerrando".
*/
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>

#define ERROR 1
#define EXITO 0
#define INTERVALO 3

#define TAM_MAX_IP 20
#define TAM_MAX_PORT 20
#define TAM_MAX_BUFFER 50

int main(int argc, char* argv[]) {

	if(argc != 3) {
		perror("Cantidad de parametros incorrecta");
		return ERROR;
	}

	const char mensaje_inicial[] = "Iniciado";
	const char mensaje_fin[] = "Cerrando";

	char ip[TAM_MAX_IP];
	char port[TAM_MAX_PORT];
	char buffer[TAM_MAX_BUFFER];
	memset(buffer,0,TAM_MAX_BUFFER);

	strncpy(ip,argv[1],TAM_MAX_IP);
	strncpy(port,argv[2],TAM_MAX_PORT);

	struct addrinfo *results;
	struct addrinfo hints;
	hints.ai_family = AF_INET; //ipv4
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_flags = 0;

	getaddrinfo(ip,port,&hints,&results);

	int sockFd = socket(results->ai_family,results->ai_socktype,0);

	connect(sockFd,results->ai_addr,results->ai_addrlen);
	freeaddrinfo(results);


	send(sockFd,mensaje_inicial,strlen(mensaje_inicial),MSG_NOSIGNAL);

	bool finalizar = false;
	while (!finalizar) {
		recv(sockFd,buffer,TAM_MAX_BUFFER,0);

		if (strcmp(buffer,mensaje_fin) == 0) {
			finalizar = true;
		} else {
			printf("%s\n", buffer);
			memset(buffer,0,TAM_MAX_BUFFER);
		}

		sleep(INTERVALO);
	}

	shutdown(sockFd,SHUT_RDWR);
	close(sockFd);

	return EXITO;
}