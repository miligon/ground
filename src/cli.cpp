#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cli.hpp"
#include "cli.hpp"
#include "framer.hpp"
#include "golay24.h"

cli::cli()
{
	//Nothing here yet!
}

/**
 * Muestra una pausa en la terminal
 */
void cli::pause()
{
	printf("\nPresione una tecla para continuar ...");
	scanf("%");
	limpiar();
}

/**
 * Limpia el buffer de entrada de STDIN
 */
void cli::limpiar()
{
	int ch;
	while ((ch = getchar()) != EOF && ch != '\n') ;
}

/**
 * Captura una string
 */
void cli::capturar_string(char data[246])
{	
	char c= 0;
	int i = 0;
	
	format(33);
	printf("Ingrese el texto a enviar: ");
	while( (c = getchar())!= '\n' && i < 246 )
	{
		data[i] = c;
		putchar( c );
		i++;
	}
	data[i] = 0;
	printf("Cadena: %s\nLongitud: %u\n", data, strlen(data));
}

char cli::hexchar_to_int(char hex)
{
	if ( hex > 0x2F && hex < 0x3A )
	{
		return (hex - 0x30);
	}
	if ( hex > 0x40 && hex < 0x47 )
	{
		return (hex - 0x37);
	}
	return 0;
}

/**
 * Captura una serie de hexadecimales
 */
void cli::capturar_hex(char data[246])
{	
	int c1= 0;
	int c2= 0;
	char num[3];
	int i = 0;
	
	while( i < 246 )
	{
		header();
		format(33);
		printf("Ingrese los bytes a enviar(ingrese ';' para finalizar): \n\n");
		
		for ( int a = 0; a < i; a++)
		{
			if ( i > 0 )
			{
				printf("0x%x ", data[a]);
			}
		}
		
		scanf("%2s", num);		
		limpiar();
		
		if(num[0] == ';')
		{
			break;
		}
		else
		{
			printf("%x, %x\n", hexchar_to_int(num[0]), hexchar_to_int(num[1]));
			data[i] = (hexchar_to_int(num[0]) << 0xF) + hexchar_to_int(num[1]);
		}
		i++;
	}
	
	data[i] = 0;
	printf("Cadena: %s\nLongitud: %u\n", data, strlen(data));
}

/**
 * Muestra un header en la terminal
 */
void cli::header()
{
	system("clear");
	printf("\n");
	
	format(32, true);
	printf("\tAztechSat 1 Radio Interface\n");
	printf("\n");
}

/**
 * Muestra el menu principal y devuelve la seleccion del usuario
 */
int cli::menu()
{
	int opcion = 0;
	header();
	format(32);
	printf("\tSelect an option:\n");
	printf("\n");
	format(32, false, true);
	printf("\t1) Send predifined command\n");
	printf("\t2) Send text\n");
	printf("\t3) Send hex\n");
	printf("\t4) Show frame from predifined command\n");
	printf("\t5) Show frame from text\n");
	printf("\t6) Show frame from hex\n");
	printf("\t7) Calc Golay24\n");
	printf("\t8) Change CSP Header\n");
	printf("\t9) Exit\n");
	printf("\n\n");
	format(32);
	printf("\tOption selected: "); scanf("%u", &opcion);
	limpiar();
	return opcion;
}

/**
 * Muestra el menu de los comandos predefinidos y devuelve el numero del comando elegido
 */
int cli::menu_comandos()
{
	int opcion = 0;
	header();
	format(32);
	printf("\tSelect the command:\n");
	printf("\n");
	format(32, false, true);
	printf("\t1) Beacon UPAEP\n");
	printf("\t2) Comando 2\n");
	printf("\t3) Comando 3\n");
	printf("\t4) Return\n");
	printf("\n\n");
	format(32);
	printf("\tOpcion seleccionada: "); scanf("%u", &opcion);
	limpiar();
	return opcion;
}

/**
 * Cambia el formato del texto de la linea de comando
 */
