/*
 * Implemente un programa C que reciba por línea de comandos 3 parámetros: IP, 
 * PUERTO y ARCHIVO; y que transmita el archivo binario <ARCHIVO>
 * al puerto <PUERTO> de la dirección <IP>, utilizando protocolo TCP/IP.
 * No valide errores.
 */

#include "stdlib.h"
#include "netdb.h"
#include "sys/socket.h"
#include "unistd.h"

#define IP 1
#define PORT 2
#define FILENAME 3
#define SIZE_BUFFER 1024

int main(int argc, char* argv[]) {
	const char* ip = argv[IP];
	const char* port = argv[PORT];
	const char* filename = argv[FILENAME];
	FILE* fp;

	struct addrinfo hints;
	struct addrinfo* results;
	memset(&hints,0,sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;

	getaddrinfo(ip,port,&hints,&results);

	int sck = socket(results->ai_family,results->ai_socktype,results->ai_protocols);
	connect(sck,results->ai_addr,results->ai_addrlen);
	fp = fopen(FILE,"rb");

	freeaddrinfo(results);

	size_t enviados = 0;
	size_t leidos = 0;
	char buffer[SIZE_BUFFER];
	memset(buffer,0,SIZE_BUFFER);

	while((leidos = fread(buffer,sizeof(char),SIZE_BUFFER,fp)) > 0) {
		while (enviados < leidos) {
			enviados+= send(sck,buffer+enviados,SIZE_BUFFER-enviados,MSG_NOSIGNAL);
		}
		memset(buffer,0,SIZE_BUFFER);
		enviados = 0;
	}

	shutdown(sck,"SHUT_RDWR");

	fclose(fp);
	close(sck);

	return 0;
}