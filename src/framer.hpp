#ifndef _FRAMER_H
#define _FRAMER_H 
 
/**
 * Clase para generar el frame de ASM+GOLAY
 */
class framer
{
	private:
		static char csp_header[4];
		/**
		 *  Aqui se pueden programar los comandos de telecomando y telemetria.
		 */
		char command_test[5] = { 0x55, 0x50, 0x41, 0x45, 0x50};
		
	public:
		framer();
		void hexdump(char str[], int size/*= 0*/);
		void new_csp_header(char src, char dest, char p_src, char p_dest);
		void crear(char datos[], char buffer[250], int size);
		void send_comando(int comando, bool send); // En esta funcion se mandan a llamar los comandos para enviarse
		void send_text(char text[], bool send);
};


#endif
