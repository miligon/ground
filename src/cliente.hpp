#ifndef _CLIENTE_H
#define _CLIENTE_H 
 
class cliente
{
	private:
		int sockfd; // Socket de la conexion actual
		char* ip;
		int port;
		
	public:
		cliente(char* direccion, int puerto);
		int conectar();
		void send(char buffer[], int size);
		void cerrar();
		static bool connected;
};


#endif
