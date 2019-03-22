/**
 * Programa para enviar datos por GNURADIO con ASM+GOLAY
 * Autor: Miguel Limón González
 * Marzo 2019
 */


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "golay24.h"
#include "cliente.hpp"
#include "framer.hpp"
#include "cli.hpp"

/** 
 * Inicio del programa.
 */
int main()
{
	cli interfaz;
	cliente gnu("127.0.0.1",2500);
	
	interfaz.run(); //Hilo principal
	
	gnu.cerrar();
	
	
	return 0;
}
