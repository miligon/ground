#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "framer.hpp"
#include "cliente.hpp"
#include "golay24.h"
#include "cli.hpp"

// Variable estática que tiene el valor del header de CSP
char framer::csp_header[4] = { 0, 0, 0, 0};

framer::framer()
{
	// Al crear la clase se inicializa el array del csp_header
	new_csp_header( 10, 1, 0, 8);
}

/**
 * Realiza un hexdump del array de bytes que se le pase por parámetro
 */
void framer::hexdump(char str[], int size = 0)
{
	int largo = (size == 0 ) ? (sizeof(str)): (size+1);
    for (int num = 0; num < largo; num++){
        printf("0x%x ",str[num] & 0xff);
    }
}

/**
 * Cambia el valor de csp_header.
 * Requiere la especificacion de los puertos de origen  y destino asi como de los puertos de origen y destino
 */
void framer::new_csp_header(char src, char dest, char p_src, char p_dest)
{
	// Priority: 2 bits
	// Source: 5 bits
	// Destination: 5 bits
	// Destination port: 6 bits
	// Source port: 6 bits
	// Reserved: 4 bits
	// HMAC: 1 bit
	// XTEA: 1 bit
	// RDP: 1 bit
	// CRC: 1 bit
		
	uint32_t header = 0;
	header += (3 << 30);     // Prioridad
	header += ((src & 0x1F) << 25);   
	header += ((dest & 0x1F) << 20);  
	header += ((p_dest & 0x3F) << 14);
	header += ((p_src & 0x3F) << 8);
	
	csp_header[0]=(char)(header >> 24) & (0xFF);
	csp_header[1]=(char)(header >> 16) & (0xFF);
	csp_header[2]=(char)(header >> 8) & (0xFF);
	csp_header[3]=(char)(header) & (0xFF);
	printf("Nuevo header de CSP:\n Byte 1: 0x%x\n Byte 2: 0x%x\n Byte 3: 0x%x\n Byte 4: 0x%x\n", (char)csp_header[0], (char)csp_header[1], (char)csp_header[2], (char)csp_header[3]);
}

/**
 * En capsula los datos en un frame de ASM+Golay.
 * Se pasa como parametro buffer[] y la salida es datos[]
 */
void framer::crear(char datos[], char buffer[250], int size = 0)
{
	//93 0B 51 DE
	char preambulo[84];
	char golay[3];
	char csp[4];
	char* frame;
	char postambulo[30];
	
	long payload_len = (size > 0) ? size : strlen(buffer); // CSP HEADER + DATA
	
	// 50 veces 0xAA
	memset(preambulo, 0, 30);
	memset(preambulo+30, 0xAA, 50);
	memset(postambulo, 0, 30);
	
	//93 0B 51 DE
	preambulo[80] = 0x93;
	preambulo[81] = 0x0B;
	preambulo[82] = 0x51;
	preambulo[83] = 0xDE;
	
	// 3 bytes para indicar longitud codificado en Golay
	uint32_t len = (uint32_t)(payload_len + 4);
	encode_golay24(&len);
	golay[0]=(char)(len >> 16) & (0xFF);
	golay[1]=(char)(len >> 8) & (0xFF);
	golay[2]=(char)(len) & (0xFF);	
	printf("Golay: %x, 1: %x, 2: %x, 3: %x\n", len, golay[0], golay[1], golay[2]);
	
	printf("***********************\n");
	frame = (char *) malloc(121 + payload_len);
	
	memcpy(frame, preambulo, 84);
	memcpy(frame + 84, golay, 3);
	memcpy(frame + 87, csp_header, 4);
	memcpy(frame + 91, buffer, payload_len);
	memcpy(frame + 91 + payload_len, postambulo, 30);
	hexdump(frame, 121 + payload_len);
	
	memcpy(datos, frame,121 + strlen(buffer)); 
	printf("***********************\n");
}

/**
 * Envia un comando predefinido a travez del socket TCP/IP
 */
void framer::send_comando(int comando, bool send = true)
{
	cliente socket("127.0.0.1", 2500);
	cli interfaz;
	
	char* buffer;
	int size = 121;
	
	if ( !cliente::connected && send)
	{
		socket.conectar();
	}
	
	if ( cliente::connected || !send)
	{
		switch(comando)
		{
			case 1:
				size += 5;
				buffer = (char *) malloc(size);
				crear(buffer, command_test, 5);
				break;
			case 2:
				size += strlen(command_1);
				buffer = (char *) malloc(size);
				crear(buffer, command_1, strlen(command_1));
				break;
			case 3:
				size += strlen(command_2);
				buffer = (char *) malloc(size);
				crear(buffer, command_2, strlen(command_2));
				break;
			case 4:
				size += strlen(command_3);
				buffer = (char *) malloc(size);
				crear(buffer, command_3, strlen(command_3));
				break;
			case 5:
				size += strlen(command_4);
				buffer = (char *) malloc(size);
				crear(buffer, command_4, strlen(command_4));
				break;
			case 6:
				size += strlen(command_5);
				buffer = (char *) malloc(size);
				crear(buffer, command_5, strlen(command_5));
				break;
			case 7:
				size += strlen(command_6);
				buffer = (char *) malloc(size);
				crear(buffer, command_6, strlen(command_6));
				break;
			case 8:
				size += strlen(command_7);
				buffer = (char *) malloc(size);
				crear(buffer, command_7, strlen(command_7));
				break;
			case 9:
				size += strlen(command_8);
				buffer = (char *) malloc(size);
				crear(buffer, command_8, strlen(command_8));
				break;
			case 10:
				size += strlen(command_9);
				buffer = (char *) malloc(size);
				crear(buffer, command_9, strlen(command_9));
				break;
			case 11:
				size += strlen(command_10);
				buffer = (char *) malloc(size);
				crear(buffer, command_10, strlen(command_10));
				break;
			case 12:
				size += strlen(command_11);
				buffer = (char *) malloc(size);
				crear(buffer, command_11, strlen(command_11));
				break;
			case 13:
				size += strlen(command_12);
				buffer = (char *) malloc(size);
				crear(buffer, command_12, strlen(command_12));
				break;
			case 14:
				size += strlen(command_13);
				buffer = (char *) malloc(size);
				crear(buffer, command_13, strlen(command_13));
				break;
			case 15:
				size += strlen(command_14);
				buffer = (char *) malloc(size);
				crear(buffer, command_14, strlen(command_14));
				break;
			case 16:
				size += strlen(command_15);
				buffer = (char *) malloc(size);
				crear(buffer, command_15, strlen(command_15));
				break;
		}
		if ( send )
		{
			socket.send(buffer,size);
		}
	}
	else
	{
		interfaz.format(31);
		printf("Error de conexión TCP/IP con GNURADIO!\n");
		interfaz.format(31,false,false,true);
	}
}

/**
 * Encapsula y envía un texto a travez de TCP/IP.
 */
void framer::send_text(char text[], bool send = true)
{
	cliente socket("127.0.0.1", 2500);
	cli interfaz;
	
	char* buffer;
	int size = 121;
	
	if ( !cliente::connected && send)
	{
		socket.conectar();
	}
	
	if ( cliente::connected || !send )
	{
		size += strlen(text);
		buffer = (char *) malloc(size);
		crear(buffer, text, strlen(text));
		if ( send )
		{
			socket.send(buffer,size);
		}
	}
	else
	{
		interfaz.format(31);
		printf("Error de conexión TCP/IP con GNURADIO!\n");
		interfaz.format(31,false,false,true);
	}
}
