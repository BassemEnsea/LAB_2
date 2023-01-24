#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "1069"
int main (int Numb_Arg,char * Arg_Vector[]){
	struct addrinfo hints;
	struct addrinfo *result;
	char * ServerName;
	int Sock,Sock2,Call,size,SendSize,RecvSize;
	
	//Data reception
	ServerName = strtok(Arg_Vector[1], ":");
	
	
	printf("Try on server : %s on port %s\n", ServerName, PORT);
	
	//call getaddrinfo to get the server address
	memset(&hints,0,sizeof(struct addrinfo));
	printf("\nRaised");
	hints.ai_family=AF_INET;//IPv4 addresses
	hints.ai_socktype=SOCK_DGRAM;//UDP socket Types
	hints.ai_protocol=IPPROTO_UDP;//make sure is UDP protocols
	printf("\nValues Ready");
	
	Call=getaddrinfo(Arg_Vector[1],PORT,&hints,&result);
	if (Call != 0){//checking if the call went wrong
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(Call));
        exit(EXIT_FAILURE);
    }
    
    int fileDescriptor=open(Arg_Vector[2],O_RDONLY);
    	if(fileDescriptor==1){
		perror("Erro in connection in Socket");
		exit(EXIT_FAILURE);
	}
	printf("socket= %d",Sock);
	printf("\nsocket test\n");
	
	char* WRQ = calloc(512, sizeof(char));//Write Request
	if(!WRQ){
		perror("calloc failed");
		exit(1);
	}
	
	
}
