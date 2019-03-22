#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "framer.hpp"
#include "cliente.hpp"
#include "golay24.h"
#include "cli.hpp"

char framer::csp_header[4] = { 0, 0, 0, 0};

framer::framer()
{
	// Al crear la clase se inicializa el array del csp_header
	new_csp_header( 10, 1, 0, 8);
}

void framer::hexdump(char str[], int size = 0)
{
	int largo = (size == 0 ) ? (sizeof(str)): (size+1);
    for (int num = 0; num < largo; num++){
        printf("0x%x ",str[num] & 0xff);
    }
}

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
	printf("header: %x, 1: 0x%x, 2: 0x%x, 3: 0x%x, 4: 0x%x\n", csp_header, csp_header[0], csp_header[1], csp_header[2], csp_header[3]);
}

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
