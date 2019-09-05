#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

using namespace std;

// Almacenamiento KV
KVStore db;

int main(int argc, char** argv)
{	
	
	int sflag = 0;
	int opt;
	
	// Procesar opciones de linea de comando
    while ((opt = getopt (argc, argv, "s:")) != -1) {
        switch (opt)
		{
			/* Procesar el flag s si el usuario lo ingresa */
			case 's':
				sflag = 1;
				break;
			default:
				return EXIT_FAILURE;
        }	    	
    }
	char *socket_path = "/tmp/db.tuples.sock";

    if (sflag == 1)
    {
    	try 
    	{
    		*socket_path = *argv[1];	
    	}
    	catch(int x)
    	{
    		cout<<"error en la ruta entregada, se usara la ruta por defecto";
    		*socket_path = *argv[1];	    		
    	}
    	
    }
	struct sockaddr_un addr;
	char buf[100];
	int fd,cl,rc;

	if (argc > 1) socket_path=argv[1];

	if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket error");
		exit(-1);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	
	if (*socket_path == '\0') 
	{
		*addr.sun_path = '\0';
		strncpy(addr.sun_path+1, socket_path+1, sizeof(addr.sun_path)-2);
	} 
	else 
	{
		strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
		unlink(socket_path);
	}

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
	{
		perror("bind error");
		exit(-1);
	}

	if (listen(fd, 5) == -1) 
	{
		perror("listen error");
		exit(-1);
	}

	// Uso elemental del almacenamiento KV:
	
	// Creamos un arreglo de bytes a mano
	byte data[] = { 0x01, 0x01, 0x01, 0x01, 0x01 };

	// Luego un vector utilizando el arreglo de bytes
	vector<byte> vdata(data, data + sizeof(data));
	
	// Creamos el valor
	Value val = { 5, vdata };
	
	// Insertamos un par clave, valor directamente
	// en el mapa KV
	
	// Nota: Debiera diseñarse una solución más robusta con una interfaz
	// adecuada para acceder a la estructura.
	db.insert(std::pair<unsigned long, Value>(1000, val));
		
	// Imprimir lo que hemos agregado al mapa KV.
	cout << db[1000].size << " " << (int) db[1000].data[0] << endl;
	
	while(true)
	{
		read
	}
	while (1) 
	{
		if ( (cl = accept(fd, NULL, NULL)) == -1) 
		{
	  		perror("accept error");
	  		continue;
		}

		while ( (rc=read(cl,buf,sizeof(buf))) > 0) 
		{
	  		printf("read %u bytes: %.*s\n", rc, rc, buf);
	  		if (buf=="connect")
	  		{
	  			cout<<"se a conectado un cliente";
	  		}
	  		else if(buf==)
		}
		if (rc == -1) 
		{
	  		perror("read");
	  		exit(-1);
		}
		
		else if (rc == 0) 
		{
	  		printf("EOF\n");
	  		close(cl);
		}
	}





	return 0;
}
