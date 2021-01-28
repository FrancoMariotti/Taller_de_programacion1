/*
 * Implemente un programa C que reciba por línea de comandos 3 parámetros: IP, 
 * PUERTO y ARCHIVO; y que transmita el archivo binario <ARCHIVO>
 * al puerto <PUERTO> de la dirección <IP>, utilizando protocolo TCP/IP.
 * No valide errores.
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


#define IP 1
#define PUERTO 2
#define FILENAME 3

int main(int argc, char const *argv[]) {
	char ip[MAX_IPLEN];
	char puerto[MAX_PUERTOLEN];
	char filename[MAX_FILENAMELEN];

	strncpy(ip,argv[IP],MAX_IPLEN);
	strncpy(puerto,argv[PUERTO],MAX_PUERTOLEN);
	strncpy(filename,argv[FILENAME],MAX_FILENAMELEN);

	struct addrinfo* results;
	struct addrinfo hints;
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_family = AF_INET; //IPv4
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	getaddrinfo(ip,puerto,&hints,&results);

	int sockFd = socket(results->ai_family,results->ai_socktype,results->ai_protocol);
	
	printf("Conectando a:\n");
	printf("ip:%s\n", ip);
	printf("puerto:%s\n", puerto);

	connect(sockFd,results->ai_addr,results->ai_addrlen);
	freeaddrinfo(results);

	printf("Enviando archivo:%s\n", filename);
	FILE* fdr = fopen(filename,"rb");
	char c = 0;

	while (!feof(fdr)) {
		c = fgetc(fdr);
		send(sockFd,&c,sizeof(char),MSG_NOSIGNAL);
	} 

	fclose(fdr);
	shutdown(SHUT_RDWR);
	close(sockFd);
	return 0;
}