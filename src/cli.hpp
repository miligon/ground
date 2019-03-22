#ifndef _CLI_H
#define _CLI_H 
 
class cli
{
	private:
		int menu_comandos();
		int menu();
		void capturar_hex(char data[246]);
		void capturar_string(char data[246]);
		void process_commands(bool send);
		void process_text(bool send);
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