void cli::format(int fg, bool bold, bool underline, bool reset)
{
/*	
╔══════════╦════════════════════════════════╦═════════════════════════════════════════════════════════════════════════╗
║  Code    ║             Effect             ║                                   Note                                  ║
╠══════════╬════════════════════════════════╬═════════════════════════════════════════════════════════════════════════╣
║ 0        ║  Reset / Normal                ║  all attributes off                                                     ║
║ 1        ║  Bold or increased intensity   ║                                                                         ║
║ 4        ║  Underline                     ║                                                                         ║
║ 30–37    ║  Set foreground color          ║  See color table below                                                  ║
║ 38       ║  Set foreground color          ║  Next arguments are `5;n` or `2;r;g;b`, see below                       ║
║ 40–47    ║  Set background color          ║  See color table below                                                  ║
║ 48       ║  Set background color          ║  Next arguments are `5;n` or `2;r;g;b`, see below                       ║
╚══════════╩════════════════════════════════╩═════════════════════════════════════════════════════════════════════════╝*/

/*
 * Foreground color: 
 * 
 * 30 -> black
 * 31 -> red
 * 32 -> green
 * 33 -> yellow
 * 34 -> blue
 * 35 -> pink
 * 36 -> cyan
 * 37 -> white
 * 
 * Background color:
 * 
 * 40 -> black
 * 41 -> red
 * 42 -> green
 * 43 -> yellow
 * 44 -> blue
 * 45 -> pink
 * 46 -> cyan
 * 47 -> white
 */
	if ( reset )
	{
		printf("\033[0m");
	}
	else
	{
		if ( bold || underline)
		{
			if ( bold )
			{
				printf("\033[1m");
			}
			if ( underline )
			{
				printf("\033[4m");
			}
		}
		else
		{
			printf("\033[0m");
		}
		
		printf("\033[%u;1m", fg);
	}
}

/**
 * Procesa el envio de los comandos predefinidos
 */
void cli::process_commands(bool send = false)
{
	framer frame;
	int a = 0;
	while((a=menu_comandos()) != 4)
	{
		switch(a)
		{
			case 1:
				frame.send_comando(1, send);
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				format(31);
				printf("\n\nOpcion no valida!\n");
				break;
		}
		pause();
	}
}

/**
 * Procesa la captura y el envio de comandos de textos
 */
void cli::process_text(bool send = false)
{
	char buff_in[cli::MAX_INPUT];
	framer frame;
	
	header();
	
	capturar_string(buff_in);
	frame.send_text(buff_in, send);
}

/**
 * Procesa la captura y el envio de comandos de textos
 */
void cli::process_hex(bool send = false)
{
	char buff_in[cli::MAX_INPUT];
	framer frame;
	
	header();
	
	capturar_hex(buff_in);
	frame.send_text(buff_in, send);
}

/**
 * Procesa el calculo de Golay24
 */
void cli::calc_golay()
{
	uint32_t len = 0;
	framer frame;
	
	header();
	format(33);
	printf("\nIngresa la longitud a codificar en Golay24: ");
	scanf("%u", &len);
	limpiar();
	encode_golay24(&len);
	printf("\nResultado: %x\n Byte 1: %x\n Byte 2: %x\n Byte 3: %x\n ", len, (char)(len >> 16) & (0xFF),
																			 (char)(len >> 8) & (0xFF),
																			 (char)(len) & (0xFF));
}

/**
 * Procesa el cambio del CSP HEADER
 */
void cli::set_csp()
{
	char src = 0;
	char dest = 0;
	char p_src = 0;
	char p_dest = 0;
	framer frame;
	
	header();
	format(33);
	printf("\nIngresa la direccion de origen: "); scanf("%u", &src); limpiar();
	printf("\nIngresa la direccion de destino: "); scanf("%u", &dest); limpiar();
	printf("\nIngresa el puerto de origen: "); scanf("%u", &p_src); limpiar();
	printf("\nIngresa el puerto de destino: "); scanf("%u", &p_dest); limpiar();
	frame.new_csp_header(src, dest, p_src, p_dest);
}

/** 
 * Ciclo principal del programa
 */
 void cli::run()
{
	int a = 0;
	while(a != 7)
	{
		a = menu();
		switch(a)
		{
			case 1:
				process_commands(true);
				break;
			case 2:
				process_text(true);
				break;
			case 3:
				process_hex(true);
				break;
			case 4:
				process_commands();
				break;
			case 5:
				process_text();
				break;
			case 6:
				process_hex();
				break;
			case 7:
				calc_golay();
				break;
			case 8:
				set_csp();
				break;
			case 9:
				break;
				break;
			default:
				format(31);
				printf("\n\nOpcion no valida!\n");
				break;
		}
		if ( a != 7 )
		{
			pause();
		}
	}
}

