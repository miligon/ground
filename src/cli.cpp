#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cli.hpp"
#include "cli.hpp"
#include "framer.hpp"

cli::cli()
{
	//Nothing here yet!
}

void cli::capturar_string(char data[246])
{	
	char c= 0;
	int i = 0;
	
	format(33);
	printf("Ingrese el texto a enviar: ");
	/*
	while( (c = getchar())!= '\n' && i < 246 )
	{
		data[i] = c;
		putchar( c );
		i++;
	}*/
	scanf("%246s", data);
	fflush(stdin);
	data[strlen(data)-1] = 0;
	printf("Cadena: %s\nLongitud: %u\n", data, strlen(data));
}

void cli::capturar_hex(char data[246])
{	
	int c= 0;
	int i = 0;
	printf("Ingrese los bytes a enviar: ");
	
	while( i < 246 )
	{
		scanf("%u", &c);
		fflush(stdin);
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
	printf("\t3) Show frame from text\n");
	printf("\t4) Calc Golay24\n");
	printf("\t5) Change CSP Header\n");
	printf("\t6) Exit\n");
	printf("\n\n");
	format(32);
	printf("\tOption selected: "); scanf("%u", &opcion);
	fflush(stdin);
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
	printf("\t1) Comando 1\n");
	printf("\t2) Comando 2\n");
	printf("\t3) Comando 3\n");
	printf("\t4) Return\n");
	printf("\n\n");
	format(32);
	printf("\tOpcion seleccionada: "); scanf("%u", &opcion);
	fflush(stdin);
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

void cli::process_commands(bool send)
{
	framer frame;
	int a = 0;
	while((a=menu_comandos()) != 4)
	{
		switch(a)
		{
			case 1:
				printf("Opcion 1\n");
				frame.send_comando(1);
				break;
			case 2:
				printf("Opcion 2\n");
				break;
			case 3:
				printf("Opcion 3\n");
				break;
			default:
				format(31);
				printf("\n\nOpcion no valida!\n");
				system("sleep 0.5s");
				break;
		}
		scanf(%);
		fflush(stdin);
	}
}

void cli::process_text(bool send)
{
	char buff_in[cli::MAX_INPUT];
	framer frame;
	
	header();
	
	capturar_string(buff_in);
	frame.send_text(buff_in);
	scanf(%);
	fflush(stdin);
}

void cli::run()
{
	int a = 0;
	while(a != 6)
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
				break;
			case 5:
				break;
			case 6:
				break;
				break;
			default:
				format(31);
				printf("\n\nOpcion no valida!\n");
				break;
		}
		scanf(%);
		fflush(stdin);
	}
}

