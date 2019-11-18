#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define ERROR -1
#define TODO_BIEN 0

int main(int argc, char *argv[]){
	int resultado = 0;
	int x=0;
	int i=0;
	char buffer[256];
	struct sockaddr_in sa;

	if(argc < 3){
		printf("Faltan parametros\n");
		return ERROR;
	}	
	
	x = socket(AF_INET,SOCK_STREAM,0);
	if(x==-1){
		printf("No se pudo crear el socket\n");
		return ERROR;		
	}

	bzero( (char *) &sa, sizeof(struct sockaddr_in) );
	sa.sin_family=AF_INET;
	sa.sin_port=htons(atoi(argv[2]));
	sa.sin_addr.s_addr=inet_addr(argv[1]);

	resultado = connect(x,(struct sockaddr *) &sa, sizeof(sa));
	if( resultado == -1){
		printf("Solicitud rechazada\n");
		return ERROR;	
	}

	printf("CONEXION REALIZADA\n");
	for(i = 0; i < 2; i++){
		bzero(buffer,256);
		recv(x,buffer,256,0);
		printf("%s\n",buffer);
		
		scanf("%s",buffer);
		send(x,buffer,strlen(buffer),0);
			
		bzero(buffer,256);
		recv(x,buffer,256,0);
		printf("%s\n",buffer);
	}

	bzero(buffer,256);
	recv(x,buffer,256,0);
	printf("%s\n",buffer);
	close(x);
	return TODO_BIEN;
}
