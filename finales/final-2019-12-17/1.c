/* Escriba un programa (desde la inicializacion hasta la liberacion de recursos) que reciba paquetes de la forma
   nnn+nn+...+nnnn= (numeros separados por +, seguidos de =) e imprima el resultado de la suma de cada paquete por pantalla.
   Al recibir un paquete vacio debe cerrarse ordenadamente. No considere errores.
*/

#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "netdb.h"
#include "unistd.h"

#define QUEUE_LEN 10
#define LEN_PACKAGE 40
#define IGUAL '='
#define MAS '+'

bool paquete_nulo(char* buffer) {
	return (buffer[0] == IGUAL);
}

int calcular_suma(char* buffer,size_t len_buffer) {
	int suma = 0;
	int inicio = 0;

	while(inicio < len_buffer) {
		int contador = 0;
		int factor = 1;
		char c = buffer[inicio];

		while (c != MAS && c != IGUAL) {
			contador++;
			factor *=10;
			c = buffer[inicio + contador];
		}

		for (int j = 0; j < contador; j++) {
			suma += (atoi(buffer[j]) * factor);
			factor /=10;
		}

		inicio += contador + 1;
	}

	return suma;
}

bool seguir_leyendo(const char* buffer, size_t len) {
	for (size_t i = 0; i < len; i++) {
		if (buffer[i] == IGUAL)
			return false;
	}
	return true;
}

int main() {
	struct addrinfo hints;
	struct addrinfo * results;

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;

	getaddrinfo(0 /*any*/,PUERTO,&hints,&results);

	int sck = socket(results->ai_family,results->ai_socktype,results->ai_protocol);

	//bind and listen
	bind(sck,results->ai_addr,results->ai_addrlen);
	freeaddrinfo(results);
	listen(sck,QUEUE_LEN);

	//accept
	int newsck = accept(sck,NULL,NULL);

	shutdown(sck,SHUT_RDWR); // shutdown del socket aceptador
	close(sck); //cierro el socket aceptador.

	char buffer[LEN_PACKAGE];
	memset(buffer,0,LEN_PACKAGE);

	while (!terminar) {
		size_t recibidos = 0;
		bool keep = true;
		while(keep && recibidos < LEN_PACKAGE) {
			recibidos += recv(newsck,buffer+recibidos,tamanio-recibidos,0);
			keep = seguir_leyendo(buffer,recibidos);
		}

		if(paquete_nulo(buffer)) {
			terminar = true;
		} else {
			int suma = calcular_suma(buffer,LEN_PACKAGE);
			printf("suma: %d\n", suma);
		}

		memset(buffer,0,tamanio);
	}

	shutdown(newsck,SHUT_RDWR); // shutdown del socket cliente
	close(newsck); //cierro el socket cliente.

	return 0;
}