#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include "cliente.hpp"

// Necesario por unistd.h cuando compila con g++
#define _XOPEN_SOURCE_EXTENDED 1

bool cliente::connected = false;  //Indica si existe una conexión activa
int cliente::sockfd = 0;          //Guarda el descriptor del socket

/**
 * Construye una nueva instancia de cliente a partir de ip y port
 */
cliente::cliente(char* direccion, int puerto)
{
	ip = direccion;
	port = puerto;
}

/**
 * Conecta con el socket TCP/IP
 */
int cliente::conectar()
{
	
	struct sockaddr_in cli_addr, serv_addr;

	memset((char*) &serv_addr, 0,sizeof(ip));
	serv_addr.sin_family = PF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(port);
	if ( (sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror("Error al abrir el socket");

		return 1;
	}

	if ( connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 )         {

		perror("Error al conectar con el servidor");
		return 1;
	}
	
	connected = true;
	return 0;
}

/**
 * Envia datos por el socket TCP/IP
 */
void cliente::send(char buffer[], int size)
{
	write(sockfd,buffer,size);
	printf("Enviado!, tx: %u bytes\n", size);
}

/**
 * Cierra la conexion del socket
 */
void cliente::cerrar()
{
	close(sockfd);
}

