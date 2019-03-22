#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "golay24.h"
#include "cliente.hpp"
#include "framer.hpp"
#include "cli.hpp"

int main()
{
	char buff_in[cli::MAX_INPUT];
	char* data;
	int size = 0;
	
	framer frame;
	cli interfaz;
	
	//cliente gnu("127.0.0.1",2500);
	
	//gnu.conectar();
	
	interfaz.run();/*
	//capturar_string(buff_in);
	capturar_hex(buff_in);
	//comandos(buff_in, menu());
	size = 121 + strlen(buff_in);
	printf("Cadena: %s\nLongitud: %u\n", buff_in, strlen(buff_in));
	
	data = (char *) malloc(size);
	frame.crear(data, buff_in);
	
	printf("Frame: ");
	frame.hexdump(data,size);
	printf("\n");
	
	gnu.send(data, size);
	gnu.cerrar();*/
	
	
	return 0;
}
