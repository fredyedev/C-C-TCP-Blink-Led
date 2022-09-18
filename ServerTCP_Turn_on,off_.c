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
#include <sys/mman.h>
#include <fcntl.h>

#define BASE (0x3F000000 + 0x200000)

int main(int narg,char *arg[]) {

	 struct sockaddr_in server;
	 struct sockaddr_in client;
	 int fd,fd2,longitud_cliente,numbytes,puerto;
	 char buf[1024]; //Para recibir mensaje
	 unsigned int volatile *gpio;


   if(narg!=2){

     printf("Error invalid argument");
     exit(-2);

   }
   else {

     puerto=atoi(arg[1]);

   }

  int fdl = open("/dev/mem", O_RDWR | O_SYNC);

 	if(fdl < 0) {

 		printf("Error al abrir archivo.\n");
 		exit (1);

 	}

 	gpio = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED,fdl, BASE);
   close(fdl);

 	*(gpio+1) |= 0x00200000;
 	fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);


	 server.sin_family= AF_INET;
	 server.sin_port = htons(puerto);
	 server.sin_addr.s_addr = INADDR_ANY;
	 bzero(&(server.sin_zero),8);

	 //Definicion de socket
	 if (( fd=socket(AF_INET,SOCK_STREAM,0) )<0) {

	 perror("Socket Error ");
	 printf("\n");
	 exit(-1);

	 }

	 //Avisar al sistema que se creo un socket
	 if(bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1) {

    perror("Bind Error ");
		printf("\n");
	  exit(-1);

	 }

	 if(listen(fd,5) == -1) {

    perror("Listen Error: ");
		printf("\n");
    exit(-1);

	 }

	 longitud_cliente= sizeof(struct sockaddr_in);

	 if ((fd2 = accept(fd,(struct sockaddr *)&client,&longitud_cliente))==-1) {

   perror("Accept Error ");
	 printf("\n");
	 exit(-1);

	 }

	//Ciclo para enviar y recibir mensajes
	 while(1) {

		 recv(fd2,buf,1024,0);

		 //if(strcmp(buf,"exit")==0) {break;}

		 printf("Cliente: %s\n",buf);

			if(strcmp(buf,"on")==0) {

			 *(gpio + 7) |= 0x00020000;
			 //send(fd2,"Receive on",1024,0);

		 }

		 if(strcmp(buf,"off")==0) {

			*(gpio +10) |= 0x00020000;
			//send(fd2,"Receive off",1024,0);

		}

		if(strcmp(buf,"exit")==0) {break;}

	}

	 close(fd2);
	 close(fd);

	 munmap((void*)gpio, getpagesize());

	return 0;

}
