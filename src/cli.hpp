#ifndef _CLI_H
#define _CLI_H 
 
 /**
  * Clase que se encarga de la interfaz de usuario
  */
class cli
{
	private:
		int menu_comandos(); //Agregar aqui el case del menu para llamar el comando
		int menu();
		void capturar_hex(char data[246]);
		void capturar_string(char data[246]);
		void process_commands(bool send);
		void process_text(bool send);
		void process_hex(bool send);
		char hexchar_to_int(char hex);
		void limpiar();
		void pause();
		void calc_golay();
		void set_csp();
		
	public:
		cli();
		void run();
		void header();
		void format(int fg, bool bold = false, bool underline = false, bool reset = false);
		const static int MAX_INPUT = 246;
};


#endif
