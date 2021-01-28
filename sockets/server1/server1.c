/*
 * Escriba un programa que escuche conexiones TCP en el puerto 3280 y guarde en disco
 * con nombres correlativos (1.html, 2.html , ...) cada uno de los HTML recibidos.
 * <simil>
 * Escriba un programa que escuche conexiones TCP en el puerto 1180 y guarde en disco
 * con nombres correlativos (1.txt, 2.txt, ...) cada una de las páginas HTML recibidas
 * (1 página por conexión).
 */

/*
 * Con la siguiente linea enviamos el contendi de generador.html por la red y luego
 * cierra la conexion a los 0 segundos de llegar al EndOfFile del archivo.
 * netcat -q 0 localhost 3280 -v < generador.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>


#define PUERTO 3280
#define QUEUE_LENGTH 10
#define LEN_BUFFER 20
#define LEN_FILENAME 50

int main(int argc,char* argv[]) {
	int clientFd = 0;
	int id = 0;
	bool finalizar = false;
	char filename[LEN_FILENAME];
	memset(filename,0,LEN_FILENAME);
	char buffer[LEN_BUFFER];
	memset(buffer,0,LEN_BUFFER);

	struct addrinfo* results;
	struct addrinfo hints;
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_family = AF_INET; //IPv4
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;

	getaddrinfo(0/*any, cualquier ip publica que tengamos*/,PUERTO,&hints,&results);

	int sockFd = socket(results.ai_family,results.ai_socktype,0);
	bind(sockFd,results->ai_addr,results->ai_addrlen);
	freeaddrinfo(results);

	listen(sockFd,QUEUE_LENGTH);

	while(!finalizar) {
		clientFd = accept(sockFd,NULL,NULL)
		id++;
		snprintf(filename,LEN_FILENAME,"%d.html",id);
		FILE* newFile = fopen(filename,"w");

		size_t bytes_recibidos = 0;
		while (bytes_recibidos > 0) {
			bytes_recibidos = recv(clientFd,buffer,LEN_BUFFER,0);
			if(bytes_recibidos > 0) {
				fwrite(buffer,sizeof(char),bytes_recibidos,newFile);
			}
		}

		fclose(newFile);


		c = 0;
        printf("Pulse q si no quiere recibir otro archivo: ");
        c = getchar();
        if (c == 'q')
            finalizar = true;
        printf("\n");

		shutdown(clientFd,SHUT_RDWR);
		close(clientFd);
	}
	
	shutdown(sockFd,SHUT_RDWR);
	close(sockFd);
	return 0;
}