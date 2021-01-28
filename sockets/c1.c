/*
 * Escriba una pequeña aplicación C/C++ que se conecte al puerto 2000 del
 * equipo 192.168.1.2, transmita la cadena “hola” y se cierre ordenadamente
 * sin esperar respuesta alguna.
 */

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define IP 192.168.1.2
#define PUERTO 2000
#define CADENA "hola"


int main(int argc,char* argv[]) {
	char mensaje[] = CADENA;
	size_t lenmensaje = strlen(mensaje);

	struct addrinfo* results;
	struct addrinfo hints;
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_family = AF_INET; // IPv4
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	getaddrinfo(IP,PUERTO,&hints,&results);

	int sockFd = socket(results->ai_family,results->ai_socktype,0);
	connect(sockFd,results->ai_addr,results->ai_addrlen);
	freeaddrinfo(results);

	//podemos hacer send/recv.
	size_t enviado = 0;
	while (enviado < lenmensaje) {
		send(sockFd,mensaje+enviado,lenmensaje-enviado,MSG_NOSIGNAL);
	}

	shutdown(sockFd,SHUT_RDWR);
	close(sockFd);

	return 0;
}