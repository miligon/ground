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
		char command_1[7] = "XE1Rf8";
		char command_2[7] = "XE15cL";
		char command_3[7] = "XE1r0C";
		char command_4[7] = "XE1LfR";
		char command_5[7] = "XE1Af4";
		char command_6[7] = "XE14cR";
		char command_7[7] = "XE1Fs1";
		char command_8[7] = "XE1L6c";
		char command_9[7] = "XE1Ml6";
		char command_10[7] = "XE1A10";
		char command_11[7] = "XE1H5v";
		char command_12[7] = "XE1E5l";
		char command_13[7] = "XE1jCl";
		char command_14[7] = "XE1eR6";
		char command_15[7] = "XE103V";

		
	public:
		framer();
		void hexdump(char str[], int size/*= 0*/);
		void new_csp_header(char src, char dest, char p_src, char p_dest);
		void crear(char datos[], char buffer[250], int size);
		void send_comando(int comando, bool send); // En esta funcion se mandan a llamar los comandos para enviarse
		void send_text(char text[], bool send);
};


#endif
