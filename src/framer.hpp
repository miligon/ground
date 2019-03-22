#ifndef _FRAMER_H
#define _FRAMER_H 
 
class framer
{
	private:
		char csp_header[4];
		char command_test[5] = { 0x55, 0x50, 0x41, 0x45, 0x50};
		
	public:
		framer();
		void hexdump(char str[], int size/*= 0*/);
		void new_csp_header(char src, char dest, char p_src, char p_dest);
		void crear(char datos[], char buffer[250], int size);
		int send_comando(int comando);
};


#endif
