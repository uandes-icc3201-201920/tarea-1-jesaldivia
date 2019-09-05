#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <algorithm>
using namespace std;




int main(int argc, char** argv) {

	char *socket_path = "/tmp/db.tuples.sock";	
	string cmd = "";

	struct sockaddr_un addr;
	char buf[500];
	int fd,rc;

	if (argc > 1) socket_path=argv[1];

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;


	while (cmd != "quit") 
	{
		cout << ">";
		cin>>cmd;

		if (cmd=="quit")
		{
			cout<<"finalizando programa"<<endl;
			break;
		}

		else if (cmd=="connect")
		{

			if ( (fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 
			{
				perror("socket error");
				exit(-1);
			}

			if (*socket_path == '\0') 
			{
				*addr.sun_path = '\0';
				strncpy(addr.sun_path+1, socket_path+1, sizeof(addr.sun_path)-2);
			} 

			else 
			{
				strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
			}
			
			if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
			{
				perror("connect error");
				exit(-1);
			}
			cout<<"conexion exitosa"<<endl;


		}

		else if (cmd == "disconnect")
		{
			if( close(fd) == 0)
			{
				cout<<"desconectado con exito"<<endl;
			}
			else
			{
				perror("error al desconectar");
				exit(-1);
			}
		}

		else if (cmd == "insert")
		{
			cout<<"inserte la llave (un numero):"<<endl;
			unsigned long key;
			cin>>key;

			cout<<"inserte el vector (los valores separados por comas sin espacios)\n"<<endl;
			cin>>buf;
			
			buf[(int)sizeof(buf)+1]='\0';
			if (write(fd, buf, rc) != rc)
			{
				if (rc > 0) fprintf(stderr,"partial write");
				else 
				{
			    	perror("write error");
			    	exit(-1);
			  	}
			}		
		}

		else if (cmd == "get")
		{

		}

		else if ( cmd == "peek")
		{

		}

		else if ( cmd == "update")
		{

		}

		else if ( cmd == "delete")
		{

		}

		else if ( cmd == "list")
		{

		}

		else
		{
			cout<< "\ncomando no reconocido"<<endl;
		}
		
		/*
		while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) 
		{
			if (write(fd, buf, rc) != rc)
			{
				if (rc > 0) fprintf(stderr,"partial write");
				else 
				{
			    	perror("write error");
			    	exit(-1);
			  	}
			}
		}
		*/	

	}
	return 0;	
}