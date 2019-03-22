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

void cli::pause()
{
	printf("\nPresione una tecla para continuar ...");
	scanf("%");
	limpiar();
}

void cli::limpiar()
{
	int ch;
	while ((ch = getchar()) != EOF && ch != '\n') ;
}

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

void cli::capturar_hex(char data[246])
{	
	int c= 0;
	int i = 0;
	
	format(33);
	printf("Ingrese los bytes a enviar: ");
	
	while( i < 246 )
	{
		scanf("%u", &c);
		limpiar();
		data[i] = (char)c;
		if(c == 0xA)
			break;
			
		printf("0x%x ", data[i] );
		i++;
	}
	
	data[i] = 0;
	printf("Cadena: %s\nLongitud: %u\n", data, strlen(data));
}

void cli::header()
{
	system("clear");
	printf("\n");
	
	format(32, true);
	printf("\tAztechSat 1 Radio Interface\n");
	printf("\n");
}

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
	printf("\t3) Show frame from predifined command\n");
	printf("\t4) Show frame from text\n");
	printf("\t5) Calc Golay24\n");
	printf("\t6) Change CSP Header\n");
	printf("\t7) Exit\n");
	printf("\n\n");
	format(32);
	printf("\tOption selected: "); scanf("%u", &opcion);
	limpiar();
	return opcion;
}

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

void cli::process_text(bool send = false)
{
	char buff_in[cli::MAX_INPUT];
	framer frame;
	
	header();
	
	capturar_string(buff_in);
	frame.send_text(buff_in, send);
}

void cli::calc_golay()
{
	uint32_t len = 0
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
    pause();
}

void cli::set_csp()
{
	char src = 0;
	char dest = 0;
	char p_src = 0;
	char p_dest = 0;
	framer frame;
	
	header();
	format(33);
	printf("\nIngresa la direccion de origen: "); scanf("%u", src); limpiar();
	printf("\nIngresa la direccion de destino: "); scanf("%u", dest); limpiar();
	printf("\nIngresa el puerto de origen: "); scanf("%u", p_src); limpiar();
	printf("\nIngresa el puerto de destino: "); scanf("%u", p_dest); limpiar();
	frame.new_csp_header(src, dest, p_src, p_dest);
    pause();
}

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
				process_commands();
				break;
			case 4:
				process_text();
				break;
			case 5:
				calc_golay();
				break;
			case 6:
				set_csp();
				break;
			case 7:
				break;
				break;
			default:
				format(31);
				printf("\n\nOpcion no valida!\n");
				break;
		}
		pause();
	}
}

