#include <netinet/in.h>  // protocol address
#include <arpa/inet.h>   // htons
#include <stdio.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>

int main(int narg,char *arg[]) {


 	struct sockaddr_in server;
 	char *ip;
 	int fd, numbytes,puerto;
 	char buf[1024];
 	char enviar[1024];

  if(narg!=3){

    printf("Error invalid argument");
    exit(-2);

  }
  else {

    puerto=atoi(arg[1]);
    ip=arg[2];

  }


  server.sin_family = AF_INET;
  server.sin_port = htons(puerto);
  server.sin_addr.s_addr=inet_addr(ip);
  bzero(&(server.sin_zero),8);

 	//Socket
 	if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1) {

  perror( "Socket Error: \n" );
 	exit(-1);

 	}

 	if(connect(fd, (struct sockaddr *)&server,sizeof(struct sockaddr))==-1) {

    perror( "Connect Error: \n" );
    exit(-1);

 	}


	while(1) {

 	//El servidor espera el primer mensaje

 		printf("Cliente: ");
    scanf("%s",enviar);
 		//scanf("%*c%[^\n]",enviar);
 		send(fd,enviar,1024,0);

 		if(strcmp(enviar,"adios")==0) {break;}

 		//El cliente recibe el mensaje del servidor
 		//recv(fd,buf,1024,0);

 		//if(strcmp(buf,"exit")==0) {break;}

 		//printf("Server: %s\n",buf);

	}

 		close(fd);

}
